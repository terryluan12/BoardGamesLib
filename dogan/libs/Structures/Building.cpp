#include "Building.h"
#include <cassert>

namespace Dogan {
Building::Building(int pid, StructureType t) : Structure(t) {
  playerID = pid;
  if (t == StructureType::ROAD || t == StructureType::PORT) {
    throw InvalidTypeException("Error: Invalid Building Type");
  }
};
void Building::upgradeToCity(void) {
  if (this->type == StructureType::CITY) {
    throw InvalidTypeException("Error: Already a City");
  }
  this->type = StructureType::CITY;
}

int Building::getWorth() const {
  switch (this->type) {
  case StructureType::VILLAGE:
    return 1;
  case StructureType::CITY:
    return 2;
  default:
    throw InvalidTypeException("Error: Invalid Building Type");
  }
}
} // namespace Dogan