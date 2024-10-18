#include "DoganVertex.h"
#include <stdexcept>
DoganVertex::DoganVertex(Coordinate2D c, Direction d)
    : DoganGraphElement(c, d) {
  if (d == Direction::EAST || d == Direction::WEST) {
    throw std::invalid_argument("Error: Direction::EAST and Direction::WEST "
                                "are invalid directions for edges");
  }
}

std::vector<DoganVertex> DoganVertex::getCorrespondingVertices(void) {
  std::vector<DoganVertex> corrVertices;
  auto [d1, d2] = AxialHexDirection::getComplementaryDirections(direction);
  Direction dc1Dir =
      (direction == Direction::NORTH || direction == Direction::SOUTH)
          ? AxialHexDirection::getOppositeDirection(d1)
          : direction;
  Direction dc2Dir = AxialHexDirection::getOppositeDirection(d2);

  corrVertices.emplace_back(DoganVertex(
      this->coordinates - AxialHexDirection::toCoordinate(dc1Dir), d1));
  corrVertices.emplace_back(DoganVertex(
      this->coordinates + AxialHexDirection::toCoordinate(dc2Dir), d2));
  return corrVertices;
}
