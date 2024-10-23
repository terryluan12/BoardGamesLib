#include "ElementHelpers.h"
#include <stdexcept>

namespace Dogan {
std::array<std::pair<Direction, Direction>, 3>
getAllVertexRepresentations(Direction d) {
  std::array<std::pair<Direction, Direction>, 3> corrVertices{};
  corrVertices[0] = {Direction::NONE, d};
  if (d == Direction::EAST || d == Direction::WEST) {
    throw std::invalid_argument("Error: Direction::EAST and Direction::WEST "
                                "are invalid directions for vertices");
  }
  
  auto [travelDir1, target1Dir, travelDir2, target2Dir] = AxialHexDirection::getComplementaryDirections(d);
  corrVertices[1] = {travelDir1, target1Dir};
  corrVertices[2] = {travelDir2, target2Dir};
  return corrVertices;
}

std::array<std::pair<Direction, Direction>, 2>
getAllEdgeRepresentations(Direction d) {
  if (d == Direction::NORTH || d == Direction::SOUTH) {
    throw std::invalid_argument("Error: Direction::NORTH and Direction::SOUTH "
                                "are invalid directions for edges");
  }
  const Direction targetDirection =
      AxialHexDirection::getOppositeDirection(d);
  return {{{Direction::NONE, d}, {d, targetDirection}}};
};
} // namespace Dogan