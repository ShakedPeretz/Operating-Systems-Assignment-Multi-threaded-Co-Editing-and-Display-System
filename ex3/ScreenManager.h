#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "UnboundedBuffer.h"
#include <string>

class ScreenManager
{
private:
    UnboundedBuffer &screenQueue;

public:
    ScreenManager(UnboundedBuffer &screenQueue);
    void displayMessages();
};

#endif // SCREENMANAGER_H
