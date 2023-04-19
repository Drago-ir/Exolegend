#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "MazeStore.h"
#include "Node.h"

class Simulator
{   
    public: 
        Node node;
        bool verbose;
    public :
        Simulator(const char *paramMaze, int paramGasInterval, bool paramVerbose);
        bool iterate(int selectedChildIndex);
};

#endif