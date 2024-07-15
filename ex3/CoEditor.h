#ifndef COEDITOR_H
#define COEDITOR_H

#include "UnboundedBuffer.h"
#include <string>

class CoEditor
{
private:
    UnboundedBuffer &queue; // Dispatcher category queue
    UnboundedBuffer &screenQueue;
    std::string category;

public:
    CoEditor(UnboundedBuffer &queue, UnboundedBuffer &screenQueue, const std::string &category);
    void process();
};

#endif // COEDITOR_H
