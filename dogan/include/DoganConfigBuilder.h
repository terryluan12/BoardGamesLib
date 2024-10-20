#pragma once

#include "Config.h"
#include <array>
#include <vector>

namespace Dogan {
class ConfigBuilder {
public:
  ConfigBuilder &setBoardSize(size_t boardSize);
  ConfigBuilder &setRobberLocation(Coordinate2D robberLocations);
  ConfigBuilder &
  setTotalStructureCount(std::array<int, 3> totalPlayerStructureCount);
  ConfigBuilder &setTileLocations(std::vector<Coordinate2D> tileLocations);
  ConfigBuilder &setResourceCount(std::array<size_t, 5> resourceCount);
  ConfigBuilder &setDevelopmentCount(std::array<size_t, 5> developmentCount);
  ConfigBuilder &setDevelopmentConfig(Configuration developmentConfig);
  ConfigBuilder &setNumberConfig(Configuration numberConfig);
  ConfigBuilder &setPortResourceConfig(Configuration portResourceConfig);
  ConfigBuilder &setResourceConfig(Configuration resourceConfig);
  ConfigBuilder &setDevelopmentLocations(
      std::vector<DevelopmentType> developmentConfigurations);
  ConfigBuilder &setNumberLocations(std::vector<int> numberLocations);
  ConfigBuilder &
  setPortLocations(std::vector<std::vector<std::pair<Coordinate2D, Direction>>>
                       portLocations);
  ConfigBuilder &setResources(std::vector<int> resourceLocations);
  ConfigBuilder &setPortResources(std::vector<int> portResources);
  Config build();

private:
  Config config;
};
} // namespace Dogan