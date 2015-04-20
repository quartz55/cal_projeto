#include "graph.h"

int Graph::addVertex(const int garbage)
{
  vertices.push_back(Vertex(garbage));
  return vertices.size()-1;
}

bool Graph::addEdge( int srcID, int destID, double distance )
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

std::vector<int> Graph::findShortestPath(int srcID, int destID)
{
  std::vector<int> finalPath;
  finalPath.push_back(srcID);
  bool finished = false;

  while(finished != true)
    {
      int min = 99999;
      int currID = finalPath[finalPath.size()-1];
      int nextID;

      std::vector<Edge> edges = vertices[currID].getAdj();
      std::cout << currID << " -> ";

      for(unsigned int i = 0; i < edges.size(); i++)
        {
          bool visited = false;
          for(unsigned int k = 0; k < finalPath.size(); k++)
            {
              if(edges[i].getDestID() == finalPath[k])
                {
                  visited = true;
                  break;
                }
            }
          if(visited) continue;

          if(edges[i].getDestID() == destID)
            {
              nextID = destID;
              finished = true;
              break;
            }
          if(edges[i].getDistance() < min)
            {
              min = vertices[srcID].getAdj()[i].getDistance();
              nextID = vertices[srcID].getAdj()[i].getDestID();
            }
        }
      finalPath.push_back(nextID);
    } /* while */

  return finalPath;
}
