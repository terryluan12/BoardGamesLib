#include "enums.h"
#include "DoganExceptions.h"
namespace Dogan {

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
std::ostream &operator<<(std::ostream &os, ResourceType const &rt) {
  switch (rt) {
  case ResourceType::STONE:
    os << "Stone";
    break;
  case ResourceType::WOOD:
    os << "Wood";
    break;
  case ResourceType::WHEAT:
    os << "Wheat";
    break;
  case ResourceType::SHEEP:
    os << "Sheep";
    break;
  case ResourceType::BRICK:
    os << "Brick";
    break;
  case ResourceType::OTHER:
    os << "Other";
    break;
  }
  return os;
}
std::ostream &operator<<(std::ostream &os, DevelopmentType const &dt) {
  switch (dt) {
  case DevelopmentType::VICPOINT:
    os << "Victory Point";
    break;
  case DevelopmentType::MONOPOLY:
    os << "Monopoly";
    break;
  case DevelopmentType::SOLDIER:
    os << "Soldier";
    break;
  case DevelopmentType::BUILDROAD:
    os << "Build Road";
    break;
  case DevelopmentType::TAKETWO:
    os << "Take Two";
    break;
  case DevelopmentType::OTHER:
    os << "Other";
    break;
  }
  return os;
}
std::ostream &operator<<(std::ostream &os, StructureType const &st) {
  switch (st) {
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
  }
  return os;
}
} // namespace Dogan