#pragma once

#include "Coordinate.h"
#include "enums.h"

class DoganVertex {
public:
  DoganVertex(Direction d, Coordinate2D c);
  friend std::ostream &operator<<(std::ostream &os, DoganVertex const &dv);
  std::vector<DoganVertex> getCorrespondingVertices(void);
  Coordinate2D getCoordinate(void) const;
  Direction getDirection(void) const;

private:
  Direction direction;
  Coordinate2D coordinate;
};