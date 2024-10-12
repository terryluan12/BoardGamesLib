#pragma once

#include <string>
#include <vector>
#include "../common.h"
#include "enums.h"
#include "default.h"



class DoganConfig {
    public:
        // add port locations
        DoganConfig(void) : 
                    boardSize(configDefault::tileLocations.size()), 
                    tileLocations(configDefault::tileLocations),
                    numberConfiguration(configDefault::numberConfig), 
                    parity(configDefault::parity),
                    resourceConfiguration(configDefault::resourceConfig),
                    robberPosition(configDefault::robberPosition){};

        size_t boardSize;
        NumberConfiguration numberConfiguration;
        Parity parity; // Parity + Coordinate System is based on https://www.redblobgames.com/grids/hexagons/
        ResourceConfiguration resourceConfiguration;
        Coordinate robberPosition;
        std::vector<Coordinate> tileLocations;

        std::vector<pip> getNumberConfiguration(std::mt19937 rengine);
        std::vector<Resource> getResourceConfiguration(std::mt19937 rengine);
};