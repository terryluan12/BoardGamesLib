#include "DoganBoard.h"
#include "enums.h"
#include <memory>
#include <sstream>
#include <iostream>

DoganCell &DoganBoard::operator [](const Coordinate2D coordinates) {
    auto it = this->cells.find(coordinates);
    if(it == this->cells.end()) {
        throw std::out_of_range("Error: Coordinate not found");
    }
    return *(it->second);
}

DoganBoard::DoganBoard(DoganConfig config) {
    rengine.seed(std::random_device{}());

    this->boardSize = config.getBoardSize(); 
    this->robberLocation = config.getRobberLocation();
    this->ports = config.getPorts(rengine);
    std::vector<pip> numbers = config.getNumbers(rengine);
    std::vector<ResourceType> resources = config.getResources(rengine);

    // create all tiles
    size_t i = 0;
    for (const auto& c : config.getTileLocations()) {
        this->cells[c] = std::make_shared<DoganCell>(DoganCell(false, c, numbers[i], resources[i]));
        ++i;
    }
    for (auto& [coord, cell] : this->cells) {
        // populate cell neighbours
        for (const auto& direction : HexagonalDirection::getAllDirections()) {
            auto adjEntry = this->cells.find(coord + HexagonalDirection::toCoordinate(direction));
            if (adjEntry != this->cells.end()) {
                auto adjCell = adjEntry->second;
                cell->addAdjacentCell(direction, adjCell);
            }
        }
    }
    cells[config.getRobberLocation()]->setRobber(true);
}

Coordinate2D DoganBoard::getRobberLocation(void) const {
    return robberLocation;
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


bool DoganBoard::hasTile(const Coordinate2D c) const {
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
    return os;
}