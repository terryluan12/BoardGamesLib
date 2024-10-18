#include "DoganBuilding.h"
#include <cassert>

DoganBuilding::DoganBuilding(int pid, StructureType t, DoganVertex dv)
    : DoganStructure(pid, t) {
  if (t == StructureType::ROAD) {
    throw InvalidTypeException("Error: Invalid Building Type");
  }
  graphElements.push_back(std::make_shared<DoganVertex>(dv));
  addCorrespondingVertices();
};
int DoganBuilding::getWorth() {
  switch(this->type) {
    case StructureType::VILLAGE:
      return 1;
    case StructureType::CITY:
      return 2;
    default:
      throw InvalidTypeException("Error: Invalid Building Type");
  }
}

void DoganBuilding::addCorrespondingVertices(void) {
  assert((this->graphElements.size() == 1));
  std::shared_ptr<DoganVertex> dv =
      std::dynamic_pointer_cast<DoganVertex>(graphElements[0]);
  auto corrVertices = dv->getCorrespondingVertices();
  for (auto &v : corrVertices) {
    graphElements.push_back(std::make_shared<DoganVertex>(v));
  }
}