#include <string>
#include <vector>
#include <tuple>
#include "../common.h"
#include "default.h"



class DoganConfig {
    public:
        // add port locations
        size_t boardSize;
        std::vector<Coordinate> tileLocations;
        std::string numberConfiguration;
        Parity parity;
        std::string resourceConfiguration;
        Coordinate robberPosition;
        DoganConfig(void) : 
                    boardSize(configDefault::tileLocations.size()), 
                    tileLocations(configDefault::tileLocations),
                    numberConfiguration(configDefault::numberConfig), 
                    parity(configDefault::parity),
                    resourceConfiguration(configDefault::resourceConfig),
                    robberPosition(configDefault::robberPosition){};
        
        std::vector<pip> getNumberConfiguration(std::mt19937 rengine);
        std::vector<Resource> getResourceConfiguration(std::mt19937 rengine);
};