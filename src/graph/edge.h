#ifndef EDGE_H
#define EDGE_H

class Edge
{
private:
    int destID;
    double distance;

public:
    Edge(int destID, double distance):destID(destID), distance(distance){}
    int getDestID() const { return destID;}
    int getDistance() const { return distance;}
    int setDistance(int dist) { return this->distance = dist;}

};

#endif
