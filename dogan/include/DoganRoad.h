#pragma once

#include <vector>
#include "DoganEdge.h"

class DoganRoad {

    public: 
        void addEdge(DoganEdge de, DoganCell &dc);
        void setPlayerID(int pid);
    private:
        int playerID;
        std::vector<DoganEdge> edges;
};