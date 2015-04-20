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

public:
  int addVertex(const int garbage);
  bool addEdge(int srcID, int destID, double distance);
  void printGraph();
  std::vector<int> findShortestPath(int srcID, int destID);
};

#endif
