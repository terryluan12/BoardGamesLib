#include "DoganEdge.h"
#include <stdexcept>

DoganEdge::DoganEdge(Coordinate2D c, Direction d) : DoganGraphElement(c, d) {
  if (d == Direction::NORTH || d == Direction::SOUTH) {
    throw std::invalid_argument("Error: Direction::NORTH and Direction::SOUTH "
                                "are invalid directions for edges");
  }
}

DoganEdge::DoganEdge(Coordinate2D c, std::string d)
    : DoganGraphElement(c, AxialHexDirection::fromString(d)) {
  Direction direction = AxialHexDirection::fromString(d);
  if (direction == Direction::NORTH || direction == Direction::SOUTH) {
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