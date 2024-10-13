#include <memory>
#include <sstream>
#include "DoganBoard.h"

DoganCell &DoganBoard::operator [](const Coordinate coordinates) {
    auto it = this->cells.find(coordinates);
    if(it == this->cells.end()) {
        throw std::out_of_range("Error: Coordinate not found");
    }
    return *(it->second);
}

DoganBoard::DoganBoard(DoganConfig config) {
    rengine.seed(std::random_device{}());

    boardSize = config.boardSize; 
    this->portLocations = config.portLocations;
    std::vector<pip> numbers = config.getNumberConfiguration(rengine);
    std::vector<Resource> resources = config.getResourceConfiguration(rengine);

    // create all tiles
    size_t i = 0;
    for (const auto& c : config.tileLocations) {
        this->cells[c] = std::make_shared<DoganCell>(DoganCell(false, c, resources[i], numbers[i]));
        ++i;
    }
    for (auto& [coords, cell] : this->cells) {
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
        // Connect all adjacent cells
        for (const auto& [d, c] : adjacentCells) {
            auto adjEntry = this->cells.find(c);
            if (adjEntry != this->cells.end()) {
                auto adjCell = adjEntry->second;
                cell->addAdjacentCell(d, adjCell);
            }
        }
    }
    cells[config.robberPosition]->setRobber(true);
}


std::string DoganBoard::toString() const {
    std::ostringstream oss;
    for(const auto& c : this->cells) {
        oss << "Cell {" << std::get<0>(c.first) << "," << std::get<1>(c.first) << "}: " << c.second->toString() << "\n";
    }
    return oss.str();
}


size_t DoganBoard::getBoardSize(void) const {
    return boardSize;
}

std::map<Coordinate, std::shared_ptr<DoganCell>> DoganBoard::getBoard(void) {
    return cells;
}

void DoganBoard::setBoardSize(size_t bs) {
    if(bs > MAX_BOARD_SIZE) {
        throw std::out_of_range("Error, attempting to set Board Size to greater than limit. Must be less than " + MAX_BOARD_SIZE);
    }
    else {
        boardSize = bs;
    }
}