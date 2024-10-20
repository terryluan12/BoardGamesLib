#include "DoganConfigBuilder.h"
#include "Coordinate.h"
#include "DoganExceptions.h"
#include "config.enum.h"

DoganConfigBuilder &DoganConfigBuilder::setBoardSize(size_t boardSize) {
  config.setBoardSize(boardSize);
  return *this;
}

DoganConfigBuilder &
DoganConfigBuilder::setRobberLocation(Coordinate2D robberLocations) {
  config.setRobberLocation(robberLocations);
  return *this;
}

DoganConfigBuilder &DoganConfigBuilder::setTotalStructureCount(
    std::array<int, 3> totalPlayerStructureCount) {
  config.setTotalStructureCount(totalPlayerStructureCount);
  return *this;
}

DoganConfigBuilder &DoganConfigBuilder::setTileLocations(
    std::vector<Coordinate2D> tileLocations) {
  std::vector<Coordinate2D> tls;
  for (Coordinate2D tileLocation : tileLocations) {
    tls.emplace_back(tileLocation);
  }
  config.setTileLocations(tls);
  return *this;
}

DoganConfigBuilder &
DoganConfigBuilder::setResourceCount(std::array<size_t, 5> rc) {
  config.setResourceCount(rc);
  return *this;
}

DoganConfigBuilder &
DoganConfigBuilder::setDevelopmentCount(std::array<size_t, 5> dc) {
  config.setDevelopmentCount(dc);
  return *this;
}

DoganConfigBuilder &DoganConfigBuilder::setDevelopmentConfig(
    Configuration developmentConfiguration) {
  config.setDevelopmentConfig(developmentConfiguration);
  return *this;
}

DoganConfigBuilder &
DoganConfigBuilder::setNumberConfig(Configuration numberConfiguration) {
  config.setNumberConfig(numberConfiguration);
  return *this;
}

DoganConfigBuilder &DoganConfigBuilder::setPortResourceConfig(
    Configuration portResourceConfigurations) {
  config.setPortResourceConfig(portResourceConfigurations);
  return *this;
}

DoganConfigBuilder &DoganConfigBuilder::setResourceConfig(
    Configuration resourceConfigurations) {
  config.setResourceConfig(resourceConfigurations);
  return *this;
}

DoganConfigBuilder &DoganConfigBuilder::setDevelopmentLocations(
    std::vector<DevelopmentType> developmentLocations) {
  config.setDevelopmentLocations(developmentLocations);
  return *this;
}

DoganConfigBuilder &
DoganConfigBuilder::setNumberLocations(std::vector<int> numberLocations) {
  config.setNumberLocations(numberLocations);
  return *this;
}

DoganConfigBuilder &DoganConfigBuilder::setPortLocations(
    std::vector<std::vector<std::pair<Coordinate2D, Direction>>>
        portLocations) {
  config.setPortLocations(portLocations);
  return *this;
}

DoganConfigBuilder &
DoganConfigBuilder::setResources(std::vector<int> resources) {
  std::vector<ResourceType> r;
  for (int resource : resources) {
    r.emplace_back(static_cast<ResourceType>(resource));
  }
  config.setResources(r);
  return *this;
}

DoganConfigBuilder &
DoganConfigBuilder::setPortResources(std::vector<int> portResources) {
  std::vector<ResourceType> pr;
  for (int resource : portResources) {
    pr.emplace_back(static_cast<ResourceType>(resource));
  }
  config.setPortResources(pr);
  return *this;
}

DoganConfig DoganConfigBuilder::build() { return config; }