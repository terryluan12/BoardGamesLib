#include "DoganBuilding.h"
#include "DoganVertex.h"
#include <cassert>

DoganBuilding::DoganBuilding(int pid, StructureType t, Coordinate2D c, Direction d) : DoganStructure(pid, t) {
    if (t == StructureType::ROAD) {
        throw InvalidTypeException("Error: Invalid Building Type");
    }
    graphElements.push_back(std::make_shared<DoganVertex>(DoganVertex(c, d)));
    addCorrespondingVertices();
};

void DoganBuilding::addCorrespondingVertices(void) {
  assert((this->graphElements.size() == 1));
  std::shared_ptr<DoganVertex> dv = std::dynamic_pointer_cast<DoganVertex>(graphElements[0]);
  auto corrVertices = dv->getCorrespondingVertices();
  for(auto &v : corrVertices) {
    graphElements.push_back(std::make_shared<DoganVertex>(v));
  }
}