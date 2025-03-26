#pragma once

#include "Coordinate.h"
#include "DoganExceptions.h"
#include "Structure.h"
#include "Vertex.h"
#include <vector>

namespace Dogan {
class Building : public Structure {
public:
  Building(int pid, StructureType t, Coordinate2D c, HexDirection d);
  void upgradeToCity(void);
  int getWorth(void) const;
  friend std::ostream &operator<<(std::ostream &os, Building const &dp) {
    os << dp.structureType << "\n";
    return os;
  };
  const Vertex &getLocation(void) const override { return location; };
  bool operator==(const Building &other) const;
  bool operator<(const Building &other) const;

protected:
  ResourceType resource;
  Vertex location;
};
} // namespace Dogan