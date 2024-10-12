#include <stdexcept>
#include "DoganBuilding.h"
#include "Cell.h"
#include "enums.h"


void DoganBuilding::addVertex(Vertex &v, DoganCell &dc) {
    auto [d, c] = v;
    if(d == Direction::EAST || d == Direction::WEST) {
        throw std::invalid_argument("Error: Direction::EAST and Direction::WEST are invalid directions for edges");
    }
    
    vertices.push_back(std::make_pair(v, dc));
    auto [d1, d2] = getComplementDirections(d);
    
    auto dc1 = (d == Direction::NORTH || d == Direction::SOUTH) ?
                dc.getAdjacentCell(getOppositeDirection(d1)) :
                dc.getAdjacentCell(d);
    auto dc2 = dc.getAdjacentCell(getOppositeDirection(d2));
    
    if (dc1) {
        Vertex v1 = std::make_tuple(d1, dc1->getCoordinate());
        vertices.push_back(std::make_pair(v1, *dc1));
    }
    if (dc2) {
        Vertex v2 = std::make_tuple(d2, dc2->getCoordinate());
        vertices.push_back(std::make_pair(v2, *dc2));
    }
}

void DoganBuilding::setType(BuildingType t) {
    buildingType = t; 
}
void DoganBuilding::setPlayerID(int pid) {
    playerID = pid;
}