#include <sstream>
#include "DoganCell.h"


void DoganCell::addAdjacentCell(const Direction d, std::shared_ptr<DoganCell> ac) {
    adjacentCells[d] = ac;
};

std::shared_ptr<DoganCell> DoganCell::getAdjacentCell(Direction d) {
    auto it = adjacentCells.find(d);
    if(it != adjacentCells.end()){
        return adjacentCells[d];
    }
    return nullptr;
}

Coordinate DoganCell::getCoordinate(void) {
    return coordinate;
}

int DoganCell::getNumber() { 
    return this->number;
}

Resource DoganCell::getType() { 
    return this->type;
}

bool DoganCell::hasRobber(){
    return this->containsRobber;
}


std::string DoganCell::toString(void) {
    std::ostringstream oss;
    oss << "Type: " << static_cast<int>(type) << "; ContainsRobber: " << containsRobber << ", Number: " << number;
    return oss.str();

    // TODO: Change when g++ supports C++20
    // return std::format("Type: {}; ContainsRobber: {}, Number: {}", type, containsRobber, number);
};

void DoganCell::setRobber(bool robber) {
    this->containsRobber=robber;
}
