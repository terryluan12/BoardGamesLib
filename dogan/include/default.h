#pragma once

#include <vector>
#include "enums.h"
#include "common.h"
#include "DoganVertex.h"

namespace configDefault {
    inline const ResourceConfiguration resourceConfig = ResourceConfiguration::DEFAULT;
    inline const NumberConfiguration numberConfig = NumberConfiguration::DEFAULT;
    inline std::vector<std::tuple<DoganVertex, DoganVertex>> portLocations =     {
                                                                    {{Direction::NORTH, std::make_tuple(1, 0)}, {Direction::NORTHWEST, std::make_tuple(1, 0)}},
                                                                    {{Direction::NORTH, std::make_tuple(2, 0)}, {Direction::NORTHWEST, std::make_tuple(2, 0)}},
                                                                    {{Direction::NORTHWEST, std::make_tuple(0, 1)}, {Direction::SOUTHWEST, std::make_tuple(0, 1)}},
                                                                    {{Direction::NORTH, std::make_tuple(3, 1)}, {Direction::NORTHEAST, std::make_tuple(3, 1)}},
                                                                    {{Direction::NORTHEAST, std::make_tuple(4, 2)}, {Direction::SOUTHEAST, std::make_tuple(4, 2)}},
                                                                    {{Direction::NORTHWEST, std::make_tuple(0, 3)}, {Direction::SOUTHEAST, std::make_tuple(0, 3)}},
                                                                    {{Direction::SOUTHWEST, std::make_tuple(3, 3)}, {Direction::SOUTH, std::make_tuple(3, 3)}},
                                                                    {{Direction::SOUTHWEST, std::make_tuple(1, 4)}, {Direction::SOUTH, std::make_tuple(1, 4)}},
                                                                    {{Direction::SOUTH, std::make_tuple(2, 4)}, {Direction::SOUTHEAST, std::make_tuple(2, 4)}}
                                                                };
    inline const Parity parity = Parity::ODD;
    inline const std::vector<Coordinate> tileLocations =   { 
                                                                        {1, 0}, {2, 0}, {3, 0}, 
                                                                    {0, 1}, {1, 1}, {2, 1}, {3, 1}, 
                                                                {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2},
                                                                    {0, 3}, {1, 3}, {2, 3}, {3, 3},
                                                                        {1, 4}, {2, 4}, {3, 4} 
                                                    };
    inline const Coordinate robberPosition = {2, 2};
}