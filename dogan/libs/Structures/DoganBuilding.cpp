#include "DoganBuilding.h"
#include <cassert>
DoganBuilding::DoganBuilding(int pid, StructureType t)
    : DoganStructure(t) {
  playerID = pid;
  if (t == StructureType::ROAD || t == StructureType::PORT) {
    throw InvalidTypeException("Error: Invalid Building Type");
  }
};
void DoganBuilding::upgradeToCity(void) {
  if (this->type == StructureType::CITY) {
    throw InvalidTypeException("Error: Already a City");
  }
  this->type = StructureType::CITY;
}

int DoganBuilding::getWorth() {
  switch (this->type) {
  case StructureType::VILLAGE:
    return 1;
  case StructureType::CITY:
    return 2;
  default:
    throw InvalidTypeException("Error: Invalid Building Type");
  }
}