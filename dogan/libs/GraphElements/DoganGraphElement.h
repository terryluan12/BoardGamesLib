#pragma once

#include "Coordinate.h"
#include "enums.h"

class DoganGraphElement {
  public:
  DoganGraphElement(Coordinate2D c, Direction d) : coordinate(c), direction(d) {}
  Coordinate2D getCoordinate(void) { return coordinate; };
  Direction getDirection(void) { return direction; };
  protected:
    Coordinate2D coordinate;
    Direction direction;
};