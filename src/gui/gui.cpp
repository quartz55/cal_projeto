#include "gui.h"

#include <sstream>
#include <string>

void Gui::draw(Graph &g){
	int x = 50;
	int y = 50;
	for(size_t i = 0; i < g.getVertices().size(); i++)
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

		gv->addNode(g.getVertices()[i].getID(), x, y);
	}

	int edgeI = 0;
	for(size_t i = 0; i < g.getVertices().size(); i++)
	{
		for(size_t j = 0; j < g.getVertices()[i].getAdj().size(); j++, edgeI++)
		{
			if(g.getVertices()[i].getAdj()[j].getDestID() < (int)i) continue;
			gv->addEdge(edgeI, g.getVertices()[i].getID(), g.getVertices()[i].getAdj()[j].getDestID(), EdgeType::UNDIRECTED);

			gv->setEdgeWeight(edgeI, g.getVertices()[i].getAdj()[j].getDistance());

			gv->rearrange();
		}
	}

	gv->rearrange();
}

void Gui::drawPath(Graph g, Path p){
	//draw(g);

	int x = 50;
	int y = 50;
	for(size_t i = 0; i < g.getVertices().size(); i++)
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

		gv->addNode(g.getVertices()[i].getID(), x, y);
	}

	for(unsigned int i=0 ; i < p.getVertices().size();i++){
		gv->setVertexColor( p.getVertices()[i]->getID(), "green");
		Sleep(1000);
		gv->rearrange();
	}

	int edgeI = 0;
	int coisa;
	for(size_t i = 0; i < g.getVertices().size(); i++)
	{
		if(p.getVertices()[coisa]->getID() == g.getVertices()[i].getID()){
			for(size_t j = 0; j < g.getVertices()[i].getAdj().size(); j++, edgeI++)
			{
				if(g.getVertices()[i].getAdj()[j].getDestID() < (int)i) continue;
				gv->addEdge(edgeI, g.getVertices()[i].getID(), g.getVertices()[i].getAdj()[j].getDestID(), EdgeType::UNDIRECTED);

				gv->setEdgeWeight(edgeI, g.getVertices()[i].getAdj()[j].getDistance());
				if(p.getVertices()[coisa]->getAdj()[0].getDestID() == g.getVertices()[i].getAdj()[j].getDestID()){
				gv->setEdgeColor(edgeI,"black");
				Sleep(1000);
				gv->rearrange();
				}
				coisa++;
				gv->rearrange();
			}
		}
		else {
		for(size_t j = 0; j < g.getVertices()[i].getAdj().size(); j++, edgeI++)
		{
			if(g.getVertices()[i].getAdj()[j].getDestID() < (int)i) continue;
			gv->addEdge(edgeI, g.getVertices()[i].getID(), g.getVertices()[i].getAdj()[j].getDestID(), EdgeType::UNDIRECTED);

			gv->setEdgeWeight(edgeI, g.getVertices()[i].getAdj()[j].getDistance());
			gv->rearrange();
		}
		}
	}

	/*
for(size_t i = 0; i < p.getVertices().size(); i++)
{
	for(size_t j = 0; j < p.getVertices()[i]->getAdj().size(); j++, edgeI++)
	{
		if(p.getVertices()[i]->getAdj()[j].getDestID() < (int)i) continue;

		gv->addEdge(edgeI, p.getVertices()[i]->getID(), p.getVertices()[i]->getAdj()[j].getDestID(), EdgeType::UNDIRECTED);
		gv->setEdgeColor(edgeI,"black");
		Sleep(1000);
		gv->rearrange();
	}
}*/
}
