#pragma once

#include "common.h"
#include "enums.h"
#include "default.h"
#include "DoganPort.h"
#include "DoganVertex.h"
#include <algorithm>
#include <ostream>
#include <vector>
#include <random>

class DoganConfig {
    public:
        // add port locations
        DoganConfig(void) : 
                    boardSize(configDefault::initialTileLocations.size()), 
                    parity(configDefault::parity),
                    initialRobberLocation(configDefault::initialRobberLocation),
                    initialTileLocations(configDefault::initialTileLocations), 
                    initialResourceCount(configDefault::initialResourceCount),
                    initialDevelopmentCount(configDefault::initialDevelopmentCount),
                    initialNumberConfig(configDefault::initialNumberConfig),
                    initialPortResourceConfig(configDefault::initialPortResourceConfig),
                    initialResourceConfig(configDefault::initialResourceConfig),
                    initialNumberLocations(configDefault::initialNumberLocations),
                    initialPortLocations(configDefault::initialPortLocations),
                    initialResources(configDefault::initialResources),
                    initialPortResources(configDefault::initialPortResources){
                        const auto &it = std::find(initialTileLocations.begin(), initialTileLocations.end(), initialRobberLocation);
                        if(it == initialTileLocations.end()) {
                            throw std::invalid_argument("Robber location must be a valid tile location");
                        }
                        robberIndex = std::distance(initialTileLocations.begin(), it);
                    };

        size_t boardSize;
        Parity parity; // Parity + Coordinate System is based on https://www.redblobgames.com/grids/hexagons/
        Coordinate2D initialRobberLocation;
        std::vector<Coordinate2D> initialTileLocations;
        
        // Initial Counts
        std::array<size_t, 5> initialResourceCount;
        std::array<size_t, 5> initialDevelopmentCount;

        std::vector<pip> getNumbers(std::mt19937 rengine);
        std::vector<ResourceType> getPortResources(std::mt19937 rengine);
        std::vector<ResourceType> getResources(std::mt19937 rengine);
        std::vector<DoganPort> getPorts(std::mt19937 rengine);

        void setNumberConfig(OrderConfiguration nc);
        void setPortResourceConfig(OrderConfiguration prc);
        void setResourceConfig(OrderConfiguration rc);
        
        void setNumberLocations(std::vector<pip> nl);
        void setPortLocations(std::vector<std::vector<DoganVertex>> pl);
        void setResources(const std::vector<ResourceType>& r);
        void setPortResources(const std::vector<ResourceType>& pr);
    private:
        // Default Configurations
        OrderConfiguration initialNumberConfig;
        OrderConfiguration initialPortResourceConfig;
        OrderConfiguration initialResourceConfig;

        // Default Locations
        std::vector<pip> initialNumberLocations;
        std::vector<std::vector<DoganVertex>> initialPortLocations;

        // Default Resources
        std::vector<ResourceType> initialResources;
        std::vector<ResourceType> initialPortResources;

        size_t robberIndex;
        
};