#include "truck.h"

#include <cassert>

void Truck::collect()
{
    assert(path.getCost() <= capacity);
    path.clear();
    this->collected = true;
}
