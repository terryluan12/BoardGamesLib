#include "DoganStructure.h"

template <StructureType T>
void DoganBuilding<T>::addVertex(DoganVertex &dv) {
    vertices.push_back(dv);
    auto corrVertices = dv.getCorrespondingVertices();
    vertices.insert(vertices.end(), std::make_move_iterator(corrVertices.begin()), std::make_move_iterator(corrVertices.end()));
}

template <StructureType T>
void DoganBuilding<T>::setPlayerID(int pid) {
    playerID = pid;
}