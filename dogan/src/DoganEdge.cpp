#include <stdexcept>
#include "DoganEdge.h"


DoganEdge::DoganEdge(Direction d, DoganCell &dc) : direction(d), doganCell(dc) {
    if(d == Direction::NORTH || d == Direction::SOUTH) {
        throw std::invalid_argument("Error: Direction::NORTH and Direction::SOUTH are invalid directions for edges");
    }
}

std::vector<DoganEdge> DoganEdge::getCorrespondingEdge(void) {
    std::vector<DoganEdge> corrEdge;
    auto dc1 = doganCell.getAdjacentCell(direction);
    if(dc1 != nullptr){
        corrEdge.emplace_back(getOppositeDirection(direction), *dc1);
    }
    return corrEdge;
}

Direction DoganEdge::getDirection(void) {
    return direction;
}
DoganCell DoganEdge::getDoganCell(void) {
    return doganCell;
}