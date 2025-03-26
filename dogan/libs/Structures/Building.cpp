#include "Building.h"
#include <cassert>

namespace Dogan {
Building::Building(int pid, StructureType t, Coordinate2D c, HexDirection d)
    : Structure(t, pid), location(Vertex(c, d)) {
  if (t == StructureType::ROAD) {
    throw InvalidTypeException("Error: Invalid Building Type");
  }
};
void Building::upgradeToCity(void) {
  this->structureType = StructureType::CITY;
}

int Building::getWorth() const {
  switch (this->structureType) {
  case StructureType::VILLAGE:
    return 1;
  case StructureType::CITY:
    return 2;
  default:
    throw InvalidTypeException("Error: Invalid Building Type");
  }
}

bool Building::operator==(const Building &other) const {
  return this->location == other.location &&
         this->structureType == other.structureType;
}
bool Building::operator<(const Building &other) const {
  if (this->location != other.location) {
    return this->structureType < other.structureType;
  }
  return this->location < other.location;
}

} // namespace Dogan