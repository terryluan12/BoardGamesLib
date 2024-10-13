#pragma once

#include "DoganVertex.h"
#include <vector>


enum class BuildingType {
    VILLAGE,
    CITY
};

class DoganBuilding {
    public: 
        void addVertex(DoganVertex &dv, DoganCell &dc);
        void setType(BuildingType t);
        void setPlayerID(int pid);
    private:
        int playerID;
        BuildingType buildingType;
        std::vector<DoganVertex> vertices;

};