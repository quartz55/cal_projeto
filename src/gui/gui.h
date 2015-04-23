#ifndef GUI_H
#define GUI_H
#include"graphviewer.h"
#include"connection.h"
#include"../graph/graph.h"

class Gui{
	GraphViewer *gv;


public:

	Gui(){this->gv=gv;}
	void draw(const vector<Vertex> &vertices);

};

#endif
