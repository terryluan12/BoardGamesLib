#include <stdexcept>
#include "DoganEdge.h"


DoganEdge::DoganEdge(Direction d, Coordinate2D c): direction(d), coordinate(c) {
    if(d == Direction::NORTH || d == Direction::SOUTH) {
        throw std::invalid_argument("Error: Direction::NORTH and Direction::SOUTH are invalid directions for edges");
    }
}

std::vector<DoganEdge> DoganEdge::getCorrespondingEdge(DoganCell &dc) {
    std::vector<DoganEdge> corrEdge;
    if(dc.hasAdjacentCell(direction)){
        auto dc1 = dc.getAdjacentCell(direction);
        corrEdge.emplace_back(getOppositeDirection(direction), dc1->getCoordinate());
    }
    return corrEdge;
}

Direction DoganEdge::getDirection(void) {
    return direction;
}