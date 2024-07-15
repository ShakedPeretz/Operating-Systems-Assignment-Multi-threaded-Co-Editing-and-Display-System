#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "BoundedBuffer.h"
#include "UnboundedBuffer.h"
#include <vector>

class Dispatcher
{
private:
    std::vector<BoundedBuffer *> &producerQueues;
    UnboundedBuffer &sportsQueue;
    UnboundedBuffer &newsQueue;
    UnboundedBuffer &weatherQueue;

public:
    Dispatcher(std::vector<BoundedBuffer *> &producerQueues, UnboundedBuffer &sportsQueue, UnboundedBuffer &newsQueue, UnboundedBuffer &weatherQueue);
    void dispatch();
};

#endif // DISPATCHER_H
