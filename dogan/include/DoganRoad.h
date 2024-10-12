#pragma once

#include <memory>
#include <utility>
#include <vector>
#include "enums.h"
#include "DoganCell.h"


class DoganRoad {

    public: 
        void addEdge(Edge &e, DoganCell &dc);
        void setPlayerID(int pid);
    private:
        int playerID;
        std::vector<std::pair<Edge, DoganCell>> edges;
};