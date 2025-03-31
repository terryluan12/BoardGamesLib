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
  using Coordinate = std::array<int, 2>;
  using Point = std::pair<Coordinate, int>;
  using intConfig = std::array<int, 2>;

  ConfigBuilder(void) : rengine(std::random_device{}()){};
  ConfigBuilder &setTileLocations(std::vector<Coordinate> tileLocations);
  ConfigBuilder &
  setPortLocations(std::vector<std::vector<Point>> portLocations);
  ConfigBuilder &setRobberLocation(Coordinate robberLocations);
  ConfigBuilder &
  setTotalStructureCount(std::array<int, 3> totalPlayerStructureCount);
  ConfigBuilder &setResourceCount(std::array<int, 5> resourceCount);
  ConfigBuilder &setDevelopmentCount(std::array<int, 5> developmentCount);
  ConfigBuilder &setBoardResourceOrder(std::vector<int> boardResourceOrder);
  ConfigBuilder &setPortResourceOrder(std::vector<int> portResourceOrder);
  ConfigBuilder &setNumberOrder(std::vector<int> numberOrder);
  ConfigBuilder &
  setDevelopmentOrder(std::vector<int> developmentConfigurations);
  ConfigBuilder &setBoardResourceConfig(intConfig boardResourceConfig);
  ConfigBuilder &setPortResourceConfig(intConfig portResourceConfig);
  ConfigBuilder &setNumberConfig(intConfig numberConfig);
  ConfigBuilder &setDevelopmentConfig(intConfig developmentConfig);
  Response validate(bool throwError = true);
  Config build();

private:
  Config config;
  std::mt19937 rengine;
  std::array<int, 5> sizeDifferences;
};
} // namespace Dogan