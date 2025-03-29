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
  ConfigBuilder &setBoardResourceConfig(Configuration boardResourceConfig);
  ConfigBuilder &setDevelopmentOrder(
      std::vector<DevelopmentType> developmentConfigurations);
  ConfigBuilder &setNumberOrder(std::vector<int> numberOrder);
  ConfigBuilder &
  setPortLocations(std::vector<std::set<VertexPrimitive>> portLocations);
  ConfigBuilder &
  setPortLocations(std::vector<std::vector<VertexPrimitive>> portLocations);
  ConfigBuilder &setBoardResourceOrder(std::vector<int> boardResourceOrder);
  ConfigBuilder &setPortResourceOrder(std::vector<int> portResourceOrder);
  void validate(void);
  Config build();

private:
  Config config;
  std::mt19937 rengine;
  std::array<int, 5> sizeDifferences;
};
} // namespace Dogan