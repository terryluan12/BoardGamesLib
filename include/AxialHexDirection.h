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
  static const std::array<Direction, 6> edgeDirections;
  static const std::array<Direction, 6> vertexDirections;
  static const std::array<Direction, 8> allDirections;


  // static methods
  static Direction fromString(std::string d);
  static Coordinate2D toCoordinate(Direction d);

  static Direction getOppositeDirection(Direction d);
  static std::array<Direction, 4>
  getComplementaryDirections(Direction d);

  static const int getEdgeIndex(Direction d);
  static const int getVertexIndex(Direction d);
};

std::ostream &operator<<(std::ostream &os,
                         AxialHexDirection::Direction const &d);

bool operator<(AxialHexDirection::Direction lhs,
               AxialHexDirection::Direction rhs);