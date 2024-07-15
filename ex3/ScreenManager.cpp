#include "ScreenManager.h"
#include <iostream>

ScreenManager::ScreenManager(UnboundedBuffer &screenQueue) : screenQueue(screenQueue) {}

void ScreenManager::displayMessages()
{
    int doneCount = 0; // Counter for the number of "DONE" messages
    while (true)
    {
        std::string message = screenQueue.remove();
        
        // Check for "DONE" message
        if (message == "DONE")
        {
            doneCount++;
            if (doneCount == 3) // If all co-editors are done
            {
                std::cout << "DONE\n";
                break;
            }
        }
        else
        {
            // Display the message
            std::cout << message << std::endl;
        }
    }
}
