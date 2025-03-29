#pragma once

#include "Config.h"
#include "Coordinate.h"
#include <array>
#include <vector>

namespace Dogan {
/**
 * @brief A class to build a Config object
 *
 */
class ConfigBuilder {
public:
  ConfigBuilder(void) : rengine(std::random_device{}()){};
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
  setPortLocations(std::vector<std::set<VertexPrimitive>> portLocations);
  ConfigBuilder &
  setPortLocations(std::vector<std::vector<VertexPrimitive>> portLocations);
  ConfigBuilder &setResources(std::vector<int> resourceLocations);
  ConfigBuilder &setPortResources(std::vector<int> portResources);
  void validate(void);
  Config build();

private:
  Config config;
  std::mt19937 rengine;
  std::array<int, 5> sizeDifferences;
};
} // namespace Dogan