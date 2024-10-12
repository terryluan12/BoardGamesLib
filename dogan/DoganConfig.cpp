#include <algorithm>
#include <random>
#include "DoganConfig.h"

std::vector<pip> DoganConfig::getNumberConfiguration(std::mt19937 rengine) {
    std::vector<pip> numberOrder;
    std::uniform_int_distribution<uint32_t> pipRand(1, 6);

    if(numberConfiguration == "default"){
        // initialize vector with all numbers in board and shuffle
        numberOrder = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
        std::shuffle(numberOrder.begin(), numberOrder.end(), rengine);
        
        numberOrder.insert(numberOrder.begin() + 9, 7);
    }
        return numberOrder;
}

std::vector<Resource> DoganConfig::getResourceConfiguration(std::mt19937 rengine) {
    std::vector<Resource> resourceOrder;
    std::uniform_int_distribution<uint32_t> resourceRand(0, 4);

    if(resourceConfiguration == "default"){
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