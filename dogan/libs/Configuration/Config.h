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
      : tileLocations(configDefault::tileLocations),
        portLocations(configDefault::portLocations),
        robberLocation(configDefault::robberLocation),
        totalStructureCount(configDefault::totalStructureCount),
        resourceCount(configDefault::resourceCount),
        developmentCount(configDefault::developmentCount),
        boardResourceOrder(configDefault::boardResourceOrder),
        portResourceOrder(configDefault::portResourceOrder),
        numberOrder(configDefault::numberOrder),
        developmentOrder(configDefault::developmentOrder),
        boardResourceConfig(configDefault::boardResourceConfig),
        portResourceConfig(configDefault::portResourceConfig),
        numberConfig(configDefault::numberConfig),
        developmentConfig(configDefault::developmentConfig){};

  const std::vector<Coordinate2D> getTileLocations(void) const;
  const std::vector<std::set<VertexPrimitive>> getPortLocations(void) const;
  Coordinate2D getRobberLocation(void) const;

  std::array<int, 3> getTotalStructureCount(void) const;
  const std::array<size_t, 5> getResourceCount(void) const;
  const std::array<size_t, 5> getDevelopmentCount(void) const;

  std::vector<DevelopmentType> getDevelopmentOrder();
  std::vector<ResourceType> getBoardResourceOrder();
  std::vector<ResourceType> getPortResourceOrder();
  std::vector<pip> getNumberOrder();

  friend class ConfigBuilder;

private:
  void setTileLocations(std::vector<Coordinate2D> tl);
  void setPortLocations(std::vector<std::set<VertexPrimitive>> pls);
  void setPortLocations(std::vector<std::vector<VertexPrimitive>> pls);
  void setRobberLocation(Coordinate2D irl);

  void setTotalStructureCount(std::array<int, 3> tsc);
  void setResourceCount(std::array<size_t, 5> rc);
  void setDevelopmentCount(std::array<size_t, 5> dc);

  void setBoardResourceOrder(std::vector<ResourceType> r);
  void setPortResourceOrder(std::vector<ResourceType> pr);
  void setNumberOrder(std::vector<pip> nl);
  void setDevelopmentOrder(std::vector<DevelopmentType> dl);

  void setBoardResourceConfig(Configuration rc);
  void setPortResourceConfig(Configuration prc);
  void setNumberConfig(Configuration nc);
  void setDevelopmentConfig(Configuration dc);

  // Coordinate System is based on
  // https://www.redblobgames.com/grids/hexagons/
  std::vector<Coordinate2D> tileLocations;
  std::vector<std::set<VertexPrimitive>> portLocations;
  Coordinate2D robberLocation;

  // Counts
  std::array<int, 3> totalStructureCount; // {Villages, Cities, Roads}
  std::array<size_t, 5> resourceCount;
  std::array<size_t, 5> developmentCount;

  // Orders
  std::vector<ResourceType> boardResourceOrder;
  std::vector<ResourceType> portResourceOrder;
  std::vector<pip> numberOrder;
  std::vector<DevelopmentType> developmentOrder;

  // Configurations
  Configuration boardResourceConfig;
  Configuration portResourceConfig;
  Configuration numberConfig;
  Configuration developmentConfig;
};
} // namespace Dogan