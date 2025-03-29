#pragma once

#include "Config.h"
#include "Coordinate.h"
#include "DoganResponse.h"
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
  ConfigBuilder &setTileLocations(std::vector<Coordinate2D> tileLocations);
  ConfigBuilder &
  setPortLocations(std::vector<std::set<VertexPrimitive>> portLocations);
  ConfigBuilder &
  setPortLocations(std::vector<std::vector<VertexPrimitive>> portLocations);
  ConfigBuilder &setRobberLocation(Coordinate2D robberLocations);
  ConfigBuilder &
  setTotalStructureCount(std::array<int, 3> totalPlayerStructureCount);
  ConfigBuilder &setResourceCount(std::array<size_t, 5> resourceCount);
  ConfigBuilder &setDevelopmentCount(std::array<size_t, 5> developmentCount);
  ConfigBuilder &setBoardResourceOrder(std::vector<int> boardResourceOrder);
  ConfigBuilder &setPortResourceOrder(std::vector<int> portResourceOrder);
  ConfigBuilder &setNumberOrder(std::vector<int> numberOrder);
  ConfigBuilder &
  setDevelopmentOrder(std::vector<DevelopmentType> developmentConfigurations);
  ConfigBuilder &setBoardResourceConfig(Configuration boardResourceConfig);
  ConfigBuilder &setPortResourceConfig(Configuration portResourceConfig);
  ConfigBuilder &setNumberConfig(Configuration numberConfig);
  ConfigBuilder &setDevelopmentConfig(Configuration developmentConfig);
  Response validate(bool throwError = true);
  Config build();

private:
  Config config;
  std::mt19937 rengine;
  std::array<int, 5> sizeDifferences;
};
} // namespace Dogan