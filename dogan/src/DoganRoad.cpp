#include "DoganRoad.h"

void DoganRoad::addEdge(DoganEdge de){
    edges.push_back(de);
    auto corrEdge = de.getCorrespondingEdge();
    edges.insert(edges.end(), std::make_move_iterator(corrEdge.begin()), std::make_move_iterator(corrEdge.end()));
};

void DoganRoad::setPlayerID(int pid) {
    playerID = pid;
}