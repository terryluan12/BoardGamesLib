#pragma once

#include "CellInterface.h"
#include "Coordinate.h"
#include "enums.h"
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class DoganCell : public CellInterface {
public:
  DoganCell(bool cr, Coordinate2D c, int n, ResourceType t);
  friend std::ostream &operator<<(std::ostream &os, DoganCell const &dc);
  Coordinate2D getCoordinate(void) const;
  ResourceType getResource(void) const;
  int getNumber(void) const;
  bool hasRobber(void) const;
  void setRobber(bool robber);

private:
  bool containsRobber;
  Coordinate2D coordinate;
  int number;
  ResourceType type;
};