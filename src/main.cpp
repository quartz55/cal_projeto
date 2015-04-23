#include <iostream>
#include "./graph/graph.h"
#include "./gui/gui.h"

int main(void)
{
	Graph testGraph;
	//Gui gui;
	int v0 = testGraph.addVertex();
	int v1 = testGraph.addVertex();
	int v2 = testGraph.addVertex();
	int v3 = testGraph.addVertex();
	int v4 = testGraph.addVertex();
	int v5 = testGraph.addVertex();
	int v6 = testGraph.addVertex();


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

	//testGraph.printGraph();

	testGraph.topologicalSort();
	std::vector<int> path = testGraph.findShortestPath(v0, v5);

	/*for(unsigned int i = 0; i < path.size()-1; i++)
		std::cout << path[i] << " -> ";
	std::cout << path[path.size()-1] << "\n";*/

	//gui.draw(testGraph.getVertices());
	//getchar();

	return 0;
}
