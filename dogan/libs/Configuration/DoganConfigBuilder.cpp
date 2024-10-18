#include "DoganConfigBuilder.h"
#include "Coordinate.h"
#include "DoganExceptions.h"
#include "config.enum.h"

DoganConfigBuilder &DoganConfigBuilder::setBoardSize(size_t boardSize) {
  config.setBoardSize(boardSize);
  return *this;
}

DoganConfigBuilder &DoganConfigBuilder::setRobberLocation(PublicCoordinate2D robberLocations) {
  config.setRobberLocation(robberLocations);
  return *this;
}

DoganConfigBuilder &
DoganConfigBuilder::setTotalStructureCount(std::array<int, 3> totalPlayerStructureCount) {
  config.setTotalStructureCount(totalPlayerStructureCount);
  return *this;
}

DoganConfigBuilder &
DoganConfigBuilder::setTileLocations(std::vector<PublicCoordinate2D> tileLocations) {
  std::vector<Coordinate2D> tls;
  for(PublicCoordinate2D tileLocation : tileLocations ) {
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

DoganConfigBuilder &DoganConfigBuilder::setDevelopmentConfig(PublicConfiguration developmentConfiguration) {
  if(developmentConfiguration[0] > 3 || developmentConfiguration[0] < 0 || developmentConfiguration[1] > 3 || developmentConfiguration[1] < 0) {
    throw InvalidTypeException("Error: Development Configuration is invalid");
  }

  Configuration dc = std::make_tuple(static_cast<OrderConfiguration>(developmentConfiguration[0]),
                                                      static_cast<ReplaceConfiguration>(developmentConfiguration[1]));

  config.setDevelopmentConfig(dc);
  return *this;
}

DoganConfigBuilder &DoganConfigBuilder::setNumberConfig(PublicConfiguration numberConfiguration) {
  if(numberConfiguration[0] > 3 || numberConfiguration[0] < 0 || numberConfiguration[1] > 3 || numberConfiguration[1] < 0) {
    throw InvalidTypeException("Error: Development Configuration is invalid");
  }
  
  Configuration nc = std::make_tuple(static_cast<OrderConfiguration>(numberConfiguration[0]),
                                                      static_cast<ReplaceConfiguration>(numberConfiguration[1]));

  config.setNumberConfig(nc);
  return *this;
}

DoganConfigBuilder &
DoganConfigBuilder::setPortResourceConfig(PublicConfiguration portResourceConfigurations) {
  if(portResourceConfigurations[0] > 3 || portResourceConfigurations[0] < 0 || portResourceConfigurations[1] > 3 || portResourceConfigurations[1] < 0) {
    throw InvalidTypeException("Error: Development Configuration is invalid");
  }

  Configuration prc = std::make_tuple(static_cast<OrderConfiguration>(portResourceConfigurations[0]),
                                                      static_cast<ReplaceConfiguration>(portResourceConfigurations[1]));

  config.setPortResourceConfig(prc);
  return *this;
}

DoganConfigBuilder &DoganConfigBuilder::setResourceConfig(PublicConfiguration resourceConfigurations) {
  if(resourceConfigurations[0] > 3 || resourceConfigurations[0] < 0 || resourceConfigurations[1] > 3 || resourceConfigurations[1] < 0) {
    throw InvalidTypeException("Error: Development Configuration is invalid");
  }
  
  Configuration rc = std::make_tuple(static_cast<OrderConfiguration>(resourceConfigurations[0]),
                                                      static_cast<ReplaceConfiguration>(resourceConfigurations[1]));
  config.setResourceConfig(rc);
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
    std::vector<std::vector<std::pair<PublicCoordinate2D, std::string>>> portLocations) {
  config.setPortLocations(portLocations);
  return *this;
}

DoganConfigBuilder &
DoganConfigBuilder::setResources(std::vector<int> resources) {
  std::vector<ResourceType> r;
  for(int resource : resources) {
    r.emplace_back(static_cast<ResourceType>(resource));
  }
  config.setResources(r);
  return *this;
}

DoganConfigBuilder &
DoganConfigBuilder::setPortResources(std::vector<int> portResources) {
  std::vector<ResourceType> pr;
  for(int resource : portResources) {
    pr.emplace_back(static_cast<ResourceType>(resource));
  }
  config.setPortResources(pr);
  return *this;
}

DoganConfig DoganConfigBuilder::build() { return config; }