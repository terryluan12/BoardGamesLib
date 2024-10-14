#include "DoganConfig.h"
#include <algorithm>
#include <iostream>
#include <random>

std::vector<pip> DoganConfig::getNumberConfiguration(std::mt19937 rengine) {
    std::vector<pip> numberOrder;
    std::uniform_int_distribution<uint32_t> pipRand(1, 6);
    
    switch(numberConfiguration) {
        case NumberConfiguration::DEFAULT:
            if(boardSize != 19) {
                std::cerr << "Error: Board Size should be 19. It is " << boardSize;
                throw("Board Size should be 19");
            }
            // initialize vector with all numbers in board and shuffle
            numberOrder = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
            std::shuffle(numberOrder.begin(), numberOrder.end(), rengine);
            
            numberOrder.insert(numberOrder.begin() + 9, 7);
            break;
    }
    return numberOrder;
}

std::vector<ResourceType> DoganConfig::getResourceConfiguration(std::mt19937 rengine) {
    std::vector<ResourceType> resourceOrder;
    std::uniform_int_distribution<uint32_t> resourceRand(0, 4);

    switch(resourceConfiguration) {
        case ResourceConfiguration::DEFAULT:
            if(boardSize != 19) {
                std::cerr << "Error: Board Size should be 19. It is " << boardSize;
                throw("Board Size should be 19");
            }
            // initialize vector with all resources in board and shuffle
            resourceOrder = {
                                ResourceType::BRICK, ResourceType::BRICK, ResourceType::BRICK,
                                ResourceType::SHEEP, ResourceType::SHEEP, ResourceType::SHEEP,
                                ResourceType::STONE, ResourceType::STONE, ResourceType::STONE,
                                ResourceType::WHEAT, ResourceType::WHEAT, ResourceType::WHEAT,
                                ResourceType::WOOD,  ResourceType::WOOD,  ResourceType::WOOD,
                                static_cast<ResourceType>(resourceRand(rengine)), 
                                static_cast<ResourceType>(resourceRand(rengine)), 
                                static_cast<ResourceType>(resourceRand(rengine))
                            };
            std::shuffle(resourceOrder.begin(), resourceOrder.end(), rengine);

            // insert into final array
            resourceOrder.insert(resourceOrder.begin() + 9, ResourceType::OTHER);
            break;
    }
    return resourceOrder;
}

std::vector<DoganPort> DoganConfig::getPortLocations(std::mt19937 rengine) {
    std::vector<DoganPort> ports;
    size_t sizeDifference = portLocations.size() - portConfiguration.size();
    if(sizeDifference != 0) {
        std::cerr   << "WARNING: portLocations size (" 
                    << portLocations.size() 
                    << ") does not match portConfiguration size ("
                    << portConfiguration.size() 
                    << "). If this is not intended, please fix this\n";
        if(sizeDifference > 0) {
            for(size_t i = 0; i < sizeDifference; i++) {
                portConfiguration.push_back(ResourceType::OTHER);
            }
        }
    }

    // Shuffle the portConfiguration and then create the ports
    std::shuffle(portConfiguration.begin(), portConfiguration.end(), rengine);

    for(size_t i = 0; i < portConfiguration.size(); i++) {
        // portConfiguration is a vector of ResourceType
        // portLocations is a vector of all vertices that the port touches
        // A DoganPort is created with a direction (portConfiguration[i]) and
        // a vector of all possible representations of a vertex
        std::vector<std::vector<DoganVertex>> portVertices;
        
        for(size_t j = 0; j < portLocations[i].size(); j++) {
            // for vertex j get all equivalent vertex 
            // representations of vertex portLocations[i][j]
            std::vector<DoganVertex>portVertexRepresentations{portLocations[i][j].getCorrespondingVertices()};
            portVertexRepresentations.push_back(portLocations[i][j]);
            portVertices.push_back(portVertexRepresentations);
        }
        // create the port and add it to the ports vector
        ports.emplace_back(portConfiguration[i], portVertices);
    }
    return ports;

}