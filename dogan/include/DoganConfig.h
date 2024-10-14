#pragma once

#include "common.h"
#include "enums.h"
#include "default.h"
#include "DoganPort.h"
#include "DoganVertex.h"
#include <ostream>
#include <vector>
#include <random>

class DoganConfig {
    public:
        // add port locations
        DoganConfig(void) : 
                    boardSize(configDefault::tileLocations.size()), 
                    parity(configDefault::parity),
                    robberPosition(configDefault::robberPosition),
                    tileLocations(configDefault::tileLocations), 
                    resourceCount(configDefault::resourceCount),
                    developmentCount(configDefault::developmentCount),
                    numberConfiguration(configDefault::numberConfig),
                    resourceConfiguration(configDefault::resourceConfig),
                    portConfiguration(configDefault::portConfiguration),
                    portLocations(configDefault::portLocations){};

        size_t boardSize;
        Parity parity; // Parity + Coordinate System is based on https://www.redblobgames.com/grids/hexagons/
        Coordinate2D robberPosition;
        std::vector<Coordinate2D> tileLocations;
        
        std::array<size_t, 5> resourceCount;
        std::array<size_t, 5> developmentCount;

        std::vector<pip> getNumberConfiguration(std::mt19937 rengine);
        std::vector<ResourceType> getResourceConfiguration(std::mt19937 rengine);
        std::vector<DoganPort> getPortLocations(std::mt19937 rengine);
    private:
        NumberConfiguration numberConfiguration;
        ResourceConfiguration resourceConfiguration;
        std::vector<ResourceType> portConfiguration;
        std::vector<std::vector<DoganVertex>> portLocations;
        
};