#pragma once

#include "common.h"
#include "defaultConfiguration.h"
#include "enums.h"
#include <algorithm>
#include <ostream>
#include <random>
#include <vector>

namespace Dogan {
using VertexPrimitive = std::pair<Coordinate2D, Direction>;

class ConfigBuilder;
class Config {
public:
  // add port locations
  Config(void)
      : totalStructureCount(configDefault::totalStructureCount),
        initialResourceCount(configDefault::initialResourceCount),
        initialDevelopmentCount(configDefault::initialDevelopmentCount),
        initialDevelopmentConfig(configDefault::initialDevelopmentConfig),
        initialNumberConfig(configDefault::initialNumberConfig),
        initialPortResourceConfig(configDefault::initialPortResourceConfig),
        initialResourceConfig(configDefault::initialResourceConfig),
        initialDevelopmentLocations(configDefault::initialDevelopmentLocations),
        initialNumberLocations(configDefault::initialNumberLocations),
        initialPortLocations(configDefault::initialPortLocations),
        initialRobberLocation(configDefault::initialRobberLocation),
        initialTileLocations(configDefault::initialTileLocations),
        initialResources(configDefault::initialResources),
        initialPortResources(configDefault::initialPortResources){};

  std::vector<pip> getNumbers();
  std::vector<ResourceType> getPortResources();
  std::vector<ResourceType> getResources();
  std::vector<std::set<VertexPrimitive>> getPortLocations();
  std::vector<DevelopmentType> getDevelopments();

  // Getters
  std::array<int, 3> getTotalStructureCount(void) const;

  Coordinate2D getRobberLocation(void) const;
  const std::vector<Coordinate2D> getTileLocations(void) const;
  const std::vector<std::set<VertexPrimitive>> getPortLocations(void) const;
  const std::array<size_t, 5> getResourceCount(void) const;
  const std::array<size_t, 5> getDevelopmentCount(void) const;
  friend class ConfigBuilder;

private:
  // Setters
  void setTotalStructureCount(std::array<int, 3> tsc);

  void setResourceCount(std::array<size_t, 5> rc);
  void setDevelopmentCount(std::array<size_t, 5> dc);

  void setDevelopmentConfig(Configuration dc);
  void setNumberConfig(Configuration nc);
  void setPortResourceConfig(Configuration prc);
  void setResourceConfig(Configuration rc);

  void setDevelopmentLocations(std::vector<DevelopmentType> dl);
  void setNumberLocations(std::vector<pip> nl);
  void setPortLocations(std::vector<std::set<VertexPrimitive>> pls);
  void setPortLocations(std::vector<std::vector<VertexPrimitive>> pls);
  void setRobberLocation(Coordinate2D irl);
  void setTileLocations(std::vector<Coordinate2D> tl);

  void setResources(std::vector<ResourceType> r);
  void setPortResources(std::vector<ResourceType> pr);
  std::array<int, 3> totalStructureCount; // {Villages, Cities, Roads}

  // Initial Counts
  std::array<size_t, 5> initialResourceCount;
  std::array<size_t, 5> initialDevelopmentCount;

  // Initial Configurations
  Configuration initialDevelopmentConfig;
  Configuration initialNumberConfig;
  Configuration initialPortResourceConfig;
  Configuration initialResourceConfig;

  // Initial Locations
  std::vector<DevelopmentType> initialDevelopmentLocations;
  std::vector<pip> initialNumberLocations;
  std::vector<std::set<VertexPrimitive>> initialPortLocations;
  Coordinate2D initialRobberLocation;
  // Coordinate System is based on
  // https://www.redblobgames.com/grids/hexagons/
  std::vector<Coordinate2D> initialTileLocations;

  // Initial Resources
  std::vector<ResourceType> initialResources;
  std::vector<ResourceType> initialPortResources;
};
} // namespace Dogan