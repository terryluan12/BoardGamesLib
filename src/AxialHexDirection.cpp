#include "AxialHexDirection.h"
#include "Exceptions.h"
#include <algorithm>

using Direction = AxialHexDirection::Direction;

const std::array<Direction, 6> AxialHexDirection::edgeDirections{ Direction::NORTHWEST, Direction::NORTHEAST, Direction::EAST,
                                                                  Direction::SOUTHEAST, Direction::SOUTHWEST, Direction::WEST};
const std::array<Direction, 6> AxialHexDirection::vertexDirections{ Direction::NORTH, Direction::NORTHEAST, Direction::SOUTHEAST,
                                                                    Direction::SOUTH, Direction::SOUTHWEST, Direction::NORTHWEST};
const std::array<Direction, 8> AxialHexDirection::allDirections{Direction::NORTH,     Direction::NORTHEAST, Direction::EAST,
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
    throw NoSuchDirection("Error: Invalid Direction");
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
  default:
    throw std::invalid_argument("Error: Invalid Direction");
  }
}

Direction AxialHexDirection::getOppositeDirection(Direction d) {
  return static_cast<Direction>((static_cast<int>(d) + 4) % 8);
}

std::array<Direction, 4>
AxialHexDirection::getComplementaryDirections(Direction d) {
  int vertexIndex = getVertexIndex(d);
  Direction firstDirection = vertexDirections[(vertexIndex+2)%6];
  Direction firstTravelDirection = edgeDirections[vertexIndex];
  Direction secondDirection = vertexDirections[(vertexIndex+4)%6];
  Direction secondTravelDirection = edgeDirections[(vertexIndex+1)%6];
  return {firstDirection, firstTravelDirection, secondDirection, secondTravelDirection};
}

const int AxialHexDirection::getEdgeIndex(Direction d) {
  if(d == Direction::NORTH || d == Direction::SOUTH){
    throw std::invalid_argument("Error: Invalid Direction. Edge Cannot be North or South");
  }
  auto it = std::find(edgeDirections.begin(), edgeDirections.end(), d);
  return std::distance(edgeDirections.begin(), it);
}

const int AxialHexDirection::getVertexIndex(Direction d) {
  if(d == Direction::EAST || d == Direction::WEST){
    throw std::invalid_argument("Error: Invalid Direction. Vertex Cannot be East or West");
  }
  auto it = std::find(vertexDirections.begin(), vertexDirections.end(), d);
  return std::distance(vertexDirections.begin(), it);
}

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
  }

  return os;
}

bool operator<(AxialHexDirection::Direction lhs,
               AxialHexDirection::Direction rhs) {
  return static_cast<int>(lhs) < static_cast<int>(rhs);
}