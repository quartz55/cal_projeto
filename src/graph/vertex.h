#ifndef VERTEX_H
#define VERTEX_H

#include "edge.h"

#include <vector>

class Vertex{
private:
    int ID;
    std::vector<Edge> adjacent;
    bool visited;
    int tentative;

public:

    Vertex(int ID):ID(ID), visited(false), tentative(0){}
    bool hasNeighbour(int neighbourID);
    void addEdge(Edge adj){ adjacent.push_back(adj);}
    Edge& getEdge(int destID);

    std::vector<Edge>& getAdj() {return adjacent;}
    bool wasVisited() const {return visited;}
    bool setVisited(bool newVisited){return visited=newVisited;}
    int getID() const {return ID;}
    void setID(const int ID) {this->ID = ID;}
    int getTentative() const {return tentative;}
    void setTentative(const int tentative) {this->tentative = tentative;}
};

#endif
