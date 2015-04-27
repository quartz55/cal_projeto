#ifndef PATH_H
#define PATH_H

#include "vertex.h"
#include <vector>
#include <string>
#include <iostream>

class Path
{
private:
    std::vector<Vertex*> m_vertices;
    int m_cost;

public:

    Path():m_cost(-1){}
    Path(std::vector<Vertex*> vertices):m_vertices(vertices){
        m_cost = calcCost();
    }
    Path(std::vector<Vertex*> vertices, int cost):m_vertices(vertices), m_cost(cost){}

    void addVertex(Vertex& v){m_vertices.push_back(&v);}
    Vertex& last(){return *m_vertices.back();}
    void pop(){m_vertices.pop_back();}

    void clear();
    bool hasVertex(int ID);
    std::string getPathString() const;
    int calcCost();
    friend std::ostream& operator<<(std::ostream& os, const Path& p);
    bool operator< (const Path &p2) const;
    bool operator> (const Path &p2) const ;
    bool operator== (const Path &p2) const;

    /*
     * Gets and sets
     */
    const std::vector<Vertex*> getVertices() const {return m_vertices;}
    void setVertices(std::vector<Vertex*> vertices) {this->m_vertices = vertices;}
    int getCost() const {return m_cost;}
    void setCost(const int cost) {this->m_cost = cost;}

};

#endif
