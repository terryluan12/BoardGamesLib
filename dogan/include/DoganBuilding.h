#pragma once

#include "DoganVertex.h"
#include <vector>


enum class BuildingType {
    VILLAGE,
    CITY
};

template <BuildingType T>
class DoganBuilding {
    public:
        DoganBuilding(int pid=-1) : playerID(pid) {};
        void addVertex(DoganVertex &dv);
        void setPlayerID(int pid);
    private:
        int playerID;
        std::vector<DoganVertex> vertices;

};

#include "DoganBuilding.tpp"