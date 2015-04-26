#include "path.h"

#include <sstream>

void Path::clear()
{
    for(size_t i = 0; i < m_vertices.size(); i++)
    {
        if(i == m_vertices.size()-1) break;

        Edge& e = m_vertices[i]->getEdge(m_vertices[i+1]->getID());
        if(e.getDestID() == -1 && e.getDistance() == -1) delete(&e);
        else e.setDistance(0);

        Edge& e2 = m_vertices[i+1]->getEdge(m_vertices[i]->getID());
        if(e2.getDestID() == -1 && e2.getDistance() == -1) delete(&e2);
        else e2.setDistance(0);
    }
}

bool Path::hasVertex(int ID)
{
    for(size_t i = 0; i < m_vertices.size(); i++)
        if(m_vertices[i]->getID() == ID) return true;

    return false;
}

std::string Path::getPathString() const
{
    std::ostringstream ss;
    for(size_t i = 0; i < m_vertices.size(); i++)
    {
        ss << "(" << m_vertices[i]->getID() << ")";
        if(i != m_vertices.size()-1)
            ss << " --" << m_vertices[i]->getEdge(m_vertices[i+1]->getID()).getDistance() << "--> ";
    }

    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Path& p)
{
    os << "Cost: " << p.getCost() << " | " << p.getPathString();
    return os;
}

bool Path::operator< (const Path &p2) {return this->m_cost < p2.getCost();
}

bool Path::operator== (const Path &p2) {return this->m_cost == p2.getCost();}

/*
 * +---------+
 * | Private |
 * +---------+
 */

int Path::calcCost()
{
    int f_cost = 0;
    for(size_t i = 0; i < m_vertices.size(); i++)
    {
        if(i == m_vertices.size()-1) break;

        Edge e = m_vertices[i]->getEdge(m_vertices[i+1]->getID());
        if(e.getDestID() == -1 && e.getDistance() == -1) delete(&e);
        else f_cost += e.getDistance();

    }

    return f_cost;
}
