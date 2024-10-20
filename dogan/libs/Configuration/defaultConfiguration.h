#pragma once

#include "Coordinate.h"
#include "Port.h"
#include "config.enum.h"
#include <vector>

namespace Dogan {
namespace configDefault {

inline const std::array<int, 3> totalStructureCount = {5, 4, 15};
inline const Coordinate2D initialRobberLocation = {2, 2};

inline const std::vector<Coordinate2D> initialTileLocations = {
    {0, 0},  {1, 0},  {2, 0},  {-1, 1}, {0, 1}, {1, 1},  {2, 1},
    {-2, 2}, {-1, 2}, {0, 2},  {1, 2},  {2, 2}, {-2, 3}, {-1, 3},
    {0, 3},  {1, 3},  {-2, 4}, {-1, 4}, {0, 4}};

// Initial Counts
inline const std::array<size_t, 5> initialResourceCount = {19, 19, 19, 19, 19};
inline const std::array<size_t, 5> initialDevelopmentCount = {5, 2, 2, 2, 2};

// Default Configurations
inline const Configuration initialNumberConfig = {
    OrderConfiguration::DEFAULT, ReplaceConfiguration::DEFAULT};
inline const Configuration initialPortResourceConfig = {
    OrderConfiguration::DEFAULT, ReplaceConfiguration::DEFAULT};
inline const Configuration initialResourceConfig = {
    OrderConfiguration::DEFAULT, ReplaceConfiguration::DEFAULT};
inline const Configuration initialDevelopmentConfig = {
    OrderConfiguration::DEFAULT, ReplaceConfiguration::DEFAULT};

// Default Locations
inline const std::vector<DevelopmentType> initialDevelopmentLocations = {
    DevelopmentType::VICPOINT,  DevelopmentType::VICPOINT,
    DevelopmentType::VICPOINT,  DevelopmentType::VICPOINT,
    DevelopmentType::VICPOINT,  DevelopmentType::MONOPOLY,
    DevelopmentType::MONOPOLY,  DevelopmentType::SOLDIER,
    DevelopmentType::SOLDIER,   DevelopmentType::BUILDROAD,
    DevelopmentType::BUILDROAD, DevelopmentType::TAKETWO,
    DevelopmentType::TAKETWO};
inline const std::vector<pip> initialNumberLocations = {
    2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};

inline std::vector<std::vector<std::pair<Coordinate2D, Direction>>>
    initialPortLocations = {
        {{{1, 0}, Direction::NORTH}, {{1, 0}, Direction::NORTHWEST}},
        {{{2, 0}, Direction::NORTH}, {{2, 0}, Direction::NORTHWEST}},
        {{{0, 1}, Direction::NORTHWEST}, {{0, 1}, Direction::SOUTHWEST}},
        {{{3, 1}, Direction::NORTH}, {{3, 1}, Direction::NORTHEAST}},
        {{{4, 2}, Direction::NORTHEAST}, {{4, 2}, Direction::SOUTHEAST}},
        {{{0, 3}, Direction::NORTHWEST}, {{0, 3}, Direction::SOUTHEAST}},
        {{{3, 3}, Direction::SOUTHWEST}, {{3, 3}, Direction::SOUTH}},
        {{{1, 4}, Direction::SOUTHWEST}, {{1, 4}, Direction::SOUTH}},
        {{{2, 4}, Direction::SOUTH}, {{2, 4}, Direction::SOUTHEAST}}};

// Default Resources
inline const std::vector<ResourceType> initialResources = {
    ResourceType::BRICK, ResourceType::BRICK, ResourceType::BRICK,
    ResourceType::SHEEP, ResourceType::SHEEP, ResourceType::SHEEP,
    ResourceType::STONE, ResourceType::STONE, ResourceType::STONE,
    ResourceType::WHEAT, ResourceType::WHEAT, ResourceType::WHEAT,
    ResourceType::WOOD,  ResourceType::WOOD,  ResourceType::WOOD,
    ResourceType::OTHER, ResourceType::OTHER, ResourceType::OTHER};

inline const std::vector<ResourceType> initialPortResources = {
    ResourceType::BRICK, ResourceType::WOOD,  ResourceType::SHEEP,
    ResourceType::WHEAT, ResourceType::STONE, ResourceType::OTHER,
    ResourceType::OTHER, ResourceType::OTHER, ResourceType::OTHER};
} // namespace configDefault
} // namespace Dogan