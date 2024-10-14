#pragma once

#include "config.enum.h"
#include "Coordinate.h"
#include "DoganPort.h"
#include "DoganVertex.h"
#include <vector>

namespace configDefault {
    inline const OrderConfiguration resourceOrderConfiguration = OrderConfiguration::DEFAULT;
    inline const OrderConfiguration numberOrderConfiguration = OrderConfiguration::DEFAULT;
    inline const OrderConfiguration portOrderConfiguration = OrderConfiguration::DEFAULT;
    inline const std::vector<ResourceType> resourceOrder = {
                                ResourceType::BRICK, ResourceType::BRICK, ResourceType::BRICK,
                                ResourceType::SHEEP, ResourceType::SHEEP, ResourceType::SHEEP,
                                ResourceType::STONE, ResourceType::STONE, ResourceType::STONE,
                                ResourceType::WHEAT, ResourceType::WHEAT, ResourceType::WHEAT,
                                ResourceType::WOOD,  ResourceType::WOOD,  ResourceType::WOOD,
                                ResourceType::OTHER, ResourceType::OTHER, ResourceType::OTHER
                            };
    inline const std::vector<ResourceType> portOrder = {
                                ResourceType::BRICK, ResourceType::WOOD, ResourceType::SHEEP, 
                                ResourceType::WHEAT, ResourceType::STONE, ResourceType::OTHER,
                                ResourceType::OTHER, ResourceType::OTHER, ResourceType::OTHER
                            };
    inline const std::vector<pip> numberOrder = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};

    inline std::vector<std::vector<DoganVertex>> portLocations =    {
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
    inline std::vector<ResourceType> portConfiguration = { 
                                                            ResourceType::BRICK, 
                                                            ResourceType::WOOD, 
                                                            ResourceType::SHEEP, 
                                                            ResourceType::WHEAT, 
                                                            ResourceType::BRICK, 
                                                            ResourceType::STONE 
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