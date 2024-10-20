#pragma once

#include "DoganConfig.h"
#include <array>
#include <vector>

class DoganConfigBuilder {
public:
  DoganConfigBuilder &setBoardSize(size_t boardSize);
  DoganConfigBuilder &setRobberLocation(Coordinate2D robberLocations);
  DoganConfigBuilder &
  setTotalStructureCount(std::array<int, 3> totalPlayerStructureCount);
  DoganConfigBuilder &setTileLocations(std::vector<Coordinate2D> tileLocations);
  DoganConfigBuilder &setResourceCount(std::array<size_t, 5> resourceCount);
  DoganConfigBuilder &
  setDevelopmentCount(std::array<size_t, 5> developmentCount);
  DoganConfigBuilder &setDevelopmentConfig(Configuration developmentConfig);
  DoganConfigBuilder &setNumberConfig(Configuration numberConfig);
  DoganConfigBuilder &setPortResourceConfig(Configuration portResourceConfig);
  DoganConfigBuilder &setResourceConfig(Configuration resourceConfig);
  DoganConfigBuilder &setDevelopmentLocations(
      std::vector<DevelopmentType> developmentConfigurations);
  DoganConfigBuilder &setNumberLocations(std::vector<int> numberLocations);
  DoganConfigBuilder &
  setPortLocations(std::vector<std::vector<std::pair<Coordinate2D, Direction>>>
                       portLocations);
  DoganConfigBuilder &setResources(std::vector<int> resourceLocations);
  DoganConfigBuilder &setPortResources(std::vector<int> portResources);
  DoganConfig build();

private:
  DoganConfig config;
};