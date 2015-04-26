#ifndef EDGE_H
#define EDGE_H

class Edge
{
private:
    int destID;
    int distance;
    bool bidirectional;

public:

    Edge(int destID, double distance, bool bidirectional):destID(destID), distance(distance), bidirectional(bidirectional){}
    int getDestID() const { return destID;}
    int getDistance() const { return distance;}
    int setDistance(int dist) { return this->distance = dist;}
    bool getBidirectional() const {return bidirectional;}
    void setBidirectional(const bool bidirectional) {this->bidirectional = bidirectional;}
};

#endif
