#include "DoganRoad.h"
#include <cassert>
#include <memory>

DoganRoad::DoganRoad(int pid, DoganEdge de)
    : DoganStructure(StructureType::ROAD) {
  playerID = pid;
  graphElements.push_back(std::make_shared<DoganEdge>(de));
  addCorrespondingEdge();
}

void DoganRoad::addCorrespondingEdge(void) {
  assert((graphElements.size() == 1));

  std::shared_ptr<DoganEdge> de =
      std::dynamic_pointer_cast<DoganEdge>(graphElements[0]);
  graphElements.push_back(
      std::make_shared<DoganEdge>(de->getCorrespondingEdge()));
}
