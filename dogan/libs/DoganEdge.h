#pragma once

#include "Coordinate.h"
#include "enums.h"
#include <vector>

class DoganEdge {
public:
  DoganEdge(Direction d, Coordinate2D c);
  DoganEdge getCorrespondingEdge(void);
  Coordinate2D getCoordinate(void);
  Direction getDirection(void);

private:
  Direction direction;
  Coordinate2D coordinate;
};