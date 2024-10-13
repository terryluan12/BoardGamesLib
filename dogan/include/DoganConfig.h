#pragma once

#include <vector>
#include "common.h"
#include "enums.h"
#include "default.h"
#include "DoganVertex.h"

class DoganConfig {
    public:
        // add port locations
        DoganConfig(void) : 
                    boardSize(configDefault::tileLocations.size()), 
                    numberConfiguration(configDefault::numberConfig), 
                    parity(configDefault::parity),
                    portLocations(configDefault::portLocations),
                    resourceConfiguration(configDefault::resourceConfig),
                    robberPosition(configDefault::robberPosition),
                    tileLocations(configDefault::tileLocations){};

        size_t boardSize;
        NumberConfiguration numberConfiguration;
        Parity parity; // Parity + Coordinate System is based on https://www.redblobgames.com/grids/hexagons/
        std::vector<std::tuple<DoganVertex, DoganVertex>> portLocations;
        ResourceConfiguration resourceConfiguration;
        Cell2D robberPosition;
        std::vector<Cell2D> tileLocations;

        std::vector<pip> getNumberConfiguration(std::mt19937 rengine);
        std::vector<Resource> getResourceConfiguration(std::mt19937 rengine);
};