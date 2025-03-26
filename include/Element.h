#pragma once

#include "AxialDirection.h"
#include "Coordinate.h"
class Element {
public:
  virtual ~Element() = default;
  const Coordinate2D getCoordinate(void) const { return coordinate; }

  const HexDirection getDirection(void) const { return direction; }

  bool operator==(const Element &other) const {
    return this->coordinate == other.coordinate &&
           this->direction == other.direction;
  }

  bool operator<(const Element &other) const {
    if (this->coordinate != other.coordinate) {
      return this->coordinate < other.coordinate;
    } else {
      return this->direction < other.direction;
    }
  }

protected:
  Element(Coordinate2D c, HexDirection d) : coordinate(c), direction(d){};

  Coordinate2D coordinate;
  HexDirection direction;
};
