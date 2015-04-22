#include "gui.h"

#include <sstream>
#include <string>

void Gui::draw(const vector<Vertex> &vertices){

	gv = new GraphViewer(600,600,false);
	gv->createWindow(600,600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("orange");


	int x = 50;
	int y = 50;
	for(size_t i = 0; i < vertices.size(); i++)
	{
		if(i%2 == 0) y += 100;
		else{
			x += 100;
			y -= 100;
		}
		if(x >= 600){
			y += 100;
			x = 50;
		}

		y += 30;

		gv->addNode(vertices[i].getID(), x, y);
	}

	int edgeI = 0;
	for(size_t i = 0; i < vertices.size(); i++)
	{
		for(size_t j = 0; j < vertices[i].getAdj().size(); j++, edgeI++)
		{
			if(vertices[i].getAdj()[j].getDestID() < (int)i) continue;
			Sleep(500);
			gv->addEdge(edgeI, vertices[i].getID(), vertices[i].getAdj()[j].getDestID(), EdgeType::UNDIRECTED);

			gv->setEdgeWeight(edgeI, vertices[i].getAdj()[j].getDistance());

			gv->rearrange();
		}
	}

	gv->rearrange();
}
