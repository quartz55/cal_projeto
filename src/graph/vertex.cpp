#include "vertex.h"

#include <iostream>

bool Vertex::hasNeighbour(int neighbourID)
{
    for(unsigned int i = 0; i < adjacent.size(); i++)
        if(adjacent[i].getDestID() == neighbourID) return true;
    return false;
}

Edge& Vertex::getEdge(int destID)
{
    for(size_t i = 0; i < adjacent.size(); i++)
    {
        if(adjacent[i].getDestID() == destID) return adjacent[i];
    }

    return *(new Edge(-1, -1, false));
}
