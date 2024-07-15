#include "Dispatcher.h"
#include <iostream>

Dispatcher::Dispatcher(std::vector<BoundedBuffer *> &producerQueues, UnboundedBuffer &sportsQueue, UnboundedBuffer &newsQueue, UnboundedBuffer &weatherQueue)
    : producerQueues(producerQueues), sportsQueue(sportsQueue), newsQueue(newsQueue), weatherQueue(weatherQueue) {}

void Dispatcher::dispatch()
{
    std::vector<bool> done(producerQueues.size(), false);

    while (true)
    {
        bool allDone = true;
        for (size_t i = 0; i < producerQueues.size(); ++i)
        {
            if (!done[i])
            {
                std::string message = producerQueues[i]->remove();

                if (message == "DONE")
                {
                    done[i] = true;
                }
                else
                {
                    allDone = false;

                    if (message.find("SPORTS") != std::string::npos)
                    {
                        sportsQueue.insert(message);
                    }
                    else if (message.find("NEWS") != std::string::npos)
                    {
                        newsQueue.insert(message);
                    }
                    else if (message.find("WEATHER") != std::string::npos)
                    {
                        weatherQueue.insert(message);
                    }
                    else
                    {
                        std::cerr << "Unknown message type: " << message << std::endl;
                    }
                }
            }
        }

        if (allDone)
        {
            sportsQueue.insert("DONE");
            newsQueue.insert("DONE");
            weatherQueue.insert("DONE");
            break;
        }
    }
}
