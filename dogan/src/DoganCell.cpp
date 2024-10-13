#include <memory>
#include <sstream>
#include "DoganCell.h"


void DoganCell::addAdjacentCell(const Direction d, std::shared_ptr<DoganCell> ac) {
    adjacentCells[d] = ac;
};

std::shared_ptr<DoganCell> DoganCell::getAdjacentCell(Direction d) {
    auto it = adjacentCells.find(d);
    if(it == adjacentCells.end()){
        throw std::out_of_range("Error: Adjacent Cell not found");
    }
    return adjacentCells[d];
}

bool DoganCell::hasAdjacentCell(Direction d) const {
    auto it = this->adjacentCells.find(d);
    return it != this->adjacentCells.end();
}

Coordinate DoganCell::getCoordinate(void) const {
    return coordinate;
}

int DoganCell::getNumber(void) const { 
    return this->number;
}

Resource DoganCell::getType(void) const { 
    return this->type;
}

bool DoganCell::hasRobber(void) const {
    return this->containsRobber;
}


std::string DoganCell::toString(void) const {
    std::ostringstream oss;
    oss << "Type: " << static_cast<int>(type) << "; ContainsRobber: " << containsRobber << ", Number: " << number;
    return oss.str();

    // TODO: Change when g++ supports C++20
    // return std::format("Type: {}; ContainsRobber: {}, Number: {}", type, containsRobber, number);
}

void DoganCell::setRobber(bool robber) {
    this->containsRobber=robber;
}
