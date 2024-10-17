#include "DoganStructure.h"

void DoganRoad::addEdge(DoganEdge de) {
  edges.push_back(de);
}

void DoganRoad::setPlayerID(int pid) { playerID = pid; }