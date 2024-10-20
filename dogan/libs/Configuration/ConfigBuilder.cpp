#include "Coordinate.h"
#include "DoganConfigBuilder.h"
#include "DoganExceptions.h"
#include "config.enum.h"

namespace Dogan {
ConfigBuilder &ConfigBuilder::setBoardSize(size_t boardSize) {
  config.setBoardSize(boardSize);
  return *this;
}

ConfigBuilder &ConfigBuilder::setRobberLocation(Coordinate2D robberLocations) {
  config.setRobberLocation(robberLocations);
  return *this;
}

ConfigBuilder &ConfigBuilder::setTotalStructureCount(
    std::array<int, 3> totalPlayerStructureCount) {
  config.setTotalStructureCount(totalPlayerStructureCount);
  return *this;
}

ConfigBuilder &
ConfigBuilder::setTileLocations(std::vector<Coordinate2D> tileLocations) {
  std::vector<Coordinate2D> tls;
  for (Coordinate2D tileLocation : tileLocations) {
    tls.emplace_back(tileLocation);
  }
  config.setTileLocations(tls);
  return *this;
}

ConfigBuilder &ConfigBuilder::setResourceCount(std::array<size_t, 5> rc) {
  config.setResourceCount(rc);
  return *this;
}

ConfigBuilder &ConfigBuilder::setDevelopmentCount(std::array<size_t, 5> dc) {
  config.setDevelopmentCount(dc);
  return *this;
}

ConfigBuilder &
ConfigBuilder::setDevelopmentConfig(Configuration developmentConfiguration) {
  config.setDevelopmentConfig(developmentConfiguration);
  return *this;
}

ConfigBuilder &
ConfigBuilder::setNumberConfig(Configuration numberConfiguration) {
  config.setNumberConfig(numberConfiguration);
  return *this;
}

ConfigBuilder &
ConfigBuilder::setPortResourceConfig(Configuration portResourceConfigurations) {
  config.setPortResourceConfig(portResourceConfigurations);
  return *this;
}

ConfigBuilder &
ConfigBuilder::setResourceConfig(Configuration resourceConfigurations) {
  config.setResourceConfig(resourceConfigurations);
  return *this;
}

ConfigBuilder &ConfigBuilder::setDevelopmentLocations(
    std::vector<DevelopmentType> developmentLocations) {
  config.setDevelopmentLocations(developmentLocations);
  return *this;
}

ConfigBuilder &
ConfigBuilder::setNumberLocations(std::vector<int> numberLocations) {
  config.setNumberLocations(numberLocations);
  return *this;
}

ConfigBuilder &ConfigBuilder::setPortLocations(
    std::vector<std::vector<std::pair<Coordinate2D, Direction>>>
        portLocations) {
  config.setPortLocations(portLocations);
  return *this;
}

ConfigBuilder &ConfigBuilder::setResources(std::vector<int> resources) {
  std::vector<ResourceType> r;
  for (int resource : resources) {
    r.emplace_back(static_cast<ResourceType>(resource));
  }
  config.setResources(r);
  return *this;
}

ConfigBuilder &ConfigBuilder::setPortResources(std::vector<int> portResources) {
  std::vector<ResourceType> pr;
  for (int resource : portResources) {
    pr.emplace_back(static_cast<ResourceType>(resource));
  }
  config.setPortResources(pr);
  return *this;
}

Config ConfigBuilder::build() { return config; }
} // namespace Dogan