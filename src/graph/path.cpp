#include "path.h"

#include <sstream>

bool Path::hasVertex(int ID)
{
    for(size_t i = 0; i < m_vertices.size(); i++)
        if(m_vertices[i].getID() == ID) return true;

    return false;
}

std::string Path::getPathString() const
{
    std::ostringstream ss;
    for(size_t i = 0; i < m_vertices.size(); i++)
    {
        if(i == m_vertices.size()-1)
            ss <<  m_vertices[i].getID();
        else ss << m_vertices[i].getID() << " -> ";
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

        for(std::vector<Edge>::const_iterator adj_it = m_vertices[i].getAdj().begin();
            adj_it != m_vertices[i].getAdj().end();
            adj_it++)
        {
            if((*adj_it).getDestID() == m_vertices[i+1].getID())
            {
                f_cost += (*adj_it).getDistance();
                break;
            }
        }
    }

    return f_cost;
}
