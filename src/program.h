#ifndef PROGRAM_H
#define PROGRAM_H

#include "./graph/graph.h"
#include "./gui/gui.h"
#include "truck.h"

#include <vector>

const std::string GRAPHS_SAVE_PATH = "./graphs/";
const std::string GRAPHS_EXTENSION =".graph";

class Program
{
private:
    Graph m_currentGraph;
    // Gui m_gui;
    std::vector<Truck> trucks;

    void collectAll();

    bool start();
    bool exit();
    bool loadGraph(const std::string& Filename, Graph& emptyGraph);
    void saveGraph(const std::string& Filename, Graph graph);
public:
    Program();
};

#endif
