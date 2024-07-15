#include "UnboundedBuffer.h"

// Constructor
UnboundedBuffer::UnboundedBuffer() {}

// Destructor
UnboundedBuffer::~UnboundedBuffer() {}

// Method to insert a string into the buffer
void UnboundedBuffer::insert(const std::string &s)
{
    std::unique_lock<std::mutex> lock(mtx); // Unique lock to manage mutex
    queue.push(s);                          // Push the string into the queue
    notEmpty.notify_one();                  // Notify one waiting thread that there is a new item
}

// Method to remove a string from the buffer
std::string UnboundedBuffer::remove()
{
    std::unique_lock<std::mutex> lock(mtx); // Unique lock to manage mutex

    // Wait for the condition variable notEmpty. This will block the current thread until the queue is not empty.
    // While waiting, the mutex is released. Once the condition is met (queue is not empty), the mutex is reacquired.
    notEmpty.wait(lock, [this]
                  { return !queue.empty(); });

    std::string s = queue.front(); // Retrieve the first item from the queue
    queue.pop();                   // Remove the first item from the queue

    return s; // Return the retrieved item
}
