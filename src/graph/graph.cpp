#include "graph.h"
#include <limits.h>
#include <algorithm>
#include <iostream>
#include <functional>

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
	vertices[srcID].addEdge(Edge(destID, distance, false));
	return true;
}

bool Graph::addEdgeBi(const int &srcID, const int &destID, const double &distance )
{
	if(vertices[srcID].hasNeighbour(destID)) return false;
	vertices[srcID].addEdge(Edge(destID, distance, true));
	vertices[destID].addEdge(Edge(srcID, distance, true));
	return true;
}

void Graph::removeVertex( const int &ID )
{
    for(size_t i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].getID() == ID)
        {
            vertices.erase(vertices.begin()+i);
            --i;
        }

        for(size_t j = 0; j < vertices[i].getAdj().size(); j++)
        {
            if(vertices[i].getAdj()[j].getDestID() == ID)
            {
                vertices[i].getAdj().erase(vertices[i].getAdj().begin()+j);
                --j;
            }
        }
    }
}

void Graph::removeEdge( const int &srcID, const int &destID )
{
    for(size_t i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].getID() == srcID)
        {
            for(size_t j = 0; j < vertices[i].getAdj().size(); j++)
            {
                if(vertices[i].getAdj()[j].getDestID() == destID)
                {
                    if(vertices[i].getAdj()[j].getBidirectional())
                        getVertex(destID).getEdge(srcID).setBidirectional(false);

                    vertices[i].getAdj().erase(vertices[i].getAdj().begin()+j);
                    break;
                }
            }
            break;
        }
    }
}

void Graph::changeEdge( const int &srcID, const int &destID, const int& distance)
{
    for(size_t i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].getID() == srcID)
        {
            for(size_t j = 0; j < vertices[i].getAdj().size(); j++)
            {
                if(vertices[i].getAdj()[j].getDestID() == destID)
                {
                    if(vertices[i].getAdj()[j].getBidirectional())
                        getVertex(destID).getEdge(srcID).setDistance(distance);

                    vertices[i].getAdj()[j].setDistance(distance);
                    break;
                }
            }
            break;
        }
    }
}

int Graph::trashToCollect()
{
    int total = 0;
    for(size_t i = 0; i < vertices.size(); i++)
    {
        for(size_t j = 0; j < vertices[i].getAdj().size(); j++)
        {
            if(vertices[i].getAdj()[j].getDestID() < (int)i) continue;
            total += vertices[i].getAdj()[j].getDistance();
        }
    }
    return total;
}

void Graph::printGraph()
{
    std::cout << "+------------------------+\n";
    std::cout << "| Start: " << start << " | End: " << end << "\n";
    std::cout << "+------------------------+\n";
    std::cout << "| Total trash: " << trashToCollect() << "\n";
    std::cout << "+------------------------+\n";
    for(size_t i = 0; i < vertices.size(); i++)
    {

        bool printed = false;

        for(size_t k = 0; k < vertices[i].getAdj().size(); k++)
        {
            // if(vertices[i].getAdj()[k].getDestID() <= (int)i && vertices[i].getAdj()[k].getBidirectional()) continue;
            printed = true;
            std::cout << "| (" << vertices[i].getID() << ")";
            std::cout << " --" << vertices[i].getAdj()[k].getDistance() << "--> (" << vertices[i].getAdj()[k].getDestID() << ")\n";
        }
        if(!printed)
            std::cout << "| (" << vertices[i].getID() << ")\n";
        std::cout << "+------------------------+\n";
    }
}

void Graph::printAllPaths()
{
    /* Descending order of trash */
    std::cout << "+------------------------+\n";
    std::cout << "|        All Paths       |\n";
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
    this->allPaths.clear();
    findAllPathsRec(srcID, destID, path, this->allPaths, cost);
    std::sort(allPaths.begin(), allPaths.end(), std::greater<Path>());
}

std::vector<int> Graph::findShortestPath(const int &srcID, const int &destID)
{
    resetVisited();

    std::vector<int> tentative(vertices.size(), INT_MAX);
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

Path& Graph::findLongestPath(const int& maxCapacity)
{
    int max = -1;
    Path *p = NULL;
    for(size_t i = 0; i < allPaths.size(); i++)
    {
        if(allPaths[i].getCost() > max && allPaths[i].getCost() <= maxCapacity)
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
