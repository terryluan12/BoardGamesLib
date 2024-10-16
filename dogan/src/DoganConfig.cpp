#include "DoganConfig.h"
#include <algorithm>
#include <iostream>
#include <random>

std::vector<pip> DoganConfig::getNumbers(std::mt19937 rengine) {
    std::uniform_int_distribution<pip> pipRand(1, 6);
    size_t sizeDifference = boardSize - initialNumberLocations.size();
    
    switch(initialNumberConfig) {
        case OrderConfiguration::DEFAULT:
        case OrderConfiguration::SHUFFLE:

            if(sizeDifference-1 != 0) {
                std::cerr   << "WARNING: Board size (" 
                            << boardSize
                            << ") does not match Tile Number Config size ("
                            << initialNumberLocations.size() 
                            << "). You should not include 7 as a number. If this is not intended, please fix this\n";
                if(sizeDifference-1 > 0) {
                    for(size_t i = 0; i < sizeDifference; i++) {
                        initialNumberLocations.push_back(pipRand(rengine));
                    }
                }
            }

            std::replace(initialNumberLocations.begin(), initialNumberLocations.end(), -1, pipRand(rengine));
            std::shuffle(initialNumberLocations.begin(), initialNumberLocations.end(), rengine);
            initialNumberLocations.insert(initialNumberLocations.begin() + robberIndex, 7);
            break;
        case OrderConfiguration::EXACT:
            if(sizeDifference != 0) {
                throw std::invalid_argument("Error: Exact Number Configuration requires number of numbers equal to board size");
            }
            std::replace(initialNumberLocations.begin(), initialNumberLocations.end(), -1, pipRand(rengine));
            break;
    }
    return initialNumberLocations;
}

std::vector<ResourceType> DoganConfig::getPortResources(std::mt19937 rengine) {
    std::uniform_int_distribution<uint32_t> resourceRand(0, 4);
    size_t sizeDifference = initialPortLocations.size() - initialPortResources.size();
    

    switch(initialResourceConfig) {
        case OrderConfiguration::DEFAULT:
        case OrderConfiguration::SHUFFLE:

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

            std::replace(initialResources.begin(), initialResources.end(), ResourceType::OTHER, static_cast<ResourceType>(resourceRand(rengine)));
            std::shuffle(initialPortResources.begin(), initialPortResources.end(), rengine);
            break;
        case OrderConfiguration::EXACT:
            if(sizeDifference != 0) {
                throw std::invalid_argument("Error: Exact Resource Configuration requires number of resources equal to board size");
            }
            std::replace(initialResources.begin(), initialResources.end(), ResourceType::OTHER, static_cast<ResourceType>(resourceRand(rengine)));
            break;
    }
    return initialPortResources;
}

std::vector<ResourceType> DoganConfig::getResources(std::mt19937 rengine) {
    std::uniform_int_distribution<uint32_t> resourceRand(0, 4);
    size_t sizeDifference = boardSize - initialResources.size();


    switch(initialResourceConfig) {
        case OrderConfiguration::DEFAULT:
        case OrderConfiguration::SHUFFLE:
        
            if(sizeDifference-1 != 0) {
                    std::cerr   << "WARNING: Board size (" 
                                << boardSize
                                << ") does not match Resource size ("
                                << initialResources.size() 
                                << "). Do not include the ResourceType::OTHER for the Robber."
                                << "If this is not intended, please fix this\n";
                if(sizeDifference > 0) {
                    for(size_t i = 0; i < sizeDifference; i++) {
                        initialResources.push_back(static_cast<ResourceType>(resourceRand(rengine)));
                    }
                }
            }
            std::replace(initialResources.begin(), initialResources.end(), ResourceType::OTHER, static_cast<ResourceType>(resourceRand(rengine)));
            std::shuffle(initialResources.begin(), initialResources.end(), rengine);
            initialResources.insert(initialResources.begin() + robberIndex, ResourceType::OTHER);
            break;
        case OrderConfiguration::EXACT:
            std::replace(initialResources.begin(), initialResources.end(), ResourceType::OTHER, static_cast<ResourceType>(resourceRand(rengine)));
            break;
    }
    return initialResources;
}

