#include "DoganStructure.h"

void DoganRoad::addEdge(DoganEdge de, DoganCell &dc) {
  edges.push_back(de);
  auto corrEdge = de.getCorrespondingEdge(dc);
  edges.insert(edges.end(), std::make_move_iterator(corrEdge.begin()),
               std::make_move_iterator(corrEdge.end()));
}

void DoganRoad::setPlayerID(int pid) { playerID = pid; }