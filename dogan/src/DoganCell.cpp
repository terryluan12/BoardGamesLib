#include "DoganCell.h"
#include <sstream>

std::unordered_set<Coordinate2D> DoganCell::allCoordinates;

DoganCell::DoganCell(bool cr, Coordinate2D c, int n, Resource t) 
    : containsRobber(cr), coordinate(c), number(n), type(t) {
    auto [_, didInsert] = allCoordinates.insert(c);
    if(!didInsert) {
        throw std::invalid_argument("Error: Cell already exists");
    }
    for (auto &d : vertexDirections ) {
        vertices.emplace(d, std::make_shared<DoganVertex>(DoganVertex(d, coordinate)));
    }
    for (auto &e : edgeDirections ) {
        edges.emplace(e, std::make_shared<DoganEdge>(DoganEdge(e, coordinate)));
    }
}

void DoganCell::addAdjacentCell(const Direction d, std::shared_ptr<DoganCell> ac) {
    adjacentCells[d] = ac;
};

std::shared_ptr<DoganCell> DoganCell::getAdjacentCell(Direction d) {
    auto it = adjacentCells.find(d);
    if(it == adjacentCells.end()){
        throw std::out_of_range("Error: Adjacent Cell not found");
    }
    return it->second;
}

bool DoganCell::hasAdjacentCell(Direction d) const {
    auto it = this->adjacentCells.find(d);
    return it != this->adjacentCells.end();
}

Coordinate2D DoganCell::getCoordinate(void) const {
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
