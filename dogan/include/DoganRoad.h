#pragma once

#include <memory>
#include <vector>
#include "enums.h"
#include "DoganCell.h"

typedef std::tuple<Direction, std::shared_ptr<DoganCell>> Edge;

class DoganRoad {

    public: 
        void addEdge(Edge e);
        void setPlayerID(int pid);
    private:
        int playerID;
        std::vector<Edge> edges;
};