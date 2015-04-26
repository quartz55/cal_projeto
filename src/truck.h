#ifndef TRUCK_H
#define TRUCK_H

#include "./graph/path.h"
#include <iostream>

class Truck
{
private:
    int capacity;
    bool collected;
    Path path;
    int ID;
    static int nextID;

public:

    Truck(int capacity):capacity(capacity), collected(false)
        {
            ID = nextID++;
        }
    void collect();
    void reset();

    friend std::ostream& operator<< (std::ostream& os, const Truck& t);

    /*
     * Gets and Sets
     */
    Path getPath() const {return path;}
    void setPath(Path& path) {this->path = path;}
    bool hasCollected() const {return collected;}
    void setCollected(const int collected) {this->collected = collected;}
    int getCapacity() const {return capacity;}
    void setCapacity(const int capacity) {this->capacity = capacity;}
    int getID() const {return ID;}
};

#endif

inline std::ostream& operator<< (std::ostream& os, const Truck& t)
{
    os << "| Truck " << t.ID << " | " << "Capacity " << t.capacity << " | " <<
        (t.collected ? "Collected" : "Not Collected") << " |\n" <<
        t.getPath();
    return os;
}
