#pragma once

#include <cstddef>

class DoganStructureType {
public:
  enum class StructureType { VILLAGE = 0, CITY = 1, ROAD = 2 };
  static const size_t NUM_TYPES;
  static StructureType fromInt(std::size_t i);
  static std::size_t toInt(StructureType t);
};

using StructureType = DoganStructureType::StructureType;