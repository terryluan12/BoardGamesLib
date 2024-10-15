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
                    initialResourceCount(configDefault::initialResourceCount),
                    initialDevelopmentCount(configDefault::initialDevelopmentCount),
                    initialNumberConfig(configDefault::initialNumberConfig),
                    initialPortResourceConfig(configDefault::initialPortResourceConfig),
                    initialResourceConfig(configDefault::initialResourceConfig),
                    initialNumberLocations(configDefault::initialNumberLocations),
                    initialPortLocations(configDefault::initialPortLocations),
                    initialRobberLocation(configDefault::initialRobberLocation),
                    initialTileLocations(configDefault::initialTileLocations), 
                    initialResources(configDefault::initialResources),
                    initialPortResources(configDefault::initialPortResources){
                        const auto &it = std::find(initialTileLocations.begin(), initialTileLocations.end(), initialRobberLocation);
                        if(it == initialTileLocations.end()) {
                            throw std::invalid_argument("Robber location must be a valid tile location");
                        }
                        robberIndex = std::distance(initialTileLocations.begin(), it);
                    };

        std::vector<pip> getNumbers(std::mt19937 rengine);
        std::vector<ResourceType> getPortResources(std::mt19937 rengine);
        std::vector<ResourceType> getResources(std::mt19937 rengine);
        std::vector<DoganPort> getPorts(std::mt19937 rengine);

        // Getters
        size_t getBoardSize(void) const;
        Parity getParity(void) const;

        Coordinate2D getRobberLocation(void) const;
        const std::vector<Coordinate2D> getTileLocations(void) const;
        const std::array<size_t, 5> getResourceCount(void) const;
        const std::array<size_t, 5> getDevelopmentCount(void) const;

        // Setters
        void setBoardSize(size_t s);
        void setParity(Parity p);

        void setResourceCount(std::array<size_t, 5> rc);
        void setDevelopmentCount(std::array<size_t, 5> dc);

        void setNumberConfig(OrderConfiguration nc);
        void setPortResourceConfig(OrderConfiguration prc);
        void setResourceConfig(OrderConfiguration rc);
        
        void setNumberLocations(std::vector<pip> nl);
        void setPortLocations(std::vector<std::vector<DoganVertex>> pl);
        void setRobberLocation(Coordinate2D irl);
        void setTileLocations(const std::vector<Coordinate2D>& tl);
        
        void setResources(const std::vector<ResourceType>& r);
        void setPortResources(const std::vector<ResourceType>& pr);

    private:
    
        size_t boardSize;
        Parity parity; // Parity + Coordinate System is based on https://www.redblobgames.com/grids/hexagons/
        
        // Initial Counts
        std::array<size_t, 5> initialResourceCount;
        std::array<size_t, 5> initialDevelopmentCount;

        // Initial Configurations
        OrderConfiguration initialNumberConfig;
        OrderConfiguration initialPortResourceConfig;
        OrderConfiguration initialResourceConfig;

        // Initial Locations
        std::vector<pip> initialNumberLocations;
        std::vector<std::vector<DoganVertex>> initialPortLocations;
        Coordinate2D initialRobberLocation;
        std::vector<Coordinate2D> initialTileLocations;

        // Initial Resources
        std::vector<ResourceType> initialResources;
        std::vector<ResourceType> initialPortResources;

        size_t robberIndex;
        
};