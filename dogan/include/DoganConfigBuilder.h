#pragma once

#include "DoganConfig.h"
#include <array>
#include <vector>

using PublicCoordinate2D = std::array<int, 2>;
using PublicConfiguration = std::array<int, 2>;

class DoganConfigBuilder {
public:
  DoganConfigBuilder &setBoardSize(size_t boardSize);
  DoganConfigBuilder &setRobberLocation(PublicCoordinate2D robberLocations);
  DoganConfigBuilder &setTotalStructureCount(std::array<int, 3> totalPlayerStructureCount);
  DoganConfigBuilder &setTileLocations(std::vector<PublicCoordinate2D> tileLocations);
  DoganConfigBuilder &setResourceCount(std::array<size_t, 5> resourceCount);
  DoganConfigBuilder &setDevelopmentCount(std::array<size_t, 5> developmentCount);
  DoganConfigBuilder &setDevelopmentConfig(PublicConfiguration developmentConfig);
  DoganConfigBuilder &setNumberConfig(PublicConfiguration numberConfig);
  DoganConfigBuilder &setPortResourceConfig(PublicConfiguration portResourceConfig);
  DoganConfigBuilder &setResourceConfig(PublicConfiguration resourceConfig);
  DoganConfigBuilder &
  setDevelopmentLocations(std::vector<DevelopmentType> developmentConfigurations);
  DoganConfigBuilder &setNumberLocations(std::vector<int> numberLocations);
  DoganConfigBuilder &
  setPortLocations(std::vector<std::vector<std::pair<PublicCoordinate2D, std::string>>> portLocations);
  DoganConfigBuilder &setResources(std::vector<ResourceType> resourceLocations);
  DoganConfigBuilder &setPortResources(std::vector<ResourceType> portResources);
  DoganConfig build();

private:
  DoganConfig config;
};