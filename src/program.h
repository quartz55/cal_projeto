#ifndef PROGRAM_H
#define PROGRAM_H

#include "./graph/graph.h"
#include "./gui/gui.h"
#include "truck.h"
#include "input.h"

#include <vector>

const std::string GRAPHS_SAVE_PATH = "./graphs/";
const std::string GRAPHS_EXTENSION =".graph";

class Program
{
private:
    Input input;
    Graph m_currentGraph;
    // Gui m_gui;
    std::vector<Truck> trucks;

    void collectAll();

    bool start();

    void mainMenu();
    void mapMenu();
    void truckMenu();
    void modifyMapMenu();
    void showTrucks();

    bool exit();
    bool loadGraph(const std::string& Filename, Graph& emptyGraph);
    void saveGraph(const std::string& Filename, Graph& graph);

public:
    Program();
};

#endif
