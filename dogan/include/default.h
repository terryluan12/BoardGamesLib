#pragma once

#include <vector>
#include "enums.h"
#include "Coordinate.h"
#include "DoganVertex.h"

namespace configDefault {
    inline const ResourceConfiguration resourceConfig = ResourceConfiguration::DEFAULT;
    inline const NumberConfiguration numberConfig = NumberConfiguration::DEFAULT;
    inline std::vector<std::tuple<DoganVertex, DoganVertex>> portLocations =    {
                                                                    {{Direction::NORTH, Coordinate2D(1, 0)}, {Direction::NORTHWEST, Coordinate2D(1, 0)}},
                                                                    {{Direction::NORTH, Coordinate2D(2, 0)}, {Direction::NORTHWEST, Coordinate2D(2, 0)}},
                                                                    {{Direction::NORTHWEST, Coordinate2D(0, 1)}, {Direction::SOUTHWEST, Coordinate2D(0, 1)}},
                                                                    {{Direction::NORTH, Coordinate2D(3, 1)}, {Direction::NORTHEAST, Coordinate2D(3, 1)}},
                                                                    {{Direction::NORTHEAST, Coordinate2D(4, 2)}, {Direction::SOUTHEAST, Coordinate2D(4, 2)}},
                                                                    {{Direction::NORTHWEST, Coordinate2D(0, 3)}, {Direction::SOUTHEAST, Coordinate2D(0, 3)}},
                                                                    {{Direction::SOUTHWEST, Coordinate2D(3, 3)}, {Direction::SOUTH, Coordinate2D(3, 3)}},
                                                                    {{Direction::SOUTHWEST, Coordinate2D(1, 4)}, {Direction::SOUTH, Coordinate2D(1, 4)}},
                                                                    {{Direction::SOUTH, Coordinate2D(2, 4)}, {Direction::SOUTHEAST, Coordinate2D(2, 4)}}
                                                                };
    inline const Parity parity = Parity::ODD;
    inline const std::vector<Coordinate2D> tileLocations =   { 
                                                                        {1, 0}, {2, 0}, {3, 0}, 
                                                                    {0, 1}, {1, 1}, {2, 1}, {3, 1}, 
                                                                {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2},
                                                                    {0, 3}, {1, 3}, {2, 3}, {3, 3},
                                                                        {1, 4}, {2, 4}, {3, 4} 
                                                    };
    inline const Coordinate2D robberPosition = {2, 2};
}