#ifndef BOUNDEDBUFFER_H
#define BOUNDEDBUFFER_H

#include <queue>
#include <semaphore.h>
#include <string>

class BoundedBuffer
{
private:
    std::queue<std::string> queue; // Queue to store the strings
    int maxSize;                   // Maximum size of the queue
    sem_t empty;                   // Semaphore to count empty slots at buffer
    sem_t full;                    // Semaphore to count full slots at buffer
    sem_t mutex;                   // Semaphore to ensure mutual exclusion

public:
    BoundedBuffer(int size);
    ~BoundedBuffer();
    void insert(const std::string &s);
    std::string remove();
};

#endif // BOUNDEDBUFFER_H
