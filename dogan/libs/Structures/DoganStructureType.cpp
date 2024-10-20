
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
  case 3: 
    return StructureType::PORT;
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
  case StructureType::PORT:
    return 3;
  default:
    throw InvalidTypeException("Error: Invalid Structure Type");
  }
}

std::ostream &operator<<(std::ostream &os, StructureType const &st) {
  switch(st) {
    case StructureType::VILLAGE:
      os << "Village";
      break;
    case StructureType::CITY:
      os << "City";
      break;
    case StructureType::ROAD:
      os << "Road";
      break;
    case StructureType::PORT:
      os << "Port";
      break;
    default:
      throw InvalidTypeException("Error: Invalid Structure Type");
  }
  return os;
}
