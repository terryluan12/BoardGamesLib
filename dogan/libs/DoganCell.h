#pragma once

#include "CellInterface.h"
#include "Coordinate.h"
#include "DoganEdge.h"
#include "DoganVertex.h"
#include "enums.h"
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class DoganCell : public CellInterface {
public:
  DoganCell(bool cr, Coordinate2D c, int n, ResourceType t);
  void addAdjacentCell(const Direction d, std::shared_ptr<DoganCell> ac);
  std::shared_ptr<DoganCell> getAdjacentCell(Direction d);
  Coordinate2D getCoordinate(void) const;
  ResourceType getResource(void) const;
  int getNumber(void) const;
  bool hasRobber(void) const;
  void setRobber(bool robber);
  bool hasAdjacentCell(Direction d) const;

private:
  std::unordered_map<Direction, std::shared_ptr<class DoganCell>> adjacentCells;
  static std::unordered_set<Coordinate2D> allCoordinates;
  bool containsRobber;
  Coordinate2D coordinate;
  int number;
  ResourceType type;
};

std::ostream &operator<<(std::ostream &os, DoganCell const &dc);