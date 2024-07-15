#include "CoEditor.h"
#include <iostream>
#include <thread> // For std::this_thread::sleep_for
#include <chrono> // For std::chrono::milliseconds

CoEditor::CoEditor(UnboundedBuffer &queue, UnboundedBuffer &screenQueue, const std::string &category) 
    : queue(queue), screenQueue(screenQueue), category(category) {}

void CoEditor::process()
{
    while (true)
    {
        std::string message = queue.remove();

        if (message == "DONE")
        {
            screenQueue.insert(message);
            break;
        }

        // Simulate the editing process by blocking for 0.1 seconds
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Pass the message to the screen manager's queue
        screenQueue.insert(message);
    }
}
