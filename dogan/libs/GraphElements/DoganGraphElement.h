#pragma once

#include "Coordinate.h"
#include "enums.h"

class DoganGraphElement {
  public:
  DoganGraphElement(Coordinate2D c, Direction d) : coordinates(c), direction(d) {}
  virtual ~DoganGraphElement() = default;
  Coordinate2D getCoordinate(void) const { return coordinates; };
  Direction getDirection(void) const { return direction; };
  inline bool operator==(const DoganGraphElement &dge) const {
    return coordinates == dge.coordinates && direction == dge.direction;
  };
  bool operator<(const DoganGraphElement &c) const {
    if(coordinates == c.coordinates) {
      return coordinates < c.coordinates;
    }
    else {
      return direction < c.direction;
    }
  }
  protected:
    Coordinate2D coordinates;
    Direction direction;
};