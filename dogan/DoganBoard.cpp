#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>
#include <tuple>
#include "../common.h"
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
    
    std::vector<pip> numbers = getNumberConfiguration(config.numberConfiguration);
    std::vector<Resource> resources = getResourceConfiguration(config.resourceConfiguration);

    size_t i = 0;
    for (const auto& c : config.tileLocations) {
        this->cells[c] = std::make_unique<DoganCell>(resources[i], false, numbers[i]);
        ++i;
    }

    static_cast<DoganCell*>(this->cells[config.robberPosition].get())->setRobber(true);

}

std::vector<pip> DoganBoard::getNumberConfiguration(const std::string configValue) {
    std::vector<pip> numberOrder;
    std::uniform_int_distribution<uint32_t> pipRand(1, 6);

    if(configValue == "default"){
        // initialize vector with all numbers in board and shuffle
        numberOrder = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
        std::shuffle(numberOrder.begin(), numberOrder.end(), rengine);
        
        numberOrder.insert(numberOrder.begin() + 9, 7);
    }
        return numberOrder;
}

std::vector<Resource> DoganBoard::getResourceConfiguration(const std::string configValue) {
    std::vector<Resource> resourceOrder;
    std::uniform_int_distribution<uint32_t> resourceRand(0, 4);

    if(configValue == "default"){
        // initialize vector with all resources in board and shuffle
        resourceOrder = {
                            Resource::BRICK, Resource::BRICK, Resource::BRICK,
                            Resource::SHEEP, Resource::SHEEP, Resource::SHEEP,
                            Resource::STONE, Resource::STONE, Resource::STONE,
                            Resource::WHEAT, Resource::WHEAT, Resource::WHEAT,
                            Resource::WOOD,  Resource::WOOD,  Resource::WOOD,
                            static_cast<Resource>(resourceRand(rengine)), 
                            static_cast<Resource>(resourceRand(rengine)), 
                            static_cast<Resource>(resourceRand(rengine))
                        };
        std::shuffle(resourceOrder.begin(), resourceOrder.end(), rengine);

        // insert into final array
        resourceOrder.insert(resourceOrder.begin() + 9, Resource::INVAL);
    }
    return resourceOrder;
}

std::string DoganBoard::toString() {
    std::ostringstream oss;
    for(const auto& c : this->cells) {
        oss << "Cell {" << std::get<0>(c.first) << "," << std::get<1>(c.first) << "}: " << c.second->toString() << "\n";
    }
    return oss.str();
}
