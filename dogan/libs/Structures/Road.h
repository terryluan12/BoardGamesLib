#pragma once

#include "Edge.h"
#include "Structure.h"
#include <vector>

namespace Dogan {
class Road : public Structure {
public:
  Road(int pid, Coordinate2D c, HexDirection d)
      : Structure(StructureType::ROAD, pid), location(Edge(c, d)){};
  friend std::ostream &operator<<(std::ostream &os, Road const &dp) {
    os << dp.structureType << "\n";
    return os;
  };

  const Edge &getLocation(void) const override { return location; };

  bool operator==(const Road &other) const {
    return this->location == other.location;
  }
  bool operator<(const Road &other) const {
    return this->location < other.location;
  }

private:
  Edge location;
};
} // namespace Dogan