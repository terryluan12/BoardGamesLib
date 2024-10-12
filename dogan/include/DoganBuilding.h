#pragma once

#include <memory>
#include <vector>
#include "DoganCell.h"


enum class BuildingType {
    VILLAGE,
    CITY
};

class DoganBuilding {
    public: 
        void addVertex(Vertex &v, DoganCell &dc);
        void setType(BuildingType t);
        void setPlayerID(int pid);
    private:
        int playerID;
        BuildingType buildingType;
        std::vector<std::pair<Vertex, DoganCell>> vertices;

};