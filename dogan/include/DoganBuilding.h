#pragma once

#include <memory>
#include <vector>
#include "DoganCell.h"

typedef std::tuple<Direction, std::shared_ptr<DoganCell>> Vertex;

enum class BuildingType {
    VILLAGE,
    CITY
};

class DoganBuilding {
    public: 
        void addVertex(Vertex v);
        void setType(BuildingType t);
        void setPlayerID(int pid);
    private:
        int playerID;
        BuildingType buildingType;
        std::vector<Vertex> vertices;

};