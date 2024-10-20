#pragma once

#include "AxialHexDirection.h"
#include "common.h"
#include <ostream>

namespace Dogan {
enum class ResourceType {
  WOOD = 0,
  SHEEP = 1,
  WHEAT = 2,
  BRICK = 3,
  STONE = 4,
  OTHER = 5
};
enum class DevelopmentType {
  VICPOINT = 0,
  MONOPOLY = 1,
  SOLDIER = 2,
  BUILDROAD = 3,
  TAKETWO = 4,
  OTHER = 5
};

class DoganStructureType {
public:
  enum class Type { VILLAGE = 0, CITY = 1, ROAD = 2, PORT = 3 };
  static Type fromInt(std::size_t i);
  static size_t toInt(Type t);
};

using StructureType = DoganStructureType::Type;
using Direction = AxialHexDirection::Direction;

std::ostream &operator<<(std::ostream &os, ResourceType const &d);
std::ostream &operator<<(std::ostream &os, DevelopmentType const &d);
std::ostream &operator<<(std::ostream &os, StructureType const &dp);
} // namespace Dogan