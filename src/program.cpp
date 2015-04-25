#include "program.h"

#include <iostream>
#include <fstream>
#include <sstream>

Program::Program()
{
    start();
}

bool Program::start()
{

    loadGraph("example", m_currentGraph);
    m_currentGraph.printGraph();

    std::vector<int> costs;
    m_currentGraph.findAllPaths(0, 5);
    m_currentGraph.printAllPaths();

    Path longestPath = m_currentGraph.findLongestPath();
    std::cout << longestPath << "\n";

    return true;
}

bool Program::exit()
{
    return true;
}

bool Program::loadGraph(const std::string& Filename, Graph& emptyGraph)
{
    if(!emptyGraph.getVertices().empty()) emptyGraph.getVertices().clear();

    std::ifstream loadFile;
    std::string filePath = GRAPHS_SAVE_PATH + Filename + GRAPHS_EXTENSION;
    loadFile.open(filePath.c_str());
    if(loadFile.is_open())
    {
        std::string buffer;
        getline(loadFile, buffer);
        if(buffer != "Vertices:")
        {
            std::cerr << "Invalid file\n";
            return false;
        }

        do
        {
            getline(loadFile, buffer);
            std::stringstream ss(buffer);
            int v_ID;
            ss >> v_ID;
            emptyGraph.addVertex(v_ID);
        } while(buffer[0] != '-');

        getline(loadFile, buffer);
        if(buffer != "Edges:")
        {
            std::cerr << "Invalid file\n";
            return false;
        }
        int v_currID;
        while(getline(loadFile, buffer))
        {

            if(buffer == "V:")
            {
                getline(loadFile, buffer);
                std::stringstream ss(buffer);
                ss >> v_currID;
            }
            else{
                std::stringstream ss(buffer);
                int e_destID, e_distance;
                ss >> e_destID >> e_distance;
                emptyGraph.addEdge(v_currID, e_destID, e_distance);
            }
        }
    }
    else
    {
        std::cerr << "Couldn't find " << filePath << "\n";
        return false;
    }
    loadFile.close();
    return true;
}

void Program::saveGraph(const std::string& Filename, Graph graph)
{
    std::ofstream saveFile;
    std::string filePath = GRAPHS_SAVE_PATH + Filename + GRAPHS_EXTENSION;
    saveFile.open(filePath.c_str());
    if(saveFile.is_open())
    {
        saveFile << "Vertices:\n";
        for(size_t i = 0; i < graph.getVertices().size(); i++)
        {
            saveFile << graph.getVertices()[i].getID() << "\n";
        }

        saveFile << "----------\n";

        saveFile << "Edges:\n";
        for(size_t i = 0; i < graph.getVertices().size(); i++)
        {
            saveFile << "V:\n" << graph.getVertices()[i].getID() << "\n";
            std::vector<Edge> adj = graph.getVertices()[i].getAdj();
            for(size_t j = 0; j < adj.size(); j++)
            {
                saveFile << adj[j].getDestID() << " " << adj[j].getDistance() << "\n";
            }
        }
    }
    else throw "Couldn't write to " + filePath + "\n";
    saveFile.close();
}
