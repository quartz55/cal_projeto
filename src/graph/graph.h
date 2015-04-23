#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include "edge.h"

#include <iostream>
#include <vector>
#include <cassert>

class Graph{
private:
    std::vector<Vertex> vertices;

    void resetVisited();

public:
    int addVertex();
    int addVertex(int ID);
    bool addEdge(const int &srcID, const int &destID, const double &distance);
    void printGraph();
    void printPath(const std::vector<int>& path);
    std::vector<int> findShortestPath(const int &srcID, const int &destID);
    std::vector<int> findLongestPath(const int &srcID, const int &destID);
    std::vector<Vertex>& getVertices(){return vertices;}
    Vertex& getVertex(int ID);
};

#endif
