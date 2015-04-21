#ifndef VERTEX_H
#define VERTEX_H

#include "edge.h"

#include <vector>

class Vertex{
private:
  std::vector<Edge> adjacent;
  int garbage;
  bool visited;

public:
  Vertex(int garbage):garbage(garbage),visited(false){}
  bool hasNeighbour(int neighbourID){
    for(unsigned int i = 0; i < adjacent.size(); i++)
      if(adjacent[i].getDestID() == neighbourID) return true;
    return false;
  }
  void addEdge(Edge adj){ adjacent.push_back(adj);}
  std::vector<Edge> getAdj() const {return adjacent;}

  bool wasVisited() const {return visited;}
  bool setVisited(bool newVisited){return visited=newVisited;}
};

#endif
