#include <iostream>
#include <memory>
#include <sstream>
#include <tuple>
#include "common.h"
#include "DoganBoard.h"
#include "DoganCell.h"
#include "enums.h"


Cell* DoganBoard::operator [](const Coordinate coordinates) {
    auto it = this->cells.find(coordinates);
    if( it == this->cells.end() ) {
        return nullptr;
    }
    return it->second.get();
}

DoganBoard::DoganBoard(DoganConfig config) {
    rengine.seed(std::random_device{}());

    boardSize = config.boardSize;
    
    std::vector<pip> numbers = config.getNumberConfiguration(rengine);
    std::vector<Resource> resources = config.getResourceConfiguration(rengine);

    size_t i = 0;
    for (const auto& c : config.tileLocations) {
        this->cells[c] = std::make_unique<DoganCell>(false, c, resources[i], numbers[i]);
        ++i;
    }
    for (const auto& [coords, cell] : this->cells) {
        auto [x, y] = coords;
        std::array<std::pair<Direction, Coordinate>, 8> adjacentCells = {
            std::make_pair(Direction::NORTH, std::make_tuple(x, y+1)),
            std::make_pair(Direction::NORTHEAST, std::make_tuple(x+1, y+1)),
            std::make_pair(Direction::EAST, std::make_tuple(x+1, y)),
            std::make_pair(Direction::SOUTHEAST, std::make_tuple(x+1, y-1)),
            std::make_pair(Direction::SOUTH, std::make_tuple(x, y-1)),
            std::make_pair(Direction::SOUTHWEST, std::make_tuple(x-1, y-1)),
            std::make_pair(Direction::WEST, std::make_tuple(x-1, y)),
            std::make_pair(Direction::NORTHWEST, std::make_tuple(x-1, y+1))
        };
        
        for (const auto& [d, c] : adjacentCells) {
            auto adjEntry = this->cells.find(c);
            if (adjEntry != this->cells.end()) {
                std::shared_ptr<DoganCell> adjCell = std::static_pointer_cast<DoganCell>(adjEntry->second);
                dynamic_cast<DoganCell *>(cell.get())->addAdjacentCell(d, adjCell);
            }
        }
    }

    static_cast<DoganCell*>(this->cells[config.robberPosition].get())->setRobber(true);

}


std::string DoganBoard::toString() {
    std::ostringstream oss;
    for(const auto& c : this->cells) {
        oss << "Cell {" << std::get<0>(c.first) << "," << std::get<1>(c.first) << "}: " << c.second->toString() << "\n";
    }
    return oss.str();
}
