#pragma once

#include "Coordinate.h"
#include "enums.h"
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class DoganCell {
public:
  DoganCell(bool cr, Coordinate2D c, int n, ResourceType t);
  Coordinate2D getCoordinate(void) const;
  ResourceType getResource(void) const;

  friend std::ostream &operator<<(std::ostream &os, DoganCell const &dc);

private:
  Coordinate2D coordinate;
  ResourceType type;
};