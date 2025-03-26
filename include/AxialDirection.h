#pragma once

#include "Coordinate.h"
#include <array>
#include <map>
#include <ostream>
#include <utility>

/**
 * @brief A class containing enums and helper functions for working with
 * Hexagonal Grids in an axial coordinate system
 *
 */
class AxialDirection {
public:
  /**
   * @brief Enums representing the 6 directions of a hexagonal grid
   *
   */
  enum class Direction {
    NORTH = 0,
    NORTHEAST = 1,
    EAST = 2,
    SOUTHEAST = 3,
    SOUTH = 4,
    SOUTHWEST = 5,
    WEST = 6,
    NORTHWEST = 7,
    NONE = 8
  };
  static const std::array<Direction, 8>
      allDirections; //!< An array of all directions

  /**
   * @brief Converts a string to a Direction
   *
   * @param d The two character string representing the direction
   * @return Direction
   */
  static Direction fromString(std::string d);
  /**
   * @brief Converts a Direction to the 2D Coordinate Representation
   *
   * @param d
   * @return Coordinate2D
   */
  static Coordinate2D toCoordinate(Direction d);
  /**
   * @brief Get the opposite direction of a given direction
   *
   * @param d
   * @return Direction
   */
  static Direction getOppositeDirection(Direction d);
};
using HexDirection = AxialDirection::Direction;
using HexPath = std::array<HexDirection, 2>;

std::ostream &operator<<(std::ostream &os, AxialDirection::Direction const &d);

bool operator<(AxialDirection::Direction lhs, AxialDirection::Direction rhs);