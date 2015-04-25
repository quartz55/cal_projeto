#include "graph.h"
#include <limits.h>
#include <algorithm>
#include <iostream>

int Graph::addVertex()
{
    int ID = 0;
    while(addVertex(ID) == -1) ID++;
    return ID;
}

int Graph::addVertex(int ID)
{
    bool exists = false;
    for(size_t i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].getID() == ID)
        {
            exists = true;
            break;
        }
    }
    if(!exists){
     vertices.push_back(Vertex(ID));
     return ID;
    }
    return -1;
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
    std::cout << "+------------------------+\n";
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

void Graph::printAllPaths()
{
    std::cout << "+------------------------+\n";
    std::cout << "+        All Paths       +\n";
    std::cout << "+------------------------+\n";
    for(size_t i = 0; i < allPaths.size(); i++)
    {
        std::cout << allPaths[i] << "\n";
    }
    std::cout << "+------------------------+\n";
}

void Graph::findAllPathsRec(const int& currID, const int& destID, Path &path, std::vector<Path> &allPaths, int &cost)
{
    std::vector<Edge> adj = getVertex(currID).getAdj();
    for(std::vector<Edge>::const_iterator adj_it = adj.begin();
        adj_it != adj.end();
        adj_it++)
    {

        if(!path.hasVertex((*adj_it).getDestID()))
        {
            cost += (*adj_it).getDistance();
            path.addVertex(getVertex((*adj_it).getDestID()));
            if((*adj_it).getDestID() == destID)
            {
                path.setCost(cost);
                allPaths.push_back(path);
            }
            else findAllPathsRec((*adj_it).getDestID(), destID, path, allPaths, cost);

            Vertex v2 = path.last();
            path.pop();
            Vertex v1 = path.last();

            for(size_t i = 0; i < v1.getAdj().size(); i++)
            {
                if(v1.getAdj()[i].getDestID() == v2.getID())
                {
                    cost -= v1.getAdj()[i].getDistance();
                    break;
                }
            }
        }
    }
}

void Graph::findAllPaths(const int &srcID, const int &destID)
{
    Path path;
    path.addVertex(getVertex(srcID));
    int cost = 0;
    findAllPathsRec(srcID, destID, path, allPaths, cost);
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

Path& Graph::findLongestPath()
{
    int max = -1;
    Path *p;
    for(size_t i = 0; i < allPaths.size(); i++)
    {
        if(allPaths[i].getCost() > max)
        {
            max = allPaths[i].getCost();
            p = &allPaths[i];
        }
    }

    return *p;
}

Vertex& Graph::getVertex(int ID)
{
    for(size_t i = 0; i < vertices.size(); i++)
        if(ID == vertices[i].getID()) return vertices[i];

    return *(new Vertex(-1));
}

bool sortByEdge(Vertex v, Vertex v1)
{
    return v.getAdj().size() < v1.getAdj().size();
}

void Graph::topologicalSort(std::vector<Vertex> &vertex)
{
    sort(vertex.begin(),vertex.end(),sortByEdge);
}

void Graph::resetVisited()
{
    for(size_t i = 0; i < vertices.size(); i++)
        vertices[i].setVisited(false);
}
