#pragma once

#include "DoganPort.h"
#include "DoganVertex.h"
#include "common.h"
#include "defaultConfiguration.h"
#include "enums.h"
#include <algorithm>
#include <ostream>
#include <random>
#include <vector>

class DoganConfig {
public:
  // add port locations
  DoganConfig(void)
      : boardSize(configDefault::initialTileLocations.size()),
        totalStructureCount(configDefault::totalStructureCount),
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
        initialPortResources(configDefault::initialPortResources) {
    const auto &it =
        std::find(initialTileLocations.begin(), initialTileLocations.end(),
                  initialRobberLocation);
    if (it == initialTileLocations.end()) {
      throw std::invalid_argument(
          "Robber location must be a valid tile location");
    }
    robberIndex = std::distance(initialTileLocations.begin(), it);
  };

  std::vector<pip> getNumbers(std::mt19937 rengine);
  std::vector<ResourceType> getPortResources(std::mt19937 rengine);
  std::vector<ResourceType> getResources(std::mt19937 rengine);
  std::vector<DoganPort> getPorts(std::mt19937 rengine);
  std::vector<DevelopmentType> getDevelopments(std::mt19937 rengine);

  // Getters
  size_t getBoardSize(void) const;
  std::array<int, 3> getTotalStructureCount(void) const;

  Coordinate2D getRobberLocation(void) const;
  const std::vector<Coordinate2D> getTileLocations(void) const;
  const std::array<size_t, 5> getResourceCount(void) const;
  const std::array<size_t, 5> getDevelopmentCount(void) const;

  // Setters
  void setBoardSize(size_t s);
  void setTotalStructureCount(std::array<int, 3> tsc);

  void setResourceCount(std::array<size_t, 5> rc);
  void setDevelopmentCount(std::array<size_t, 5> dc);

  void setDevelopmentConfig(Configuration dc);
  void setNumberConfig(Configuration nc);
  void setPortResourceConfig(Configuration prc);
  void setResourceConfig(Configuration rc);

  void setDevelopmentLocations(std::vector<DevelopmentType> dl);
  void setNumberLocations(std::vector<pip> nl);
  void setPortLocations(std::vector<std::vector<std::pair<std::array<int, 2>, std::string>>> pls);
  void setRobberLocation(Coordinate2D irl);
  void setTileLocations(std::vector<Coordinate2D> tl);

  void setResources(std::vector<ResourceType> r);
  void setPortResources(std::vector<ResourceType> pr);

private:
  size_t boardSize;
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
  std::vector<std::vector<DoganVertex>> initialPortLocations;
  Coordinate2D initialRobberLocation;
  // Coordinate System is based on
  // https://www.redblobgames.com/grids/hexagons/
  std::vector<Coordinate2D> initialTileLocations;

  // Initial Resources
  std::vector<ResourceType> initialResources;
  std::vector<ResourceType> initialPortResources;

  size_t robberIndex;
};