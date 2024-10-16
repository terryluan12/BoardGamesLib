#pragma once

#include "Coordinate.h"
#include "DoganCell.h"
#include "direction.enum.h"

class Vertex {
public:
  Vertex(Direction d, Coordinate2D c);
  std::vector<DoganVertex> getCorrespondingVertices(void);
  Coordinate2D getCoordinate(void) const;
  Direction getDirection(void) const;

private:
  Direction direction;
  Coordinate2D coordinate;
};
std::ostream &operator<<(std::ostream &os, DoganVertex const &dc);