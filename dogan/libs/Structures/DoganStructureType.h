#pragma once

#include <cstddef>
#include <ostream>

class DoganStructureType {
public:
  enum class StructureType { VILLAGE = 0, CITY = 1, ROAD = 2, PORT = 3 };
  static StructureType fromInt(std::size_t i);
  static size_t toInt(StructureType t);
};

using StructureType = DoganStructureType::StructureType;
std::ostream &operator<<(std::ostream &os, StructureType const &dp);