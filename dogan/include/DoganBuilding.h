#pragma once

#include <memory>
#include <vector>
#include "DoganCell.h"
#include "DoganVertex.h"


enum class BuildingType {
    VILLAGE,
    CITY
};

class DoganBuilding {
    public: 
        void addVertex(DoganVertex &dv);
        void setType(BuildingType t);
        void setPlayerID(int pid);
    private:
        int playerID;
        BuildingType buildingType;
        std::vector<DoganVertex> vertices;

};