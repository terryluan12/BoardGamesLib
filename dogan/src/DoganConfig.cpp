#include "DoganConfig.h"
#include <algorithm>
#include <iostream>
#include <random>

std::vector<pip> DoganConfig::getNumberConfiguration(std::mt19937 rengine) {
    std::uniform_int_distribution<uint32_t> pipRand(1, 6);
    size_t sizeDifference = boardSize - numberOrder.size();

    if(sizeDifference != 0) {
        
        if(sizeDifference != 0) {
            std::cerr   << "WARNING: Board size (" 
                        << boardSize
                        << ") does not match Number Order size ("
                        << numberOrder.size() 
                        << "). If this is not intended, please fix this\n";
        }
        if(sizeDifference > 0) {
            for(size_t i = 0; i < sizeDifference; i++) {
                numberOrder.push_back(pipRand(rengine));
            }
        }
    }
    
    switch(numberOrderConfiguration) {
        case OrderConfiguration::DEFAULT:
        case OrderConfiguration::SHUFFLE:
            std::shuffle(numberOrder.begin(), numberOrder.end(), rengine);
            break;
        case OrderConfiguration::EXACT:
            break;
    }
    return numberOrder;
}


std::vector<ResourceType> DoganConfig::getPortConfiguration(std::mt19937 rengine) {
    std::uniform_int_distribution<uint32_t> resourceRand(0, 4);
    size_t sizeDifference = portLocations.size() - portOrder.size();

    if(sizeDifference != 0) {
        
        if(sizeDifference != 0) {
            std::cerr   << "WARNING: Port amount (" 
                        << portLocations.size()
                        << ") does not match Port Order size ("
                        << portOrder.size() 
                        << "). If this is not intended, please fix this\n";
        }
        if(sizeDifference > 0) {
            for(size_t i = 0; i < sizeDifference; i++) {
                portOrder.push_back(static_cast<ResourceType>(resourceRand(rengine)));
            }
        }
    }

    switch(resourceOrderConfiguration) {
        case OrderConfiguration::DEFAULT:
        case OrderConfiguration::SHUFFLE:
            std::shuffle(portOrder.begin(), portOrder.end(), rengine);
            break;
        case OrderConfiguration::EXACT:
            break;
    }
    return portOrder;
}



std::vector<ResourceType> DoganConfig::getResourceConfiguration(std::mt19937 rengine) {
    std::uniform_int_distribution<uint32_t> resourceRand(0, 4);
    size_t sizeDifference = boardSize - resourceOrder.size();

    if(sizeDifference != 0) {
        
        if(sizeDifference != 0) {
            std::cerr   << "WARNING: Board size (" 
                        << boardSize
                        << ") does not match Resource Order size ("
                        << resourceOrder.size() 
                        << "). If this is not intended, please fix this\n";
        }
        if(sizeDifference > 0) {
            for(size_t i = 0; i < sizeDifference; i++) {
                resourceOrder.push_back(static_cast<ResourceType>(resourceRand(rengine)));
            }
        }
    }

    switch(resourceOrderConfiguration) {
        case OrderConfiguration::DEFAULT:
        case OrderConfiguration::SHUFFLE:
            std::shuffle(resourceOrder.begin(), resourceOrder.end(), rengine);
            break;
        case OrderConfiguration::EXACT:
            break;
    }
    return resourceOrder;
}



std::vector<DoganPort> DoganConfig::getPortLocations(std::mt19937 rengine) {
    std::vector<DoganPort> ports;
    std::vector<ResourceType> portConfiguration = getPortConfiguration(rengine);

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