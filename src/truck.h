#ifndef TRUCK_H
#define TRUCK_H

#include "./graph/path.h"

class Truck
{
private:
    int capacity;
    bool collected;
    Path path;

public:

    Truck(int capacity):capacity(capacity), collected(false){}
    void collect();

    /*
     * Gets and Sets
     */
    Path getPath() const {return path;}
    void setPath(Path& path) {this->path = path;}
    bool hasCollected() const {return collected;}
    void setCollected(const int collected) {this->collected = collected;}
    int getCapacity() const {return capacity;}
    void setCapacity(const int capacity) {this->capacity = capacity;}
};

#endif
