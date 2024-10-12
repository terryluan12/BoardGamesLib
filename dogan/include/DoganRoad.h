#pragma once

#include <memory>
#include <utility>
#include <vector>
#include "enums.h"
#include "DoganCell.h"
#include "DoganEdge.h"

class DoganRoad {

    public: 
        void addEdge(DoganEdge de);
        void setPlayerID(int pid);
    private:
        int playerID;
        std::vector<DoganEdge> edges;
};