#ifndef PRODUCER_H
#define PRODUCER_H

#include "BoundedBuffer.h"
#include <string>

class Producer {
private:
    int id;
    int numProducts;
    int countSports;
    int countNews;
    int countWeather;
    BoundedBuffer &queue; // Reference to BoundedBuffer

public:
    Producer(int id, int numProducts, BoundedBuffer &queue);
    int getId();
    int getCount(std::string type);
    void produce();
};

#endif // PRODUCER_H
