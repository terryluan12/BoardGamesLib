#include "Edge.h"
#include <algorithm>

Edge::Edge(Coordinate2D c, HexDirection d) : Element(c, d) {
  if (d == HexDirection::NORTH || d == HexDirection::SOUTH) {
    throw std::invalid_argument("Error: Direction::NORTH and Direction::SOUTH "
                                "are invalid directions for edges");
  }
}

const std::array<HexDirection, 6> Edge::directions{
    HexDirection::NORTHWEST, HexDirection::NORTHEAST, HexDirection::EAST,
    HexDirection::SOUTHEAST, HexDirection::SOUTHWEST, HexDirection::WEST};

const int Edge::getEdgeIndex(HexDirection d) {
  if (d == HexDirection::NORTH || d == HexDirection::SOUTH) {
    throw std::invalid_argument("Error: Direction::NORTH and Direction::SOUTH "
                                "are invalid directions for edges");
  }
  auto it = std::find(directions.begin(), directions.end(), d);
  return std::distance(directions.begin(), it);
}

std::array<HexPath, 2> Edge::getAllEdgeRepresentations(HexDirection d) {
  if (d == HexDirection::NORTH || d == HexDirection::SOUTH) {
    throw std::invalid_argument("Error: Direction::NORTH and Direction::SOUTH "
                                "are invalid directions for edges");
  }
  const HexDirection targetDirection = AxialDirection::getOppositeDirection(d);
  return {{{HexDirection::NONE, d}, {d, targetDirection}}};
};

const std::vector<Edge> Edge::getAllRepresentations(void) const {
  auto otherEdge = getOtherRepresentations();
  return {*this, otherEdge[0]};
}

const std::vector<Edge> Edge::getOtherRepresentations(void) const {
  auto coord = coordinate + AxialDirection::toCoordinate(direction);
  auto dir = AxialDirection::getOppositeDirection(direction);
  auto edge = Edge(coord, dir);
  return {edge};
}

std::array<HexPath, 6> Edge::getAdjacentEdges(HexDirection d) {
  if (d == HexDirection::NORTH || d == HexDirection::SOUTH) {
    throw std::invalid_argument("Error: Direction::NORTH and Direction::SOUTH "
                                "are invalid directions for edges");
  }
  std::array<HexPath, 6> paths{};
  auto localEdges = getLocalAdjacentEdges(d);
  std::copy(localEdges.begin(), localEdges.end(), paths.begin());

  auto distantEdges = getDistantAdjacentEdges(d);
  std::copy(distantEdges.begin(), distantEdges.end(), paths.begin() + 2);
  return paths;
}

std::array<HexPath, 2> Edge::getLocalAdjacentEdges(HexDirection d) {
  if (d == HexDirection::NORTH || d == HexDirection::SOUTH) {
    throw std::invalid_argument("Error: Direction::NORTH and Direction::SOUTH "
                                "are invalid directions for edges");
  }
  int edgeIndex = getEdgeIndex(d);
  return {{{HexDirection::NONE, directions[(edgeIndex + 1) % 6]},
           {HexDirection::NONE, directions[(edgeIndex + 5) % 6]}}};
}

std::array<HexPath, 4> Edge::getDistantAdjacentEdges(HexDirection d) {
  if (d == HexDirection::NORTH || d == HexDirection::SOUTH) {
    throw std::invalid_argument("Error: Direction::NORTH and Direction::SOUTH "
                                "are invalid directions for edges");
  }
  int edgeIndex = getEdgeIndex(d);
  return {{{directions[edgeIndex], directions[(edgeIndex + 2) % 6]},
           {directions[(edgeIndex + 1) % 6], directions[(edgeIndex + 5) % 6]},
           {directions[edgeIndex], directions[(edgeIndex + 4) % 6]},
           {directions[(edgeIndex + 5) % 6], directions[(edgeIndex + 1) % 6]}}};
}
