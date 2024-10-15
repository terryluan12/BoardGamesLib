#include "DoganConfig.h"
#include <algorithm>
#include <iostream>
#include <random>

std::vector<pip> DoganConfig::getNumberConfiguration(std::mt19937 rengine) {
    std::uniform_int_distribution<uint32_t> pipRand(1, 6);
    size_t sizeDifference = boardSize - initialNumberLocations.size();

    if(sizeDifference != 0) {
        std::cerr   << "WARNING: Board size (" 
                    << boardSize
                    << ") does not match Tile Number Config size ("
                    << initialNumberLocations.size() 
                    << "). If this is not intended, please fix this\n";
        if(sizeDifference > 0) {
            for(size_t i = 0; i < sizeDifference; i++) {
                initialNumberLocations.push_back(pipRand(rengine));
            }
        }
    }
    
    switch(initialNumberConfig) {
        case OrderConfiguration::DEFAULT:
        case OrderConfiguration::SHUFFLE:
            std::shuffle(initialNumberLocations.begin(), initialNumberLocations.end(), rengine);
            break;
        case OrderConfiguration::EXACT:
            break;
    }
    initialNumberLocations.insert(initialNumberLocations.begin() + robberIndex, 7);
    return initialNumberLocations;
}


std::vector<ResourceType> DoganConfig::getPortConfiguration(std::mt19937 rengine) {
    std::uniform_int_distribution<uint32_t> resourceRand(0, 4);
    size_t sizeDifference = initialPortLocations.size() - initialPortResources.size();

    if(sizeDifference != 0) {
        std::cerr   << "WARNING: Amount of Ports (" 
                    << initialPortLocations.size()
                    << ") does not match Port Resources Config size ("
                    << initialPortResources.size() 
                    << "). If this is not intended, please fix this\n";
        if(sizeDifference > 0) {
            for(size_t i = 0; i < sizeDifference; i++) {
                initialPortResources.push_back(static_cast<ResourceType>(resourceRand(rengine)));
            }
        }
    }

    switch(initialResourceConfig) {
        case OrderConfiguration::DEFAULT:
        case OrderConfiguration::SHUFFLE:
            std::shuffle(initialPortResources.begin(), initialPortResources.end(), rengine);
            break;
        case OrderConfiguration::EXACT:
            break;
    }
    return initialPortResources;
}



std::vector<ResourceType> DoganConfig::getResourceConfiguration(std::mt19937 rengine) {
    std::uniform_int_distribution<uint32_t> resourceRand(0, 4);
    size_t sizeDifference = boardSize - initialResources.size();

    if(sizeDifference != 0) {
        
        if(sizeDifference != 0) {
            std::cerr   << "WARNING: Board size (" 
                        << boardSize
                        << ") does not match Resource size ("
                        << initialResources.size() 
                        << "). If this is not intended, please fix this\n";
        }
        if(sizeDifference > 0) {
            for(size_t i = 0; i < sizeDifference; i++) {
                initialResources.push_back(static_cast<ResourceType>(resourceRand(rengine)));
            }
        }
    }

    switch(initialResourceConfig) {
        case OrderConfiguration::DEFAULT:
        case OrderConfiguration::SHUFFLE:
            std::shuffle(initialResources.begin(), initialResources.end(), rengine);
            break;
        case OrderConfiguration::EXACT:
            break;
    }
    return initialResources;
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
        
        for(size_t j = 0; j < initialPortLocations[i].size(); j++) {
            // for vertex j get all equivalent vertex 
            // representations of vertex portLocations[i][j]
            std::vector<DoganVertex>portVertexRepresentations{initialPortLocations[i][j].getCorrespondingVertices()};
            portVertexRepresentations.push_back(initialPortLocations[i][j]);
            portVertices.push_back(portVertexRepresentations);
        }
        // create the port and add it to the ports vector
        ports.emplace_back(portConfiguration[i], portVertices);
    }
    return ports;

}