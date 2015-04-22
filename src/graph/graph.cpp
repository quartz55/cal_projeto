#include "graph.h"
#include <limits.h>
#include <algorithm>

int Graph::addVertex()
{
    int ID = vertices.size();
    vertices.push_back(Vertex(ID));
    return ID;
}

bool Graph::addEdge(const int &srcID, const int &destID, const double &distance )
{
    if(vertices[srcID].hasNeighbour(destID)) return false;
    vertices[srcID].addEdge(Edge(destID, distance));
    vertices[destID].addEdge(Edge(srcID, distance));
    return true;
}

void Graph::printGraph()
{
    for(size_t i = 0; i < vertices.size(); i++)
    {
        for(size_t k = 0; k < vertices[i].getAdj().size(); k++)
        {
            if(vertices[i].getAdj()[k].getDestID() <= (int)i) continue;
            std::cout << "(" << i << ")";
            std::cout << " --" << vertices[i].getAdj()[k].getDistance() << "--> (" << vertices[i].getAdj()[k].getDestID() << ")\n";
        }
        std::cout << "+------------------------+\n";
    }
}

std::vector<int> Graph::findShortestPath(const int &srcID, const int &destID)
{
    resetVisited();

    std::vector<double> tentative(vertices.size(), INT_MAX);
    std::vector<int> previous(vertices.size());
    tentative[srcID] = 0;

    bool done = false;
    while(!done)
    {
        /* Find vertex with min tentative value */
        double min = INT_MAX;
        int minID = -1;
        for(size_t i = 0; i < vertices.size(); i++)
        {
            if(!getVertex(i).wasVisited() && tentative[getVertex(i).getID()] < min)
            {
                min = tentative[getVertex(i).getID()];
                minID = getVertex(i).getID();
            }
        }

        /* Update vertex neighbours' tentative values */
        std::vector<Edge> adj = getVertex(minID).getAdj();
        for(size_t i = 0; i < adj.size(); i++)
        {
            if(getVertex(adj[i].getDestID()).wasVisited()) continue;

            double distance = adj[i].getDistance();
            double weight = tentative[adj[i].getDestID()];
            double newWeight = tentative[minID]+distance;

            if(newWeight < weight)
            {
                previous[adj[i].getDestID()] = minID;
                tentative[adj[i].getDestID()] = newWeight;
            }
        }

        getVertex(minID).setVisited(true);
        if(minID == destID || min >= INT_MAX)
        {
            done = true;
            break;
        }
    }

    std::vector<int> finalPath;
    finalPath.push_back(destID);
    int vertexID = previous[destID];
    while(vertexID != srcID)
    {
        finalPath.push_back(vertexID);
        vertexID = previous[vertexID];
    }
    finalPath.push_back(srcID);
    std::reverse(finalPath.begin(),finalPath.end());

    return finalPath;
}

std::vector<int> Graph::findLongestPath(const int &srcID, const int &destID)
{
    return std::vector<int>();
}

void Graph::resetVisited()
{
    for(size_t i = 0; i < vertices.size(); i++)
        vertices[i].setVisited(false);
}

Vertex& Graph::getVertex(int ID)
{
    for(size_t i = 0; i < vertices.size(); i++)
        if(ID == vertices[i].getID()) return vertices[i];

    return *(new Vertex(-1));
}
