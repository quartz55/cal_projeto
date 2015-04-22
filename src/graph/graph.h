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
  int addVertex(const int &garbage);
  bool addEdge(const int &srcID, const int &destID, const double &distance);
  void printGraph();
  std::vector<int> findShortestPath(const int &srcID, const int &destID, const std::string &method);
  void resetVisited();
};

#endif
