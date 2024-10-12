#include <stdexcept>
#include "DoganBuilding.h"
#include "Cell.h"
#include "enums.h"


void DoganBuilding::addVertex(DoganVertex &dv) {
    vertices.emplace_back(dv);
    auto corrVertices = dv.getCorrespondingVertices();
    vertices.insert(vertices.end(), std::make_move_iterator(corrVertices.begin()), std::make_move_iterator(corrVertices.end()));
}

void DoganBuilding::setType(BuildingType t) {
    buildingType = t; 
}
void DoganBuilding::setPlayerID(int pid) {
    playerID = pid;
}