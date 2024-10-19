
#include "DoganStructureType.h"
#include "DoganExceptions.h"

StructureType DoganStructureType::fromInt(std::size_t i) {
  switch (i) {
  case 0:
    return StructureType::VILLAGE;
  case 1:
    return StructureType::CITY;
  case 2:
    return StructureType::ROAD;
  default:
    throw InvalidTypeException("Error: Invalid Structure Type");
  }
}
std::size_t DoganStructureType::toInt(StructureType t) {
  switch (t) {
  case StructureType::VILLAGE:
    return 0;
  case StructureType::CITY:
    return 1;
  case StructureType::ROAD:
    return 2;
  default:
    throw InvalidTypeException("Error: Invalid Structure Type");
  }
}