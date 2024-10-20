#include "DoganElementHelpers.h"
#include <stdexcept>

std::vector<std::pair<Coordinate2D, Direction>>
getAllVertexRepresentations(std::pair<Coordinate2D, Direction> dvp) {
  auto [c, d] = dvp;
  if (d == Direction::EAST || d == Direction::WEST) {
    throw std::invalid_argument("Error: Direction::EAST and Direction::WEST "
                                "are invalid directions for edges");
  }
  std::vector<std::pair<Coordinate2D, Direction>> corrVertices{{c, d}};
  auto [d1, d2] = AxialHexDirection::getComplementaryDirections(d);
  Direction dc1Dir = (d == Direction::NORTH || d == Direction::SOUTH)
                         ? AxialHexDirection::getOppositeDirection(d1)
                         : d;
  Direction dc2Dir = AxialHexDirection::getOppositeDirection(d2);

  Coordinate2D dc1 = c + AxialHexDirection::toCoordinate(dc1Dir);

  corrVertices.emplace_back(dc1, d1);
  corrVertices.emplace_back(dc1 + AxialHexDirection::toCoordinate(dc2Dir), d2);
  return corrVertices;
}

std::vector<std::pair<Coordinate2D, Direction>>
getAllEdgeRepresentations(std::pair<Coordinate2D, Direction> dep) {
  auto [c, d] = dep;
  if (d == Direction::NORTH || d == Direction::SOUTH) {
    throw std::invalid_argument("Error: Direction::NORTH and Direction::SOUTH "
                                "are invalid directions for edges");
  }
  const Direction oppositeDirection =
      AxialHexDirection::getOppositeDirection(d);
  const Coordinate2D oppositeCoordinate = AxialHexDirection::toCoordinate(d);
  return {{c, d}, {c + oppositeCoordinate, oppositeDirection}};
};