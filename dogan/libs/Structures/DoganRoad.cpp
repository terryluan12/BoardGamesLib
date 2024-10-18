#include "DoganRoad.h"
#include <cassert>
#include <memory>

DoganRoad::DoganRoad(int pid, StructureType t, Coordinate2D c, Direction d)
    : DoganStructure(pid, t) {
  if (t != StructureType::ROAD) {
    throw InvalidTypeException("Error: Invalid Building Type");
  }
  graphElements.push_back(std::make_shared<DoganEdge>(DoganEdge(c, d)));
  addCorrespondingEdge();
}

void DoganRoad::addCorrespondingEdge(void) {
  assert((graphElements.size() == 1));

  std::shared_ptr<DoganEdge> de =
      std::dynamic_pointer_cast<DoganEdge>(graphElements[0]);
  graphElements.push_back(
      std::make_shared<DoganEdge>(de->getCorrespondingEdge()));
}
