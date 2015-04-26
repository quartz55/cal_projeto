#include "gui.h"

#include <sstream>
#include <string>

void Gui::draw(Graph &g){
    for(size_t i = 0; i < g.getVertices().size(); i++)
    {
        gv->addNode(g.getVertices()[i].getID());
    }

    for(size_t i = 0; i < g.getVertices().size(); i++)
    {
        for(size_t j = 0; j < g.getVertices()[i].getAdj().size(); j++)
        {
            std::vector<Edge> adj = g.getVertices()[i].getAdj();
            if(adj[j].getDestID() < (int)i
               && adj[j].getBidirectional()) continue;

            if(adj[j].getBidirectional())
                gv->addEdge(adj[j].getID(), g.getVertices()[i].getID(), adj[j].getDestID(), EdgeType::UNDIRECTED);
            else
                gv->addEdge(adj[j].getID(), g.getVertices()[i].getID(), adj[j].getDestID(), EdgeType::DIRECTED);

            gv->setEdgeWeight(adj[j].getID(), adj[j].getDistance());

            gv->rearrange();
        }
    }

    gv->rearrange();
}

void Gui::drawPath(Graph g, Path p){
    draw(g);

    for(unsigned int i=0 ; i < p.getVertices().size();i++)
    {
        gv->setVertexColor( p.getVertices()[i]->getID(), "green");
        gv->rearrange();
        guiSleep(1000);
        if(i < p.getVertices().size()-1)
        {
            int id1, id2;
            id1 = p.getVertices()[i]->getEdge(p.getVertices()[i+1]->getID()).getID();
            id2 = p.getVertices()[i+1]->getEdge(p.getVertices()[i]->getID()).getID();
            gv->setEdgeColor(id1, "black");
            gv->setEdgeColor(id2, "black");
            gv->rearrange();
        }
    }
}
