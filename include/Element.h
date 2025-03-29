#pragma once

#include "AxialDirection.h"
#include "Coordinate.h"
class Element {
public:
  virtual ~Element() = default;
  const Coordinate2D getCoordinate(void) const { return coordinate; }

  const HexDirection getDirection(void) const { return direction; }

  bool operator==(const Element &other) const;

  bool operator<(const Element &other) const;

protected:
  Element(Coordinate2D c, HexDirection d) : coordinate(c), direction(d){};

  Coordinate2D coordinate;
  HexDirection direction;
};
