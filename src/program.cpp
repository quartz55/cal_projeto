#include "program.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits.h>

const int DEFAULT_CAPACITY = 20;

Program::Program()
{
    start();
}

bool Program::start()
{
    loadGraph("example", m_currentGraph);

    mainMenu();

    return exit();
}

void Program::mainMenu()
{
    while(true)
    {
        int options = 1;
        input.clear();
        std::cout << "Lixo e Caixotes LDA\n\n";
        std::cout << "+-----------+\n";
        std::cout << "| Main Menu |\n";
        std::cout << "+-----------+\n";
        std::cout << options++ << ". Map\n";
        std::cout << options++ << ". Trucks\n";
        std::cout << options++ << ". Exit\n";

        int choice = input.getUnsignedInt(" > ");
        options = 1;
        if(choice == options++)
        {
            mapMenu();
        }
        else if(choice == options++)
        {
            truckMenu();
        }
        else if(choice == options++)
        {
            input.wait("\n\n* Press ENTER to quit *\n");
            break;
        }
    }
}

void Program::mapMenu()
{
    while(true)
    {
        int options = 1;
        input.clear();
        std::cout << "Lixo e Caixotes LDA\n\n";
        std::cout << "+----------+\n";
        std::cout << "| Map Menu |\n";
        std::cout << "+----------+\n";
        std::cout << options++ << ". Show map (CLI)\n";
        std::cout << options++ << ". Show map (GUI)\n";
        std::cout << options++ << ". Show all paths\n";
        std::cout << options++ << ". Modify map\n";
        std::cout << options++ << ". Exit\n";

        int choice = input.getUnsignedInt(" > ");
        options = 1;
        if(choice == options++)
        {
            input.clear();
            m_currentGraph.printGraph();
            input.wait("* Press ENTER to continue *\n");
        }
        else if(choice == options++)
        {
            input.clear();
            m_currentGraph.printGraph();
            input.wait("* Press ENTER to continue *\n");
        }
        else if(choice == options++)
        {
            input.clear();
            m_currentGraph.findAllPaths(m_currentGraph.getStart(), m_currentGraph.getEnd());
            m_currentGraph.printAllPaths();
            input.wait("* Press ENTER to continue *\n");
        }
        else if(choice == options++)
        {
            modifyMapMenu();
        }
        else if(choice == options++)
        {
            return;
        }
    }
}

void Program::modifyMapMenu()
{
    while(true)
    {
        int options = 1;
        input.clear();
        std::cout << "Lixo e Caixotes LDA\n\n";
        std::cout << "+-----------------+\n";
        std::cout << "| Modify Map Menu |\n";
        std::cout << "+-----------------+\n";
        m_currentGraph.printGraph();
        std::cout << options++ << ". Add vertex\n";
        std::cout << options++ << ". Add edge\n";
        std::cout << options++ << ". Change edge\n";
        std::cout << options++ << ". Remove vertex\n";
        std::cout << options++ << ". Remove edge\n";
        std::cout << options++ << ". Change start\n";
        std::cout << options++ << ". Change end\n";
        std::cout << options++ << ". Save map\n";
        std::cout << options++ << ". Load map\n";
        std::cout << options++ << ". Exit\n";

        int choice = input.getUnsignedInt(" > ");
        options = 1;
        if(choice == options++)
        {
            m_currentGraph.addVertex();
        }
        else if(choice == options++)
        {
            int src,dest;
            double garbage;
            src = input.getUnsignedInt("Start vertex? ");
            dest = input.getUnsignedInt("End vertex? ");
            garbage = (double)input.getUnsignedInt("Garbage quantity? ");
            char bi = input.getChar("Bidirectional (Y/n)? ");
            if(bi == 'n') m_currentGraph.addEdge(src,dest,garbage);
            else m_currentGraph.addEdgeBi(src,dest,garbage);
        }
        else if(choice == options++)
        {
            int src,dest,dist;
            src = input.getUnsignedInt("Start vertex? ");
            dest = input.getUnsignedInt("End vertex? ");
            dist = input.getUnsignedInt("New distance? ");
            m_currentGraph.changeEdge(src, dest, dist);
        }
        else if(choice == options++)
        {
            int ID;
            ID = input.getUnsignedInt("ID? ");
            m_currentGraph.removeVertex(ID);
        }
        else if(choice == options++)
        {
            int src,dest;
            src = input.getUnsignedInt("Start vertex? ");
            dest = input.getUnsignedInt("End vertex? ");
            m_currentGraph.removeEdge(src, dest);
        }
        else if(choice == options++)
        {
            m_currentGraph.setStart(input.getUnsignedInt("New start? "));
        }
        else if(choice == options++)
        {
            m_currentGraph.setEnd(input.getUnsignedInt("New end? "));
        }
        else if(choice == options++)
        {
            saveGraph(input.getString("Graph name? "), m_currentGraph);
        }
        else if(choice == options++)
        {
            loadGraph(input.getString("Graph name? "), m_currentGraph);
        }
        else if(choice == options++)
        {
            break;
        }
    }
}

