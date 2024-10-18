#include "DoganEdge.h"
#include <stdexcept>

DoganEdge::DoganEdge(Coordinate2D c, Direction d) : DoganGraphElement(c, d) {
  if (d == Direction::NORTH || d == Direction::SOUTH) {
    throw std::invalid_argument("Error: Direction::NORTH and Direction::SOUTH "
                                "are invalid directions for edges");
  }
}

DoganEdge DoganEdge::getCorrespondingEdge(void) {
  const Direction oppositeDirection =
      AxialHexDirection::getOppositeDirection(direction);
  const Coordinate2D oppositeCoordinate =
      AxialHexDirection::toCoordinate(direction);
  return DoganEdge(this->coordinates + oppositeCoordinate, oppositeDirection);
};