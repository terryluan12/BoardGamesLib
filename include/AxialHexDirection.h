#pragma once

#include "Coordinate.h"
#include <array>
#include <map>
#include <ostream>
#include <utility>

/**
 * @brief A class containing enums and helper functions for working with Hexagonal Grids in an axial coordinate system
 * 
 */
class AxialHexDirection {
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
  static const std::array<Direction, 6> edgeDirections; //!< An array of the 6 edge directions
  static const std::array<Direction, 6> vertexDirections; //!< An array of the 6 vertex directions
  static const std::array<Direction, 8> allDirections; //!< An array of all directions

  /// An array of 2 directions representing an alternative representation of an edge or vertex. 
  /// The first Direction is the direction to travel to get to the tile the element is in. 
  /// The second Direction is the direction of the target edge or vertex, once you're in the target cell
  /// For example, the Southeastern vertex in a cell, has an alternative representation of {EAST, SOUTHWEST}, or {SOUTHEAST, NORTHWEST}
  using edgeRepresentation = std::array<AxialHexDirection::Direction, 2>; 
  using vertexRepresentation = std::array<AxialHexDirection::Direction, 2>; 

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
  /**
   * @brief Get the two other representations of a given vertex
   * 
   * @param d The direction of the target vertex
   * @return std::array<elementRepresentation, 2> 
   */
  static std::array<vertexRepresentation, 2> getComplementaryVertexRepresentations(Direction d);
  
  /**
   * @brief Get the locally adjacent edges of edge \p d (aka the two edges that are available within the local tile)
   * 
   * @param d The direction of the target edge
   * @return std::array<Direction, 2> The two edges which are adjacent to the target edge
   */
  static std::array<Direction, 2>
  getLocalAdjacentEdgeToEdgeDirections(Direction d);
  /**
   * @brief Get all representations of the two edges of edge \p d that must be traversed to. There are two distant edges, and two methods of travel for each edge
   * 
   * @param d The direction of the target edge
   * @return std::array<elementRepresentation, 4> 
   */
  static std::array<edgeRepresentation, 4>
  getDistantAdjacentEdgeToEdgeDirections(Direction d);
  /**
   * @brief Get The locally adjacent edges to vertex \p d .
   * 
   * @param d The direction of the target vertex
   * @return std::array<Direction, 2> The directions to the two edges that are adjacent to the vertex
   */
  static std::array<Direction, 2>
  getAdjacentEdgeToVertexDirections(Direction d);
  /**
   * @brief Get the edge that is "behind" a vertex in a certain direction. Used with @ref getAdjacentEdgeToVertexDirections to get all neighbouring edges to a vertex
   * 
   * @param d 
   * @return std::array<std::array<Direction, 2>, 2> 
   */
  static std::array<std::array<Direction, 2>, 2>
  getEdgeFromVertexDirection(Direction d);
  /**
   * @brief Get the two locally adjacent vertices to vertex \p d
   * 
   * @param d The direction of the target vertex
   * @return std::array<Direction, 2> The directions to the two vertices that are adjacent to the target vertex
   */
  static std::array<Direction, 2>
  getAdjacentVertexToVertexDirections(Direction d);
  /**
   * @brief Get the representations of the vertex that are "behind another vertex" in a certain direction. Used with @ref getAdjacentVertexToVertexDirections to get all neighbouring vertices to a vertex
   * 
   * @param d The direction of the target vertex
   * @return std::array<elementRepresentation, 2> The two representations of the vertex that are "behind" the target vertex
   */
  static std::array<vertexRepresentation, 2>
  getSecondDegreeVertex(Direction d);

  /**
   * @brief Get the index of an edge in the edgeDirections array
   * 
   * @param d Direction of the edge
   * @return const int The index of the edge in the edgeDirections array
   */
  static const int getEdgeIndex(Direction d);
  /**
   * @brief Get the index of a vertex in the vertexDirections array
   * 
   * @param d Direction of the vertex
   * @return const int The index of the vertex in the vertexDirections array
   */
  static const int getVertexIndex(Direction d);
  /**
   * @brief Get all representations of a given vertex
   * 
   * @param d 
   * @return std::array<elementRepresentation, 3> 
   */
  static std::array<vertexRepresentation, 3>
  getAllVertexRepresentations(Direction d);
  /**
   * @brief Get all representations of a given edge
   * 
   * @param d 
   * @return std::array<elementRepresentation, 3> 
   */
  static std::array<edgeRepresentation, 2>
  getAllEdgeRepresentations(Direction d);
};
using vertexRepresentation = AxialHexDirection::vertexRepresentation;
using edgeRepresentation = AxialHexDirection::edgeRepresentation;
using elementRepresentation = std::array<AxialHexDirection::Direction, 2>;

std::ostream &operator<<(std::ostream &os,
                         AxialHexDirection::Direction const &d);

bool operator<(AxialHexDirection::Direction lhs,
               AxialHexDirection::Direction rhs);