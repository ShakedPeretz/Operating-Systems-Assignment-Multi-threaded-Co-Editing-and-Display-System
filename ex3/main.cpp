#include "Producer.h"
#include "Dispatcher.h"
#include "CoEditor.h"
#include "ScreenManager.h"
#include "BoundedBuffer.h"
#include "UnboundedBuffer.h"
#include <thread>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

struct ProducerConfig
{
    int numProducts;
    int queueSize;
};

void readConfig(const std::string &filename, std::vector<ProducerConfig> &producerConfigs)
{
    std::ifstream configFile(filename);
    if (!configFile)
    {
        std::cerr << "Error: Could not open configuration file." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(configFile, line))
    {
        if (line.find("PRODUCER") != std::string::npos)
        {
            ProducerConfig config;
            std::getline(configFile, line);
            config.numProducts = std::stoi(line);

            std::getline(configFile, line);
            std::istringstream iss(line);
            std::string temp;
            iss >> temp >> temp >> temp >> config.queueSize;

            producerConfigs.push_back(config);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <config file>" << std::endl;
        return 1;
    }

    std::string configFileName = argv[1];
    std::vector<ProducerConfig> producerConfigs;

    readConfig(configFileName, producerConfigs);

    // Create producer queues as BoundedBuffer pointers
    std::vector<BoundedBuffer *> producerQueues;
    for (const auto &config : producerConfigs)
    {
        producerQueues.push_back(new BoundedBuffer(config.queueSize));
    }

    // Create category queues as UnboundedBuffer
    UnboundedBuffer sportsQueue;
    UnboundedBuffer newsQueue;
    UnboundedBuffer weatherQueue;
    UnboundedBuffer screenQueue; // Shared queue for the screen manager

    // Create producers using BoundedBuffer queues
    std::vector<Producer *> producers;
    for (size_t i = 0; i < producerConfigs.size(); ++i)
    {
        producers.emplace_back(new Producer(i, producerConfigs[i].numProducts, *producerQueues[i]));
    }

    // Create dispatcher
    Dispatcher dispatcher(producerQueues, sportsQueue, newsQueue, weatherQueue);

    // Create co-editors
    CoEditor sportsEditor(sportsQueue, screenQueue, "SPORTS");
    CoEditor newsEditor(newsQueue, screenQueue, "NEWS");
    CoEditor weatherEditor(weatherQueue, screenQueue, "WEATHER");

    // Create screen manager
    ScreenManager screenManager(screenQueue);

    // Start producers in separate threads
    std::vector<std::thread> producerThreads;
    for (Producer *producer : producers)
    {
        producerThreads.emplace_back(&Producer::produce, producer);
    }

    // Start dispatcher in a separate thread
    std::thread dispatcherThread(&Dispatcher::dispatch, &dispatcher);

    // Start co-editors in separate threads
    std::thread sportsEditorThread(&CoEditor::process, &sportsEditor);
    std::thread newsEditorThread(&CoEditor::process, &newsEditor);
    std::thread weatherEditorThread(&CoEditor::process, &weatherEditor);

    // Start screen manager in a separate thread
    std::thread screenManagerThread(&ScreenManager::displayMessages, &screenManager);

    // Wait for all producer threads to finish
    for (std::thread &thread : producerThreads)
    {
        thread.join();
    }

    // Wait for dispatcher thread to finish
    dispatcherThread.join();

    // Wait for all co-editor threads to finish
    sportsEditorThread.join();
    newsEditorThread.join();
    weatherEditorThread.join();

    // Wait for screen manager thread to finish
    screenManagerThread.join();

    // Clean up producer queues
    for (BoundedBuffer *queue : producerQueues)
    {
        delete queue;
    }

    // Clean up producers
    for (Producer *producer : producers)
    {
        delete producer;
    }

    return 0;
}
