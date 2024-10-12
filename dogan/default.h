#pragma once

#include <string>
#include <vector>
#include "enums.h"
#include "../common.h"

namespace configDefault {
    const std::string resourceConfig = "default";
    const std::string numberConfig = "default";
    const Parity parity = Parity::ODD;
    const std::vector<Coordinate> tileLocations = { 
                                                                        {1, 0}, {2, 0}, {3, 0}, 
                                                                    {0, 1}, {1, 1}, {2, 1}, {3, 1}, 
                                                                {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2},
                                                                    {0, 3}, {1, 3}, {2, 3}, {3, 3},
                                                                        {1, 4}, {2, 4}, {3, 4} 
                                                                };
    const Coordinate robberPosition = {2, 2};
}