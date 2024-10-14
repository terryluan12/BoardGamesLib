#pragma once

#include "enums.h"
#include "Coordinate.h"
#include "DoganVertex.h"
#include <vector>

namespace configDefault {
    inline const ResourceConfiguration resourceConfig = ResourceConfiguration::DEFAULT;
    inline const NumberConfiguration numberConfig = NumberConfiguration::DEFAULT;
    inline std::vector<std::tuple<DoganVertex, DoganVertex>> portLocations =    {
                                                                    {{Direction::NORTH, {1, 0}}, {Direction::NORTHWEST, {1, 0}}},
                                                                    {{Direction::NORTH, {2, 0}}, {Direction::NORTHWEST, {2, 0}}},
                                                                    {{Direction::NORTHWEST, {0, 1}}, {Direction::SOUTHWEST, {0, 1}}},
                                                                    {{Direction::NORTH, {3, 1}}, {Direction::NORTHEAST, {3, 1}}},
                                                                    {{Direction::NORTHEAST, {4, 2}}, {Direction::SOUTHEAST, {4, 2}}},
                                                                    {{Direction::NORTHWEST, {0, 3}}, {Direction::SOUTHEAST, {0, 3}}},
                                                                    {{Direction::SOUTHWEST, {3, 3}}, {Direction::SOUTH, {3, 3}}},
                                                                    {{Direction::SOUTHWEST, {1, 4}}, {Direction::SOUTH, {1, 4}}},
                                                                    {{Direction::SOUTH, {2, 4}}, {Direction::SOUTHEAST, {2, 4}}}
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

    inline const std::array<size_t, 5> resourceCount = {19, 19, 19, 19, 19};
    inline const std::array<size_t, 5> developmentCount = {5, 2, 2, 2, 2};
}