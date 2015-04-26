#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include "edge.h"
#include "path.h"

#include <iostream>
#include <vector>
#include <cassert>

using std::vector;

class Graph{
private:
    int start, end;
    vector<Vertex> vertices;
    vector<Path> allPaths;

    void resetVisited();

public:
    int addVertex();
    int addVertex(int ID);
    bool addEdge(const int &srcID, const int &destID, const double &distance);
    bool addEdgeBi(const int &srcID, const int &destID, const double &distance);

    void removeVertex(const int& ID);
    void removeEdge(const int& srcID, const int& destID);
    void changeEdge(const int& srcID, const int& destID, const int& distance);

    int garbageToCollect();

    /*
     * Visualisations
     */
    void printGraph();
    void printAllPaths();

    /*
     * Algorithms
     */
    vector<int> findShortestPath(const int &srcID, const int &destID);
    Path& findLongestPath(const int& maxCapacity);
    void findAllPathsRec(const int& currID, const int& destID, Path &path, vector<Path> &allPaths, int &cost);
    void findAllPaths(const int &srcID, const int &destID);
    void topologicalSort(vector<Vertex> &vertex);

    /*
     * Gets and Sets
     */
    vector<Vertex>& getVertices(){return vertices;}
    Vertex& getVertex(int ID);
    int getStart(){ return start;}
    void setStart(const int& ID){ this->start = ID;}
    int getEnd(){ return end;}
    void setEnd(const int& ID){ this->end = ID;}
};

#endif
