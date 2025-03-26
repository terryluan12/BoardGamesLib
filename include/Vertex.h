#pragma once

#include "AxialDirection.h"
#include "Coordinate.h"
#include "Element.h"

class Vertex : public Element {
public:
  Vertex(Coordinate2D c, HexDirection d);
  static const std::array<HexDirection, 6> directions;
  /**
   * @brief Get the index of a vertex in the directions array
   *
   * @param d Direction of the vertex
   * @return const int The index of the vertex in the directions array
   */
  static const int getIndex(HexDirection d);

  /**
   * @brief Get all representations of a given vertex
   *
   * @param d
   * @return std::array<HexPath, 3>
   */
  static std::array<HexPath, 3> getAllVertexRepresentations(HexDirection d);

  /**
   * @brief Get all representations of the vertex
   *
   * @param d
   * @return std::vector<Element>
   */
  const std::vector<Vertex> getAllRepresentations(void) const;
  /**
   * @brief Get a vector of all representations of the vertex
   *
   * @param d
   * @return std::vector<Element>
   */
  const std::vector<Vertex> getOtherRepresentations(void) const;

  /**
   * @brief Get the two other representations of a given vertex
   *
   * @param d The direction of the target vertex
   * @return std::array<HexPath, 2>
   */
  static std::array<HexPath, 2>
  getComplementaryVertexRepresentations(HexDirection d);

  /**
   * @brief Get The adjacent local edges \p d .
   *
   * @param d The direction of the target vertex
   * @return std::array<Direction, 4> The directions to the two edges that are
   * adjacent to the vertex
   */
  static std::array<HexPath, 4> getAdjacentEdges(HexDirection d);

  /**
   * @brief Get the adjacent local edges \p d .
   *
   * @param d The direction of the target vertex
   * @return std::array<HexPath, 2> The directions to the two edges that are
   * adjacent to the vertex
   */
  static std::array<HexPath, 2> getLocalAdjacentEdges(HexDirection d);

  /**
   * @brief Get the edge that is "behind" a vertex in a certain direction. Used
   * with @ref getAdjacentEdges to get all neighbouring edges
   * to a vertex
   *
   * @param d The direction of the target vertex
   * @return std::array<HexPath, 2>
   */
  static std::array<HexPath, 2> getDistantAdjacentEdge(HexDirection d);

  /**
   * @brief Get representations of all adjacent vertex. The two "local" vertices
   * first and then both representations of the third "distant" vertex
   * @return std::array<HexPath, 4>
   *
   */
  static std::array<HexPath, 4> getAdjacentVertices(HexDirection d);

  /**
   * @brief Get the directions of the two adjacent local vertices \p d
   *
   * @param d The direction of the target vertex
   * @return std::array<HexPath, 2> The directions to the two vertices that
   * are adjacent to the target vertex
   */
  static std::array<HexPath, 2> getLocalAdjacentVertices(HexDirection d);

  /**
   * @brief Get the representations of the vertex that are "behind another
   * vertex" in a certain direction. Used with @ref
   * getAdjacentVertices to get all neighbouring vertices to a
   * vertex
   *
   * @param d The direction of the target edge
   * @return std::array<HexPath, 4>
   */
  static std::array<HexPath, 2> getDistantAdjacentVertex(HexDirection d);
};