#include "truck.h"

#include <cassert>

int Truck::nextID = 0;

void Truck::collect()
{
    if(this->collected) return;
    assert(path.getCost() <= capacity);
    path.clear();
    this->collected = true;
}

void Truck::reset()
{
    path = Path();
    this->collected = false;
}

bool Truck::operator> (const Truck &t2) const
{
    return this->capacity > t2.getCapacity();
}
