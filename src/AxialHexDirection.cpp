#include "AxialHexDirection.h"
#include "Exceptions.h"
#include <algorithm>

using Direction = AxialHexDirection::Direction;

const std::array<Direction, 6> AxialHexDirection::edgeDirections{
    Direction::NORTHWEST, Direction::NORTHEAST, Direction::EAST,
    Direction::SOUTHEAST, Direction::SOUTHWEST, Direction::WEST};
const std::array<Direction, 6> AxialHexDirection::vertexDirections{
    Direction::NORTH, Direction::NORTHEAST, Direction::SOUTHEAST,
    Direction::SOUTH, Direction::SOUTHWEST, Direction::NORTHWEST};
const std::array<Direction, 8> AxialHexDirection::allDirections{
    Direction::NORTH,     Direction::NORTHEAST, Direction::EAST,
    Direction::SOUTHEAST, Direction::SOUTH,     Direction::SOUTHWEST,
    Direction::WEST,      Direction::NORTHWEST};

Direction AxialHexDirection::fromString(std::string d) {
  if (d == "N")
    return Direction::NORTH;
  else if (d == "NE")
    return Direction::NORTHEAST;
  else if (d == "E")
    return Direction::EAST;
  else if (d == "SE")
    return Direction::SOUTHEAST;
  else if (d == "S")
    return Direction::SOUTH;
  else if (d == "SW")
    return Direction::SOUTHWEST;
  else if (d == "W")
    return Direction::WEST;
  else if (d == "NW")
    return Direction::NORTHWEST;
  else
    throw NoSuchDirectionException("Error: Invalid Direction");
}

Coordinate2D AxialHexDirection::toCoordinate(Direction d) {
  switch (d) {
  case Direction::NORTHEAST:
    return {1, -1};
  case Direction::EAST:
    return {1, 0};
  case Direction::SOUTHEAST:
    return {0, 1};
  case Direction::SOUTHWEST:
    return {-1, 1};
  case Direction::WEST:
    return {-1, 0};
  case Direction::NORTHWEST:
    return {0, -1};
  case Direction::NONE:
    return {0, 0};
  default:
    throw std::invalid_argument("Error: Invalid Direction");
  }
}

Direction AxialHexDirection::getOppositeDirection(Direction d) {
  return static_cast<Direction>((static_cast<int>(d) + 4) % 8);
}

std::array<vertexRepresentation, 2>
AxialHexDirection::getComplementaryVertexRepresentations(Direction d) {
  int vertexIndex = getVertexIndex(d);
  Direction firstTravelDirection = edgeDirections[vertexIndex];
  Direction firstDirection = vertexDirections[(vertexIndex + 2) % 6];
  Direction secondTravelDirection = edgeDirections[(vertexIndex + 1) % 6];
  Direction secondDirection = vertexDirections[(vertexIndex + 4) % 6];
  return {{{firstTravelDirection, firstDirection},
           {secondTravelDirection, secondDirection}}};
}

std::array<Direction, 2>
AxialHexDirection::getLocalAdjacentEdgeToEdgeDirections(Direction d) {
  int edgeIndex = getEdgeIndex(d);
  return {edgeDirections[(edgeIndex + 1) % 6],
          edgeDirections[(edgeIndex + 5) % 6]};
}

std::array<edgeRepresentation, 4>
AxialHexDirection::getDistantAdjacentEdgeToEdgeDirections(Direction d) {
  int edgeIndex = getEdgeIndex(d);
  return {{{edgeDirections[edgeIndex], edgeDirections[(edgeIndex + 2) % 6]},
           {edgeDirections[edgeIndex], edgeDirections[(edgeIndex + 4) % 6]},
           {edgeDirections[(edgeIndex + 5) % 6],
            edgeDirections[(edgeIndex + 1) % 6]},
           {edgeDirections[(edgeIndex + 1) % 6],
            edgeDirections[(edgeIndex + 5) % 6]}}};
}

std::array<Direction, 2>
AxialHexDirection::getAdjacentEdgeToVertexDirections(Direction d) {
  if (d == Direction::EAST || d == Direction::WEST) {
    throw std::invalid_argument("Error: Direction::EAST and Direction::WEST "
                                "are invalid directions for vertices");
  }
  int edgeIndex = AxialHexDirection::getVertexIndex(d);
  Direction d1 = AxialHexDirection::edgeDirections[edgeIndex];
  Direction d2 = AxialHexDirection::edgeDirections[(edgeIndex + 1) % 6];
  return {d1, d2};
}

