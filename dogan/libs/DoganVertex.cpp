#include "DoganVertex.h"
#include <stdexcept>

DoganVertex::DoganVertex(Direction d, Coordinate2D c)
    : direction(d), coordinate(c) {
  if (d == Direction::EAST || d == Direction::WEST) {
    throw std::invalid_argument("Error: Direction::EAST and Direction::WEST "
                                "are invalid directions for edges");
  }
}

std::vector<DoganVertex> DoganVertex::getCorrespondingVertices(void) {
  std::vector<DoganVertex> corrVertices;
  auto [d1, d2] = HexagonalDirection::getComplementaryDirections(direction);
  Direction dc1Dir =
      (direction == Direction::NORTH || direction == Direction::SOUTH)
          ? HexagonalDirection::getOppositeDirection(d1)
          : direction;
  Direction dc2Dir = HexagonalDirection::getOppositeDirection(d2);

  corrVertices.emplace_back(DoganVertex(
      d1, this->coordinate + HexagonalDirection::toCoordinate(dc1Dir)));
  corrVertices.emplace_back(DoganVertex(
      d2, this->coordinate + HexagonalDirection::toCoordinate(dc2Dir)));
  return corrVertices;
}

Coordinate2D DoganVertex::getCoordinate(void) const { return coordinate; }

Direction DoganVertex::getDirection(void) const { return direction; }

std::ostream &operator<<(std::ostream &os, DoganVertex const &dv) {
  os << "Vertex" << dv.getCoordinate() << ": " << dv.getDirection();
  return os;
}