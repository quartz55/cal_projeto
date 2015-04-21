#include "graph.h"
#include <limits.h>

int Graph::addVertex(const int &garbage)
{
  vertices.push_back(Vertex(garbage));
  return vertices.size()-1;
}

bool Graph::addEdge(const int &srcID, const int &destID, const double &distance )
{
  assert(srcID < vertices.size());
  assert(destID < vertices.size());

  if(vertices[srcID].hasNeighbour(destID)) return false;
  vertices[srcID].addEdge(Edge(destID, distance));
  vertices[destID].addEdge(Edge(srcID, distance));
  return true;
}

void Graph::printGraph()
{
  for(unsigned int i = 0; i < vertices.size(); i++)
    for(unsigned int k = 0; k < vertices[i].getAdj().size(); k++)
      std::cout << i << " -> " << vertices[i].getAdj()[k].getDestID() << " | " << vertices[i].getAdj()[k].getDistance() << "\n";
}

std::vector<int> Graph::findShortestPath(const int &srcID, const int &destID)
{
  resetVisited();

  std::vector<int> finalPath;
  return finalPath;
}

void Graph::resetVisited(){
  for(size_t i = 0; i < vertices.size(); i++)
    vertices[i].setVisited(false);
}
