#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>
#include "DoganBoard.h"
#include "DoganCell.h"
#include "enums.h"


Cell *DoganBoard::operator [](const int i) {
    if( i >= this->BOARDSIZE || i < 0) {
        std::cerr << "Error: Index out of bounds" << i << " is not between 0 and " << this->BOARDSIZE-1;
        throw std::out_of_range("Index out of bounds in DoganBoard::operator[]");
    }
    return this->cells[i].get();
}

DoganBoard::DoganBoard(void) {
    rengine.seed(std::random_device{}());
    
    
    std::array<Resource, BOARDSIZE> resources = getResourceConfiguration();
    std::array<DoganBoard::pips, BOARDSIZE> numbers = getNumberConfiguration();


    for (size_t i = 0; i < BOARDSIZE; i++) {
        this->cells[i] = std::make_unique<DoganCell>(resources[i], false, numbers[i]);
    }

    static_cast<DoganCell*>(this->cells[BOARDSIZE/2].get())->setRobber(true);

}

std::array<DoganBoard::pips, DoganBoard::BOARDSIZE> DoganBoard::getNumberConfiguration(const std::string configValue) {
    std::array<pips, BOARDSIZE> numberOrder;
    std::uniform_int_distribution<uint32_t> pipRand(1, 6);

    if(configValue == "default"){
        // initialize vector with all numbers in board and shuffle
        std::vector<pips> initialNumberOrder = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
        std::shuffle(initialNumberOrder.begin(), initialNumberOrder.end(), rengine);
        
        // insert into final array
        size_t j = 0;
        for(size_t i = 0; i < BOARDSIZE; i++) {
            if(i == BOARDSIZE/2) {
                numberOrder[i] = Resource::INVAL;
            }
            numberOrder[i] = initialNumberOrder[j++];
        }
    }
    return numberOrder;
}

std::array<Resource, DoganBoard::BOARDSIZE> DoganBoard::getResourceConfiguration(const std::string configValue) {
    std::array<Resource, BOARDSIZE> resourceOrder;
    std::uniform_int_distribution<uint32_t> resourceRand(0, 4);

    if(configValue == "default"){
        // initialize vector with all resources in board and shuffle
        std::vector<Resource> initialResourceOrder = {
                                                        Resource::BRICK, Resource::BRICK, Resource::BRICK,
                                                        Resource::SHEEP, Resource::SHEEP, Resource::SHEEP,
                                                        Resource::STONE, Resource::STONE, Resource::STONE,
                                                        Resource::WHEAT, Resource::WHEAT, Resource::WHEAT,
                                                        Resource::WOOD,  Resource::WOOD,  Resource::WOOD,
                                                        static_cast<Resource>(resourceRand(rengine)), 
                                                        static_cast<Resource>(resourceRand(rengine)), 
                                                        static_cast<Resource>(resourceRand(rengine))
                                                    };
        std::shuffle(initialResourceOrder.begin(), initialResourceOrder.end(), rengine);

        // insert into final array
        size_t j = 0;
        for(size_t i = 0; i < BOARDSIZE; i++) {
            if(i == BOARDSIZE/2) {
                resourceOrder[i] = Resource::INVAL;
            }
            resourceOrder[i] = initialResourceOrder[j++];
        }
    }
    return resourceOrder;
}

std::string DoganBoard::toString() {
    std::ostringstream oss;
    for(size_t i = 0; i < BOARDSIZE; i++) {
        oss << "Cell " << i << ": " << this->cells[i]->toString() << "\n";
    }
    return oss.str();
}
