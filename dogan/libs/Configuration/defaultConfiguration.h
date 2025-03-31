#pragma once

#include "Coordinate.h"
#include "Port.h"
#include "config.enum.h"
#include "Config.h"
#include <vector>

namespace Dogan {
namespace configDefault {
    using VertexPrimitive = std::tuple<Coordinate2D, Direction>;

    inline const std::vector<Coordinate2D> tileLocations = { 
                {0, 0}, {1, 0}, {2, 0}, 
            {-1, 1}, {0, 1}, {1, 1}, {2, 1}, 
            {-2, 2}, {-1, 2}, {1, 2}, {2, 2},
            {-2, 3}, {-1, 3}, {0, 3}, {1, 3},
                {-2, 4}, {-1, 4}, {0, 4} 
    };

    inline std::vector<std::set<VertexPrimitive>> portLocations = {
        {{{1, 0}, Direction::NORTH},        {{1, 0}, Direction::NORTHWEST}},
        {{{2, 0}, Direction::NORTH},        {{2, 0}, Direction::NORTHWEST}},
        {{{0, 1}, Direction::NORTHWEST},    {{0, 1}, Direction::SOUTHWEST}},
        {{{3, 1}, Direction::NORTH},        {{3, 1}, Direction::NORTHEAST}},
        {{{4, 2}, Direction::NORTHEAST},    {{4, 2}, Direction::SOUTHEAST}},
        {{{0, 3}, Direction::NORTHWEST},    {{0, 3}, Direction::SOUTHEAST}},
        {{{3, 3}, Direction::SOUTHWEST},    {{3, 3}, Direction::SOUTH}},
        {{{1, 4}, Direction::SOUTHWEST},    {{1, 4}, Direction::SOUTH}},
        {{{2, 4}, Direction::SOUTH},        {{2, 4}, Direction::SOUTHEAST}}};
    
    inline const Coordinate2D robberLocation = {0, 2};
    
    // Default Counts
    inline const std::array<int, 3> totalStructureCount = {5, 4, 15};
    inline const std::array<int, 5> resourceCount = {19, 19, 19, 19, 19};
    inline const std::array<int, 5> developmentCount = {5, 2, 2, 2, 2};

    // Default Orders
    inline const std::vector<ResourceType> boardResourceOrder = {
        ResourceType::BRICK, ResourceType::BRICK, ResourceType::BRICK,
        ResourceType::SHEEP, ResourceType::SHEEP, ResourceType::SHEEP,
        ResourceType::STONE, ResourceType::STONE, ResourceType::STONE,
        ResourceType::WHEAT, ResourceType::WHEAT, ResourceType::WHEAT,
        ResourceType::WOOD,  ResourceType::WOOD,  ResourceType::WOOD,
        ResourceType::OTHER, ResourceType::OTHER, ResourceType::OTHER
    };
    
    inline const std::vector<ResourceType> portResourceOrder = {
        ResourceType::BRICK, ResourceType::WOOD, ResourceType::SHEEP, 
        ResourceType::WHEAT, ResourceType::STONE, ResourceType::OTHER,
        ResourceType::OTHER, ResourceType::OTHER, ResourceType::OTHER
    };
    inline const std::vector<pip> numberOrder = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
    inline const std::vector<DevelopmentType> developmentOrder = {
                                                                            DevelopmentType::VICPOINT, DevelopmentType::VICPOINT, DevelopmentType::VICPOINT, DevelopmentType::VICPOINT, DevelopmentType::VICPOINT, 
                                                                            DevelopmentType::MONOPOLY, DevelopmentType::MONOPOLY, 
                                                                            DevelopmentType::SOLDIER, DevelopmentType::SOLDIER, 
                                                                            DevelopmentType::BUILDROAD, DevelopmentType::BUILDROAD,
                                                                            DevelopmentType::TAKETWO, DevelopmentType::TAKETWO
                                                                            };

    // Default Configurations
    inline const Configuration boardResourceConfig = {OrderConfiguration::DEFAULT, ReplaceConfiguration::DEFAULT};
    inline const Configuration portResourceConfig = {OrderConfiguration::DEFAULT, ReplaceConfiguration::DEFAULT};
    inline const Configuration numberConfig = {OrderConfiguration::DEFAULT, ReplaceConfiguration::DEFAULT};
    inline const Configuration developmentConfig = {OrderConfiguration::DEFAULT, ReplaceConfiguration::DEFAULT};

}
}