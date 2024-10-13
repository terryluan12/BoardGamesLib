#pragma once

#include "DoganEdge.h"
#include <vector>

class DoganRoad {

    public: 
        void addEdge(DoganEdge de, DoganCell &dc);
        void setPlayerID(int pid);
    private:
        int playerID;
        std::vector<DoganEdge> edges;
};