void Program::truckMenu()
{
    while(true)
    {
        int options = 1;
        input.clear();
        std::cout << "Lixo e Caixotes LDA\n\n";
        std::cout << "+------------+\n";
        std::cout << "| Truck Menu |\n";
        std::cout << "+------------+\n";
        std::cout << "| Garbage left: " << m_currentGraph.garbageToCollect() << "\n";
        std::cout << "+------------+\n";
        std::cout << options++ << ". Show trucks\n";
        std::cout << options++ << ". Truck info\n";
        std::cout << options++ << ". Collect all\n";
        std::cout << options++ << ". Add truck\n";
        std::cout << options++ << ". Remove truck\n";
        std::cout << options++ << ". Exit\n";

        int choice = input.getUnsignedInt(" > ");
        options = 1;
        if(choice == options++)
        {
            input.clear();
            showTrucks();
            input.wait("* Press ENTER to continue *\n");
        }
        else if(choice == options++)
        {
            input.clear();
            showTrucks();
            int ID = input.getUnsignedInt("Truck ID? ");
            Truck *t = NULL;
            for(size_t i = 0; i < trucks.size(); i++)
            {
                if(trucks[i].getID() == ID)
                {
                    t = &trucks[i];
                    break;
                }
            }
            /*
             * Truck info
             */
            if(t != NULL)
            {
                while(true)
                {
                    int options2 = 1;
                    input.clear();
                    std::cout << *t << "\n";
                    std::cout << options2++ << ". Collect\n";
                    std::cout << options2++ << ". Change capacity\n";
                    std::cout << options2++ << ". Return to central\n";
                    std::cout << options2++ << ". Exit\n";

                    int choice2 = input.getUnsignedInt(" > ");
                    options2 = 1;

                    if(choice2 == options2++)
                    {
                        if(!t->hasCollected())
                        {
                            m_currentGraph.findAllPaths(m_currentGraph.getStart(), m_currentGraph.getEnd());
                            Path* best = &m_currentGraph.findLongestPath(t->getCapacity());
                            if(best == NULL)
                            {
                                std::cerr << "No available paths for the specified capacity\n";
                                return;
                            }
                            t->setPath(*best);
                            t->collect();
                        }
                    }
                    else if(choice2 == options2++)
                    {
                        int newCapacity = input.getUnsignedInt("New Capacity? ");
                        t->setCapacity(newCapacity);
                    }
                    else if(choice2 == options2++)
                    {
                        t->reset();
                    }
                    else if(choice2 == options2++)
                    {
                        break;
                    }

                }
            }
        }
        else if(choice == options++)
        {
            input.clear();
            collectAll();
            input.wait("* Press ENTER to continue *\n");
        }
        else if(choice == options++)
        {
            input.clear();
            int capacity = input.getUnsignedInt("Truck capacity? ");
            trucks.push_back(capacity);
            std::cout << trucks.back() << "\n";
            input.wait("* Press ENTER to continue *\n");
        }
        else if(choice == options++)
        {
            input.clear();
            showTrucks();
            int ID = input.getUnsignedInt("Truck ID? ");
            for(size_t i = 0; i < trucks.size(); i++)
            {
                if(trucks[i].getID() == ID)
                {
                    trucks.erase(trucks.begin()+i);
                    break;
                }
            }
            input.wait("* Press ENTER to continue *\n");
        }
        else if(choice == options++)
        {
            return;
        }
    }
}

void Program::collectAll()
{
    int trucksUsed = 0;
    while(m_currentGraph.garbageToCollect() > 0)
    {
        if(trucksUsed >= (int)trucks.size())
            break;
        // trucks.push_back(Truck(DEFAULT_CAPACITY));

        Truck &t = trucks[trucksUsed];
        m_currentGraph.findAllPaths(m_currentGraph.getStart(), m_currentGraph.getEnd());
        Path* best = &m_currentGraph.findLongestPath(t.getCapacity());
        if(best == NULL)
        {
            std::cerr << "No available paths for the specified capacity\n";
            return;
        }
        t.setPath(*best);

        t.collect();
        ++trucksUsed;
    }
}

void Program::showTrucks()
{
    if(trucks.empty())
    {
        std::cout << "No trucks available\n";
        return;
    }
    std::cout << "+---------------\n";
    for(size_t i = 0; i < trucks.size(); i++)
    {
        std::cout << trucks[i] << "\n";
        std::cout << "+---------------\n";
    }
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
            if(buffer[0] == '-')
            {
                getline(loadFile, buffer);
                std::stringstream ss(buffer);
                int start, end;
                ss >> start >> end;
                emptyGraph.setStart(start);
                emptyGraph.setEnd(end);
            }
            else if(buffer == "V:")
            {
                getline(loadFile, buffer);
                std::stringstream ss(buffer);
                ss >> v_currID;
            }
            else{
                std::stringstream ss(buffer);
                int e_destID, e_distance;
                bool bi;
                ss >> e_destID >> e_distance >> bi;
                if(bi)
                    emptyGraph.addEdgeBi(v_currID, e_destID, e_distance);
                else
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

void Program::saveGraph(const std::string& Filename, Graph& graph)
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
                saveFile << adj[j].getDestID() << " " << adj[j].getDistance() << " " << adj[j].getBidirectional() << "\n";
            }
        }
        saveFile << "----------\n";
        saveFile << graph.getStart() << " " << graph.getEnd() << "\n";
    }
    else throw "Couldn't write to " + filePath + "\n";
    saveFile.close();
}
