#include "Producer.h"
#include <random>
#include <iostream>

Producer::Producer(int id, int numProducts, BoundedBuffer &queue)
    : id(id), numProducts(numProducts), countSports(0), countNews(0), countWeather(0), queue(queue) {
}

int Producer::getId() {
    return id;
}

int Producer::getCount(std::string type) {
    if (type == "SPORTS")
        return countSports;
    else if (type == "NEWS")
        return countNews;
    else if (type == "WEATHER")
        return countWeather;
    else
        return -1; // Handle unknown type or error condition
}

void Producer::produce() {
    std::random_device rd;
    std::mt19937 rng(rd()); // Initialize Mersenne Twister with a random seed from random_device

    std::uniform_int_distribution<int> distribution(0, 2); // Distribution for random category selection
    const char *categories[] = {"SPORTS", "NEWS", "WEATHER"};

    for (int i = 0; i < numProducts; ++i) {
        // Randomly select a category
        int index = distribution(rng);
        std::string type = categories[index];

        // Construct the message
        std::string message = "producer " + std::to_string(id) + " " + type + " " + std::to_string(getCount(type));

        // Insert message into the queue
        queue.insert(const_cast<char *>(message.c_str()));

        // Update the count for the selected category
        if (type == "SPORTS")
            ++countSports;
        else if (type == "NEWS")
            ++countNews;
        else if (type == "WEATHER")
            ++countWeather;
    }

    // Signal end of production
    queue.insert("DONE");
}
