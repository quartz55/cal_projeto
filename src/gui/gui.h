#ifndef GUI_H
#define GUI_H
#include"graphviewer.h"
#include"connection.h"
#include"../graph/graph.h"

class Gui{
    GraphViewer *gv;
    int width;
    int height;

public:

    Gui(int w, int h)
        {
            this->width = w;
            this->height = h;
            gv = new GraphViewer(width,height,true);
            gv->createWindow(width,height);
            gv->defineVertexColor("blue");
            gv->defineEdgeColor("orange");
        }
    ~Gui()
        {
            gv->closeWindow();
            delete(gv);
        }
    void draw(Graph &g);
    void drawPath(Graph g,Path p);
    int getWidth(){return this->width;}
    int getheight(){return this->height;}

    void guiSleep(int mili);

};

#endif

inline void Gui::guiSleep(int mili)
{
#ifdef linux
    sleep(mili/1000);
#elif defined _WIN32
    Sleep(mili);
#endif
}
