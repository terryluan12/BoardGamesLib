#include "DoganEdge.h"
#include <stdexcept>

DoganEdge::DoganEdge(Direction d, Coordinate2D c)
    : direction(d), coordinate(c) {
  if (d == Direction::NORTH || d == Direction::SOUTH) {
    throw std::invalid_argument("Error: Direction::NORTH and Direction::SOUTH "
                                "are invalid directions for edges");
  }
}

Coordinate2D DoganEdge::getCoordinate(void) { return coordinate; }

DoganEdge DoganEdge::getCorrespondingEdge(void) {
  const Direction oppositeDirection =
      HexagonalDirection::getOppositeDirection(direction);
  const Coordinate2D oppositeCoordinate =
      HexagonalDirection::toCoordinate(direction);
  return DoganEdge(oppositeDirection, oppositeCoordinate);
};

Direction DoganEdge::getDirection(void) { return direction; }