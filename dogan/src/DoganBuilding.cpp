#include <stdexcept>
#include "DoganBuilding.h"
#include "Cell.h"
#include "enums.h"


void DoganBuilding::addVertex(Vertex v) {
    auto [d, dc] = v;
    vertices.push_back(v);
    auto [d1, d2] = getComplementDirections(d);
    
    if(d == Direction::NORTH || d == Direction::SOUTH) {
        Vertex v1 = std::make_tuple(d1, dc->getAdjacentCell(getOppositeDirection(d1)));
        Vertex v2 = std::make_tuple(d2, dc->getAdjacentCell(getOppositeDirection(d2)));
        vertices.push_back(v1);
        vertices.push_back(v2);
    }
    else {
        Vertex v1 = std::make_tuple(d1, dc->getAdjacentCell(d));
        Vertex v2 = std::make_tuple(d2, dc->getAdjacentCell(getOppositeDirection(d2)));
        vertices.push_back(v1);
        vertices.push_back(v2);
    }
}

void DoganBuilding::setType(BuildingType t) {
    buildingType = t; 
}
void DoganBuilding::setPlayerID(int pid) {
    playerID = pid;
}