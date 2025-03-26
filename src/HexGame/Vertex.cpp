#include "Vertex.h"
#include "Edge.h"
#include <algorithm>
      
Vertex::Vertex(Coordinate2D c, HexDirection d) : coordinate(c) {
    if (d == HexDirection::EAST || d == HexDirection::WEST ) {
        throw std::invalid_argument("Direction cannot be East or West for a vertex");
    }
    else {
        direction = d;
    }
}

const std::array<HexDirection, 6> Vertex::directions{
    HexDirection::NORTH, HexDirection::NORTHEAST, HexDirection::SOUTHEAST,
    HexDirection::SOUTH, HexDirection::SOUTHWEST, HexDirection::NORTHWEST};

const int Vertex::getIndex(HexDirection d) {
    if (d == HexDirection::EAST || d == HexDirection::WEST) {
      throw std::invalid_argument(
        "Error: Invalid Direction. Vertex Cannot be East or West");
    }
    auto it = std::find(directions.begin(), directions.end(), d);
    return std::distance(directions.begin(), it);
}
std::array<HexPath, 3>
Vertex::getAllVertexRepresentations(HexDirection d) {
  if (d == HexDirection::EAST || d == HexDirection::WEST) {
    throw std::invalid_argument("Error: Direction::EAST and Direction::WEST "
                                "are invalid directions for vertices");
  }

  auto [vertexRepresentation1, vertexRepresentation2] =
      getComplementaryVertexRepresentations(d);
  std::array<HexPath, 3> corrVertices{{
      {HexDirection::NONE, d},
      vertexRepresentation1,
      vertexRepresentation2,
  }};
  return corrVertices;
}

std::array<HexPath, 2>
Vertex::getComplementaryVertexRepresentations(HexDirection d) {
  int vertexIndex = getIndex(d);
  HexDirection firstTravelDirection = Edge::directions[vertexIndex];
  HexDirection firstDirection = directions[(vertexIndex + 2) % 6];
  HexDirection secondTravelDirection = Edge::directions[(vertexIndex + 1) % 6];
  HexDirection secondDirection = directions[(vertexIndex + 4) % 6];
  return {{{firstTravelDirection, firstDirection},
           {secondTravelDirection, secondDirection}}};
}

std::array<HexPath, 4>
Vertex::getAdjacentEdges(HexDirection d) {
  if (d == HexDirection::EAST || d == HexDirection::WEST) {
    throw std::invalid_argument("Error: Direction::EAST and Direction::WEST "
                                "are invalid directions for vertices");
  }
  std::array<HexPath, 4> paths{};

  auto localEdges = getLocalAdjacentEdges(d);
  std::copy(localEdges.begin(), localEdges.end(), paths.begin());

  auto distantEdge = getDistantAdjacentEdge(d);
  std::copy(distantEdge.begin(), distantEdge.end(), paths.begin()+2);
  return paths;
}

std::array<HexPath, 2>
      Vertex::getLocalAdjacentEdges(HexDirection d) {
        int edgeIndex = getIndex(d);
        HexDirection d1 = Edge::directions[edgeIndex];
        HexDirection d2 = Edge::directions[(edgeIndex + 1) % 6];
        return {{
          {HexDirection::NONE, d1},
          {HexDirection::NONE, d2}, 
        }};
      }

std::array<HexPath, 2> Vertex::getDistantAdjacentEdge(HexDirection d) {
    
  if (d == HexDirection::EAST || d == HexDirection::WEST) {
    throw std::invalid_argument("Error: Direction::EAST and Direction::WEST "
                                "are invalid directions for vertices");
  }
  int vertexIndex = getIndex(d);
  return {{{Edge::directions[vertexIndex], Edge::directions[(vertexIndex + 2) % 6]},
           {Edge::directions[(vertexIndex + 1) % 6], Edge::directions[(vertexIndex + 5) % 6]}}};
}

std::array<HexPath, 4>
Vertex::getAdjacentVertices(HexDirection d) {
    if (d == HexDirection::EAST || d == HexDirection::WEST) {
      throw std::invalid_argument("Error: Direction::EAST and Direction::WEST "
                                  "are invalid directions for vertices");
    }
    std::array<HexPath, 4> paths{};
    auto localVertices = getLocalAdjacentVertices(d);
    auto distantVertices = getDistantAdjacentVertex(d);
    std::copy(localVertices.begin(), localVertices.end(), paths.begin());
    std::copy(distantVertices.begin(), distantVertices.end(), paths.begin()+2);
    return paths;

}

std::array<HexPath, 2>
Vertex::getLocalAdjacentVertices(HexDirection d) {
    if (d == HexDirection::EAST || d == HexDirection::WEST) {
      throw std::invalid_argument("Error: Direction::EAST and Direction::WEST "
                                  "are invalid directions for vertices");
    }
  int vertexIndex = getIndex(d);
  return {{
    {HexDirection::NONE, directions[(vertexIndex + 1) % 6]},
    {HexDirection::NONE, directions[(vertexIndex + 5) % 6]}
    }};
}

std::array<HexPath, 2>
Vertex::getDistantAdjacentVertex(HexDirection d) {
    if (d == HexDirection::EAST || d == HexDirection::WEST) {
        throw std::invalid_argument("Error: Direction::EAST and Direction::WEST "
                                    "are invalid directions for vertices");
    }
    int vertexIndex = getIndex(d);
    return {
        {{Edge::directions[vertexIndex], directions[(vertexIndex + 1) % 6]},
        {Edge::directions[(vertexIndex + 1) % 6],
            directions[(vertexIndex + 5) % 6]}}};
}