std::array<Direction, 2>
AxialHexDirection::getAdjacentVertexToVertexDirections(Direction d) {
  int vertexIndex = getVertexIndex(d);
  return {vertexDirections[(vertexIndex + 1) % 6],
          vertexDirections[(vertexIndex + 5) % 6]};
}

std::array<vertexRepresentation, 2>
AxialHexDirection::getSecondDegreeVertex(Direction d) {
  if (d == Direction::EAST || d == Direction::WEST) {
    throw std::invalid_argument(
        "Error: Invalid Direction. Vertex Cannot be East or West");
  }
  int vertexIndex = getVertexIndex(d);
  return {
      {{edgeDirections[vertexIndex], vertexDirections[(vertexIndex + 1) % 6]},
       {edgeDirections[(vertexIndex + 1) % 6],
        vertexDirections[(vertexIndex + 5) % 6]}}};
}

std::array<std::array<Direction, 2>, 2>
AxialHexDirection::getEdgeFromVertexDirection(Direction d) {
  if (d == Direction::EAST || d == Direction::WEST) {
    throw std::invalid_argument(
        "Error: Invalid Direction. Vertex Cannot be East or West");
  }
  int vertexIndex = getVertexIndex(d);
  return {{{edgeDirections[vertexIndex], edgeDirections[(vertexIndex + 2) % 6]},
           {edgeDirections[(vertexIndex + 1) % 6],
            edgeDirections[(vertexIndex - 1) % 6]}}};
}

const int AxialHexDirection::getEdgeIndex(Direction d) {
  if (d == Direction::NORTH || d == Direction::SOUTH) {
    throw std::invalid_argument(
        "Error: Invalid Direction. Edge Cannot be North or South");
  }
  auto it = std::find(edgeDirections.begin(), edgeDirections.end(), d);
  return std::distance(edgeDirections.begin(), it);
}

const int AxialHexDirection::getVertexIndex(Direction d) {
  if (d == Direction::EAST || d == Direction::WEST) {
    throw std::invalid_argument(
        "Error: Invalid Direction. Vertex Cannot be East or West");
  }
  auto it = std::find(vertexDirections.begin(), vertexDirections.end(), d);
  return std::distance(vertexDirections.begin(), it);
}

std::array<vertexRepresentation, 3>
AxialHexDirection::getAllVertexRepresentations(Direction d) {
  if (d == Direction::EAST || d == Direction::WEST) {
    throw std::invalid_argument("Error: Direction::EAST and Direction::WEST "
                                "are invalid directions for vertices");
  }

  auto [vertexRepresentation1, vertexRepresentation2] =
      AxialHexDirection::getComplementaryVertexRepresentations(d);
  std::array<vertexRepresentation, 3> corrVertices{{
      {Direction::NONE, d},
      vertexRepresentation1,
      vertexRepresentation2,
  }};
  return corrVertices;
}

std::array<edgeRepresentation, 2>
AxialHexDirection::getAllEdgeRepresentations(Direction d) {
  if (d == Direction::NORTH || d == Direction::SOUTH) {
    throw std::invalid_argument("Error: Direction::NORTH and Direction::SOUTH "
                                "are invalid directions for edges");
  }
  const Direction targetDirection = AxialHexDirection::getOppositeDirection(d);
  return {{{Direction::NONE, d}, {d, targetDirection}}};
};

std::ostream &operator<<(std::ostream &os, Direction const &d) {
  switch (d) {
  case Direction::NORTH:
    os << "North";
    break;
  case Direction::NORTHEAST:
    os << "NorthEast";
    break;
  case Direction::EAST:
    os << "East";
    break;
  case Direction::SOUTHEAST:
    os << "SouthEast";
    break;
  case Direction::SOUTH:
    os << "South";
    break;
  case Direction::SOUTHWEST:
    os << "SouthWest";
    break;
  case Direction::WEST:
    os << "West";
    break;
  case Direction::NORTHWEST:
    os << "NorthWest";
    break;
  case Direction::NONE:
    os << "None";
    break;
  }

  return os;
}

bool operator<(AxialHexDirection::Direction lhs,
               AxialHexDirection::Direction rhs) {
  return static_cast<int>(lhs) < static_cast<int>(rhs);
}