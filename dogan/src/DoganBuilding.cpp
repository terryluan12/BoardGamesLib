#include "DoganBuilding.h"


void DoganBuilding::addVertex(DoganVertex &dv, DoganCell &dc) {
    vertices.push_back(dv);
    auto corrVertices = dv.getCorrespondingVertices(dc);
    vertices.insert(vertices.end(), std::make_move_iterator(corrVertices.begin()), std::make_move_iterator(corrVertices.end()));
}

void DoganBuilding::setType(BuildingType t) {
    buildingType = t; 
}
void DoganBuilding::setPlayerID(int pid) {
    playerID = pid;
}