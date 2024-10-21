#include "ElementHelpers.h"
#include <stdexcept>

namespace Dogan {
std::vector<std::pair<Coordinate2D, Direction>>
getAllVertexRepresentations(std::pair<Coordinate2D, Direction> dvp) {
  auto [coordinates, direction] = dvp;
  std::vector<std::pair<Coordinate2D, Direction>> corrVertices{{coordinates, direction}};
  if (direction == Direction::EAST || direction == Direction::WEST) {
    throw std::invalid_argument("Error: Direction::EAST and Direction::WEST "
                                "are invalid directions for edges");
  }
  auto [target1Dir, baseDir1, target2Dir, baseDir2] = AxialHexDirection::getComplementaryDirections(direction);
  auto newCoord1 = coordinates + AxialHexDirection::toCoordinate(baseDir1);
  auto newCoord2 = coordinates + AxialHexDirection::toCoordinate(baseDir2);
  corrVertices.emplace_back(newCoord1, target1Dir);
  corrVertices.emplace_back(newCoord2, target2Dir);
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
} // namespace Dogan