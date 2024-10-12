#include <iostream>
#include <sstream>
#include "common.h"
#include "DoganBoard.h"
#include "DoganCell.h"
#include "enums.h"


Cell* DoganBoard::operator [](const Coordinate coordinates) {
    auto it = this->cells.find(coordinates);
    if( it == this->cells.end() ) {
        std::cerr << "Error: Coordinate of Cell not found";
        throw std::domain_error("Coordinate of Cell not found");
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
        this->cells[c] = std::make_unique<DoganCell>(resources[i], false, numbers[i]);
        ++i;
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
