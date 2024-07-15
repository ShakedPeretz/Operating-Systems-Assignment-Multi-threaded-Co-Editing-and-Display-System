#include "BoundedBuffer.h"

// Constructor to initialize the BoundedBuffer - According to the Bounded-Buffer Problem
BoundedBuffer::BoundedBuffer(int size) : maxSize(size)
{
    sem_init(&empty, 0, size); // Initialize empty with size
    sem_init(&full, 0, 0);     // Initialize full with 0
    sem_init(&mutex, 0, 1);    // Initialize mutex with 1 (binary semaphore)
}

// Destructor to destroy the semaphores
BoundedBuffer::~BoundedBuffer()
{
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
}

// Method to insert a string into the buffer
void BoundedBuffer::insert(const std::string &s)
{
    sem_wait(&empty); // Wait for an empty slot
    sem_wait(&mutex); // Wait for exclusive access

    // Critical section
    queue.push(s); // Add the string to the queue

    sem_post(&mutex); // Release exclusive access
    sem_post(&full);  // Signal that there is a new full slot
}

// Method to remove a string from the buffer
std::string BoundedBuffer::remove()
{
    sem_wait(&full);  // Wait for a full slot
    sem_wait(&mutex); // Wait for exclusive access

    std::string s = queue.front();
    queue.pop(); // Remove the string from the queue

    sem_post(&mutex); // Release exclusive access
    sem_post(&empty); // Signal that there is a new empty slot

    return s;
}
