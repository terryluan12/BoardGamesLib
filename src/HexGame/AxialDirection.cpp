#include "AxialDirection.h"
#include "Exceptions.h"
#include <algorithm>

const std::array<HexDirection, 8> AxialDirection::allDirections{
    Direction::NORTH,     Direction::NORTHEAST, Direction::EAST,
    Direction::SOUTHEAST, Direction::SOUTH,     Direction::SOUTHWEST,
    Direction::WEST,      Direction::NORTHWEST};

HexDirection AxialDirection::fromString(std::string d) {
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

Coordinate2D AxialDirection::toCoordinate(Direction d) {
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
    throw std::invalid_argument("Error: Invaldid Direction");
  }
}

HexDirection AxialDirection::getOppositeDirection(Direction d) {
  return static_cast<Direction>((static_cast<int>(d) + 4) % 8);
}

std::ostream &operator<<(std::ostream &os, HexDirection const &d) {
  switch (d) {
  case HexDirection::NORTH:
    os << "North";
    break;
  case HexDirection::NORTHEAST:
    os << "NorthEast";
    break;
  case HexDirection::EAST:
    os << "East";
    break;
  case HexDirection::SOUTHEAST:
    os << "SouthEast";
    break;
  case HexDirection::SOUTH:
    os << "South";
    break;
  case HexDirection::SOUTHWEST:
    os << "SouthWest";
    break;
  case HexDirection::WEST:
    os << "West";
    break;
  case HexDirection::NORTHWEST:
    os << "NorthWest";
    break;
  case HexDirection::NONE:
    os << "None";
    break;
  }

  return os;
}

bool operator<(AxialDirection::Direction lhs,
               AxialDirection::Direction rhs) {
  return static_cast<int>(lhs) < static_cast<int>(rhs);
}