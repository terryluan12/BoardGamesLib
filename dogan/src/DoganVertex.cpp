#include <stdexcept>
#include "DoganVertex.h"

DoganVertex::DoganVertex(Direction d, DoganCell &dc) : direction(d), doganCell(dc), coordinate(dc.getCoordinate()), isReady(true) {
    if(d == Direction::EAST || d == Direction::WEST) {
        throw std::invalid_argument("Error: Direction::EAST and Direction::WEST are invalid directions for edges");
    }
}

DoganVertex::DoganVertex(std::initializer_list<std::variant<Direction, Coordinate>> parameters) : isReady(false) {
    if(parameters.size() == 2) {
        auto it = parameters.begin();
        direction = std::get<Direction>(*it);
        coordinate = std::get<Coordinate>(*(it + 1));
    }else {
        
        throw std::invalid_argument("Initializer list invalid. Must contain 2 elements");
    }
}


std::vector<DoganVertex> DoganVertex::getCorrespondingVertices(void) {
    if(!isReady) throw std::runtime_error("Error: DoganCell is not fully initialized. Call `ready` to finish initializing");
    std::vector<DoganVertex> corrVertices;
    auto [d1, d2] = getComplementDirections(direction);
    auto dc1 = (direction == Direction::NORTH || direction == Direction::SOUTH) ?
                doganCell->get().getAdjacentCell(getOppositeDirection(d1)) :
                doganCell->get().getAdjacentCell(direction);
    auto dc2 = doganCell->get().getAdjacentCell(getOppositeDirection(d2));

    
    if (dc1 != nullptr) {
        corrVertices.emplace_back(d1, *dc1);
    }
    if (dc2 != nullptr) {
        corrVertices.emplace_back(d2, *dc2);
    }
    return corrVertices;
}

Direction DoganVertex::getDirection(void) {
    return direction;
}

std::optional<DoganCell> DoganVertex::getDoganCell(void) {
    if(doganCell.has_value()){
        return *doganCell;
    } else {
        return std::nullopt;
    }
}

void DoganVertex::ready(std::map<Coordinate, std::shared_ptr<Cell>> cells) {
    auto cell = dynamic_cast<DoganCell*>(cells[coordinate].get());
    doganCell = std::ref(*cell);
    isReady = true;
}