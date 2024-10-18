#pragma once

#include "Coordinate.h"
#include <array>
#include <map>
#include <ostream>
#include <utility>

class AxialHexDirection {
public:
  // Direction
  enum class Direction {
    NORTH = 0,
    NORTHEAST = 1,
    EAST = 2,
    SOUTHEAST = 3,
    SOUTH = 4,
    SOUTHWEST = 5,
    WEST = 6,
    NORTHWEST = 7
  };

  // static methods
  static const Direction fromString(std::string d);
  static const Coordinate2D toCoordinate(Direction d);

  static Direction getOppositeDirection(Direction d);
  static std::pair<Direction, Direction>
  getComplementaryDirections(Direction d);

  static const std::array<Direction, 6> getEdgeDirections(void);
  static const std::array<Direction, 6> getVertexDirections(void);
  static const std::array<Direction, 8> getAllDirections(void);
};

std::ostream &operator<<(std::ostream &os,
                         AxialHexDirection::Direction const &d);

bool operator<(AxialHexDirection::Direction lhs,
               AxialHexDirection::Direction rhs);