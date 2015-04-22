#include <iostream>
#include "./graph/graph.h"

int main(void){
  Graph testGraph;
  int v0 = testGraph.addVertex(80);
  int v1 = testGraph.addVertex(30);
  int v2 = testGraph.addVertex(60);
  int v3 = testGraph.addVertex(90);
  int v4 = testGraph.addVertex(90);
  int v5 = testGraph.addVertex(90);
  int v6 = testGraph.addVertex(90);

  testGraph.addEdge(v0, v1, 4);
  testGraph.addEdge(v0, v2, 3);
  testGraph.addEdge(v0, v4, 7);

  testGraph.addEdge(v1, v2, 6);
  testGraph.addEdge(v1, v3, 5);

  testGraph.addEdge(v2, v3, 11);
  testGraph.addEdge(v2, v4, 8);

  testGraph.addEdge(v3, v4, 2);
  testGraph.addEdge(v3, v5, 2);
  testGraph.addEdge(v3, v6, 10);

  testGraph.addEdge(v4, v6, 5);

  testGraph.addEdge(v5, v6, 3);

  testGraph.printGraph();

  std::vector<int> path = testGraph.findShortestPath(v0, v5, "max");
  for(unsigned int i = 0; i < path.size()-1; i++)
    std::cout << path[i] << " -> ";

  std::cout << path[path.size()-1] << "\n";

  return 0;
}
