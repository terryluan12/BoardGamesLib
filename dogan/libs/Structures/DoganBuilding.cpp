#include "DoganBuilding.h"
#include <cassert>

DoganBuilding::DoganBuilding(int pid, StructureType t, Coordinate2D c, Direction d) : DoganStructure(pid, t), graphElements{{c, d}} {
    if ( t == StructureType::ROAD) {
        throw InvalidTypeException("Error: Invalid Building Type");
    }
    addCorrespondingVertices();
};

void DoganBuilding::addCorrespondingVertices(void) {
  assert((this->graphElements.size() == 1));
  auto corrVertices = this->graphElements[0].getCorrespondingVertices();
  graphElements.insert(graphElements.end(), std::make_move_iterator(corrVertices.begin()),
                  std::make_move_iterator(corrVertices.end()));
}