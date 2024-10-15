#include "DoganBoard.h"
#include "enums.h"
#include <memory>
#include <sstream>

DoganCell &DoganBoard::operator [](const Coordinate2D coordinates) {
    auto it = this->cells.find(coordinates);
    if(it == this->cells.end()) {
        throw std::out_of_range("Error: Coordinate not found");
    }
    return *(it->second);
}

DoganBoard::DoganBoard(DoganConfig config) {
    rengine.seed(std::random_device{}());

    this->boardSize = config.boardSize; 
    this->robberPosition = config.initialRobberLocation;
    this->ports = config.getPortLocations(rengine);
    std::vector<pip> numbers = config.getNumberConfiguration(rengine);
    std::vector<ResourceType> resources = config.getResourceConfiguration(rengine);
    std::array<size_t, 5> resourceCount = config.initialResourceCount;
    std::array<size_t, 5> developmentCount = config.initialDevelopmentCount;
    bank = DoganBank(resourceCount, developmentCount);

    // create all tiles
    size_t i = 0;
    for (const auto& c : config.initialTileLocations) {
        this->cells[c] = std::make_shared<DoganCell>(DoganCell(false, c, numbers[i], resources[i]));
        ++i;
    }
    for (auto& [coords, cell] : this->cells) {
        const auto [x, y] = coords;
        std::array<std::pair<Direction, Coordinate2D>, 8> adjacentCells = {
            std::make_pair<Direction, Coordinate2D>(Direction::NORTH, {x, y+1}),
            std::make_pair<Direction, Coordinate2D>(Direction::NORTHEAST, {x+1, y+1}),
            std::make_pair<Direction, Coordinate2D>(Direction::EAST, {x+1, y}),
            std::make_pair<Direction, Coordinate2D>(Direction::SOUTHEAST, {x+1, y-1}),
            std::make_pair<Direction, Coordinate2D>(Direction::SOUTH, {x, y-1}),
            std::make_pair<Direction, Coordinate2D>(Direction::SOUTHWEST, {x-1, y-1}),
            std::make_pair<Direction, Coordinate2D>(Direction::WEST, {x-1, y}),
            std::make_pair<Direction, Coordinate2D>(Direction::NORTHWEST, {x-1, y+1})
        };
        // populate cell neighbours
        for (const auto& [d, c] : adjacentCells) {
            auto adjEntry = this->cells.find(c);
            if (adjEntry != this->cells.end()) {
                auto adjCell = adjEntry->second;
                cell->addAdjacentCell(d, adjCell);
            }
        }
    }
    
    cells[config.initialRobberLocation]->setRobber(true);
}

Coordinate2D DoganBoard::getRobberPosition(void) const {
    return robberPosition;
}

const DoganBank DoganBoard::getBank(void) const {
    return bank;
}

size_t DoganBoard::getBoardSize(void) const {
    return boardSize;
}

const std::map<Coordinate2D, std::shared_ptr<DoganCell>> DoganBoard::getBoard(void) const {
    return cells;
}

const std::vector<DoganPort> DoganBoard::getPorts(void) const {
    return ports;
}


bool DoganBoard::hasVertex(const Coordinate2D c) const {
    return cells.find(c) != cells.end();
}


void DoganBoard::setBoardSize(size_t bs) {
    if(bs > MAX_BOARD_SIZE) {
        throw std::out_of_range("Error, attempting to set Board Size to greater than limit. Must be less than " + MAX_BOARD_SIZE);
    }
    else {
        boardSize = bs;
    }
}

std::ostream &operator<< (std::ostream &os, DoganBoard const &db) {
    for(const auto& c : db.getBoard()) {
        os << *(c.second);
    }
    size_t i = 1;
    for(auto &pl : db.getPorts()) {
        os << pl;
        ++i;
    }
    os << db.getBank();
    return os;
}