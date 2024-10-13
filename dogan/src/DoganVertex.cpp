#include <stdexcept>
#include "DoganVertex.h"

DoganVertex::DoganVertex(Direction d, std::shared_ptr<DoganCell> dc) : direction(d), doganCell(dc), coordinate(dc->getCoordinate()), isReady(true) {
    if(d == Direction::EAST || d == Direction::WEST) {
        throw std::invalid_argument("Error: Direction::EAST and Direction::WEST are invalid directions for edges");
    }
}

DoganVertex::DoganVertex(std::initializer_list<std::variant<Direction, Coordinate2D>> parameters) : isReady(false) {
    if(parameters.size() == 2) {
        auto it = parameters.begin();
        direction = std::get<Direction>(*it);
        coordinate = std::get<Coordinate2D>(*(it + 1));
    }else {
        throw std::invalid_argument("Initializer list invalid. Must contain 2 elements");
    }
}


std::vector<DoganVertex> DoganVertex::getCorrespondingVertices(void) {
    if(!isReady) throw std::runtime_error("Error: DoganCell is not fully initialized. Call `ready` to finish initializing");
    std::vector<DoganVertex> corrVertices;
    auto [d1, d2] = getComplementDirections(direction);
    Direction dc1Dir = (direction == Direction::NORTH || direction == Direction::SOUTH) ? getOppositeDirection(d1) : direction;
    Direction dc2Dir = getOppositeDirection(d2);

    bool dc1Exists = doganCell->hasAdjacentCell(dc1Dir);
    bool dc2Exists = doganCell->hasAdjacentCell(dc2Dir);
    
    if (dc1Exists) {
        auto dc1 = doganCell->getAdjacentCell(dc1Dir);
        corrVertices.emplace_back(d1, dc1);
    }
    if (dc2Exists) {
        auto dc2 = doganCell->getAdjacentCell(dc2Dir);
        corrVertices.emplace_back(d2, dc2);
    }
    return corrVertices;
}

Direction DoganVertex::getDirection(void) {
    return direction;
}

std::shared_ptr<DoganCell> DoganVertex::getDoganCell(void) {
    if(!isReady) throw std::runtime_error("Error: DoganCell is not fully initialized. Call `ready` to finish initializing");
    return doganCell;
}

void DoganVertex::ready(std::map<Coordinate2D, std::shared_ptr<DoganCell>> cells) {
    auto it = cells.find(coordinate);
    if(it == cells.end()) throw std::runtime_error("Error: Attempting to make a vertex that doesn't exist");
    doganCell = cells[coordinate];
    isReady = true;
}