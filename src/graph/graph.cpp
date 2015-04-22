#include "graph.h"
#include <limits.h>
#include <algorithm>

int Graph::addVertex(const int &garbage)
{
    vertices.push_back(Vertex(garbage));
    return vertices.size()-1;
}

bool Graph::addEdge(const int &srcID, const int &destID, const double &distance )
{
    assert(srcID < (int)vertices.size());
    assert(destID < (int)vertices.size());

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

std::vector<int> Graph::findShortestPath(const int &srcID, const int &destID, const std::string &method)
{
    resetVisited();

    std::vector<double> tentative(vertices.size(), INT_MAX);
    std::vector<int> previous(vertices.size());
    tentative[srcID] = 0;

    bool done = false;
    while(!done)
    {
        double min = INT_MAX;
        int minID;
        for(size_t i = 0; i < vertices.size(); i++)
        {
            if(!vertices[i].wasVisited() && tentative[i] < min)
            {
                min = tentative[i];
                minID = i;
            }
        }
        std::vector<Edge> adj = vertices[minID].getAdj();
        for(size_t i = 0; i < adj.size(); i++)
        {
            if(vertices[adj[i].getDestID()].wasVisited()) continue;

            double distance = adj[i].getDistance();
            double weight = tentative[adj[i].getDestID()];
            double newWeight = tentative[minID]+distance;

            if(method == "max")
            {
                weight = (double)1.0/weight;
                newWeight = (double)1.0/newWeight;
            }

            if(newWeight < weight)
            {
                previous[adj[i].getDestID()] = minID;
                tentative[adj[i].getDestID()] = ;
            }
        }
        vertices[minID].setVisited(true);
        if(minID == destID || min >= INT_MAX)
        {
            done = true;
            break;
        }
    }

    for(size_t i = 0; i < tentative.size(); i++)
        std::cout << tentative[i] << " - ";
    std::cout << "\n";

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

void Graph::resetVisited()
{
    for(size_t i = 0; i < vertices.size(); i++)
        vertices[i].setVisited(false);
}
