#include <iostream>
#include "./graph/graph.h"

int main(void){
  Graph testGraph;
  int v0 = testGraph.addVertex(80);
  int v1 = testGraph.addVertex(30);
  int v2 = testGraph.addVertex(60);
  int v3 = testGraph.addVertex(90);
  int v4 = testGraph.addVertex(90);

  testGraph.addEdge(v0, v1, 100);
  testGraph.addEdge(v0, v4, 120);

  testGraph.addEdge(v1, v2, 100);
  testGraph.addEdge(v1, v4, 100);

  testGraph.addEdge(v2, v3, 100);

  testGraph.addEdge(v4, v1, 100);
  testGraph.addEdge(v4, v2, 20);

  testGraph.printGraph();

  std::vector<int> path = testGraph.findShortestPath(v0, v3);
  for(unsigned int i = 0; i < path.size()-1; i++)
    std::cout << path[i] << " -> ";

  std::cout << path[path.size()-1] << "\n";

  return 0;
}
