// UnboundedBuffer.h

#ifndef UNBOUNDEDBUFFER_H
#define UNBOUNDEDBUFFER_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <string> // Include string header for std::string

class UnboundedBuffer
{
private:
    std::queue<std::string> queue;    // Queue to store the strings as std::string
    std::mutex mtx;                   // Mutex for synchronization
    std::condition_variable notEmpty; // Condition variable to wait for items

public:
    UnboundedBuffer();
    ~UnboundedBuffer();
    void insert(const std::string &s); // Method to insert a string into the buffer
    std::string remove();              // Method to remove a string from the buffer
};

#endif // UNBOUNDEDBUFFER_H