std::vector<DevelopmentType> DoganConfig::getDevelopments(std::mt19937 rengine) {

    switch(initialDevelopmentConfig) {
        case OrderConfiguration::DEFAULT:
        case OrderConfiguration::SHUFFLE:
            std::shuffle(initialDevelopmentLocations.begin(), initialDevelopmentLocations.end(), rengine);
            break;
        case OrderConfiguration::EXACT:
            break;
    }
    return initialDevelopmentLocations;
}

std::vector<DoganPort> DoganConfig::getPorts(std::mt19937 rengine) {
    std::vector<DoganPort> ports;
    std::vector<ResourceType> portConfiguration = getPortResources(rengine);

    for(size_t i = 0; i < portConfiguration.size(); i++) {
        // portConfiguration is a vector of ResourceType
        // initialPortLocations is a vector of all vertices that the port touches
        // A DoganPort is created with a direction (portConfiguration[i]) and
        // a vector of all possible representations of a vertex
        std::vector<std::vector<DoganVertex>> portVertices;
        
        for(size_t j = 0; j < initialPortLocations[i].size(); j++) {
            // for vertex j get all equivalent vertex 
            // representations of vertex initialPortLocations[i][j]
            std::vector<DoganVertex>portVertexRepresentations{initialPortLocations[i][j].getCorrespondingVertices()};
            portVertexRepresentations.push_back(initialPortLocations[i][j]);
            portVertices.push_back(portVertexRepresentations);
        }
        // create the port and add it to the ports vector
        ports.emplace_back(portConfiguration[i], portVertices);
    }
    return ports;

}

// Getters

size_t DoganConfig::getBoardSize(void) const {
    return boardSize;
}

Parity DoganConfig::getParity(void) const {
    return parity;
}

std::array<size_t, 3> DoganConfig::getTotalStructureCount(void) const {
    return totalStructureCount;
}

Coordinate2D DoganConfig::getRobberLocation(void) const {
    return initialRobberLocation;
}

const std::vector<Coordinate2D> DoganConfig::getTileLocations(void) const {
    return initialTileLocations;
}

const std::array<size_t, 5> DoganConfig::getResourceCount(void) const {
    return initialResourceCount;
}

// Setters

void DoganConfig::setBoardSize(size_t s) {
    boardSize = s;
}

void DoganConfig::setParity(Parity p) {
    parity = p;
}

void DoganConfig::setTotalStructureCount(std::array<size_t, 3> tsc) {
    totalStructureCount = tsc;
}

void DoganConfig::setResourceCount(std::array<size_t, 5> rc) {
    initialResourceCount = rc;
}

void DoganConfig::setDevelopmentCount(std::array<size_t, 5> dc) {
    initialDevelopmentCount = dc;
}

void DoganConfig::setDevelopmentConfig(OrderConfiguration dc) {
    initialDevelopmentConfig = dc;
}

void DoganConfig::setNumberConfig(OrderConfiguration nc) {
    initialNumberConfig = nc;
}

void DoganConfig::setPortResourceConfig(OrderConfiguration prc) {
    initialPortResourceConfig = prc;
}

void DoganConfig::setResourceConfig(OrderConfiguration rc) {
    initialResourceConfig = rc;
}

void DoganConfig::setDevelopmentLocations(std::vector<DevelopmentType> dl) {
    initialDevelopmentLocations = dl;
}

void DoganConfig::setNumberLocations(std::vector<pip> nl) {
    initialNumberLocations = nl;
}

void DoganConfig::setPortLocations(std::vector<std::vector<DoganVertex>> pl) {
    initialPortLocations = pl;
}

void DoganConfig::setRobberLocation(Coordinate2D irl) {
    initialRobberLocation = irl;
}

void DoganConfig::setTileLocations(const std::vector<Coordinate2D>& tl) {
    initialTileLocations = tl;
}

void DoganConfig::setResources(const std::vector<ResourceType>& r) {
    initialResources = r;
}

void DoganConfig::setPortResources(const std::vector<ResourceType>& pr) {
    initialPortResources = pr;
}