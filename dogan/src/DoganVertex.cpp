#include <stdexcept>
#include "DoganVertex.h"

DoganVertex::DoganVertex(Direction d, Coordinate2D c): direction(d), coordinate(c)  {
    if(d == Direction::EAST || d == Direction::WEST) {
        throw std::invalid_argument("Error: Direction::EAST and Direction::WEST are invalid directions for edges");
    }
}

std::vector<DoganVertex> DoganVertex::getCorrespondingVertices(DoganCell &dc) {
    std::vector<DoganVertex> corrVertices;
    auto [d1, d2] = getComplementDirections(direction);
    Direction dc1Dir = (direction == Direction::NORTH || direction == Direction::SOUTH) ? getOppositeDirection(d1) : direction;
    Direction dc2Dir = getOppositeDirection(d2);

    bool dc1Exists = dc.hasAdjacentCell(dc1Dir);
    bool dc2Exists = dc.hasAdjacentCell(dc2Dir);
    
    if (dc1Exists) {
        auto dc1 = dc.getAdjacentCell(dc1Dir);
        corrVertices.emplace_back(DoganVertex(d1, dc1->getCoordinate()));
    }
    if (dc2Exists) {
        auto dc2 = dc.getAdjacentCell(dc2Dir);
        corrVertices.emplace_back(DoganVertex(d2, dc2->getCoordinate()));
    }
    return corrVertices;
}

Coordinate2D DoganVertex::getCoordinate(void) const {
    return coordinate;
}

Direction DoganVertex::getDirection(void) const {
    return direction;
}