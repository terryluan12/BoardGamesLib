#include "Coordinate.h"
#include "DoganConfigBuilder.h"
#include "DoganExceptions.h"
#include "config.enum.h"
#include <sstream>
#include <iostream>

namespace Dogan {
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
    std::vector<std::set<VertexPrimitive>> portLocations) {
  config.setPortLocations(portLocations);
  return *this;
}

ConfigBuilder &ConfigBuilder::setPortLocations(
    std::vector<std::vector<VertexPrimitive>> portLocations) {
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
  auto &[_, replaceConfig] = config.initialPortResourceConfig;
  return *this;
}

bool followsReplaceExactConfiguration(Configuration c, int sizeDifference) {
  auto &[orderConfig, replaceConfig] = c;
  if (replaceConfig == ReplaceConfiguration::EXACT) {
    if (sizeDifference != 0) {
      return true;
    }
  }
  return false;
}

void ConfigBuilder::validate(void) {
  std::stringstream ss;
  std::string message{};
  int sizeDifference =
      config.initialTileLocations.size() - config.initialNumberLocations.size();
  if (followsReplaceExactConfiguration(config.initialNumberConfig,
                                       sizeDifference)) {
    ss << "Error: ReplaceConfiguration::EXACT set. "
       << "Therefore number location size: "
       << config.initialNumberLocations.size()
       << " must equal to board size: "
       << config.initialTileLocations.size() << std::endl;
  }

  sizeDifference =
      config.initialPortLocations.size() - config.initialPortResources.size();
  if (followsReplaceExactConfiguration(config.initialPortResourceConfig,
                                       sizeDifference)) {
    ss << "Error: ReplaceConfiguration::EXACT set. "
       << "Therefore Port Resources size: "
       << config.initialPortResources.size()
       << " must equal to Port locations size: "
       << config.initialPortLocations.size() << std::endl;
  }

  sizeDifference =
      config.initialTileLocations.size() - config.initialResources.size();
  if (followsReplaceExactConfiguration(config.initialResourceConfig,
                                       sizeDifference)) {
    ss << "Error: ReplaceConfiguration::EXACT set. "
       << "Therefore Resources size: " << config.initialResources.size()
       << " must equal to board size: "
       << config.initialTileLocations.size() << std::endl;
  }

  for (int i = 0; i < 5; i++) {
    sizeDifferences[i] = static_cast<int>(config.initialDevelopmentCount[i]);
  }
  for (auto &d : config.initialDevelopmentLocations) {
    sizeDifferences[static_cast<int>(d)] -= 1;
  }
  for (int i = 0; i < 5; i++) {
    if (followsReplaceExactConfiguration(config.initialDevelopmentConfig,
                                         sizeDifferences[i])) {
      ss << "Error: ReplaceConfiguration::EXACT set. "
         << "Therefore Amount of DevelopmentCard type: "
         << static_cast<DevelopmentType>(i) << " must equal to "
         << config.initialDevelopmentCount[i] << std::endl;
    }
  }

  const auto &it = std::find(config.initialTileLocations.begin(),
                             config.initialTileLocations.end(),
                             config.initialRobberLocation);
  if (it != config.initialTileLocations.end()) {
    ss << "Error: Robber location must be separate from TileLocations";
  }

  if (!ss.str().empty()) {
    throw std::invalid_argument(ss.str());
  }
}

template <class T>
void initialize(Configuration c, int sizeDifference, std::vector<T> &vector,
                T replaceElement, std::mt19937 rengine,
                std::uniform_int_distribution<size_t> distribution) {
  auto &[orderConfig, replaceConfig] = c;

  switch (orderConfig) {
  case OrderConfiguration::DEFAULT:
  case OrderConfiguration::SHUFFLE:
    if (sizeDifference > 0) {
      for (int i = 0; i < sizeDifference; i++) {
        vector.emplace_back(static_cast<T>(distribution(rengine)));
      }
    }
    std::shuffle(vector.begin(), vector.end(), rengine);
    break;
  case OrderConfiguration::EXACT:
    break;
  }

  switch (replaceConfig) {
  case ReplaceConfiguration::DEFAULT:
  case ReplaceConfiguration::REPLACE:
    std::replace(vector.begin(), vector.end(), replaceElement,
                 static_cast<T>(distribution(rengine)));
    break;
  case ReplaceConfiguration::EXACT:
    break;
  }
}

Config ConfigBuilder::build() {
  validate();
  std::uniform_int_distribution<size_t> resourceRand(0, 4), pipRand(2, 12);

  // Initialize Port Resource with Configuration
  int sizeDifference =
      config.initialPortLocations.size() - config.initialPortResources.size();
  initialize<ResourceType>(config.initialPortResourceConfig, sizeDifference,
                           config.initialPortResources, ResourceType::OTHER,
                           rengine, resourceRand);
                      
  // Initialize Board Numbers with Configuration
  sizeDifference = config.initialTileLocations.size() -
                       config.initialNumberLocations.size();
  initialize(config.initialNumberConfig, sizeDifference,
             config.initialNumberLocations, 7, rengine, pipRand);

  // Initialize Board Resources with Configuration
  sizeDifference =
      config.initialTileLocations.size() - config.initialResources.size();
  initialize(config.initialResourceConfig, sizeDifference,
             config.initialResources, ResourceType::OTHER, rengine,
             resourceRand);

  // Initialize Development with Configuration
  for(int i = 0; i < 5; i++) {
    if(sizeDifferences[i] < 0) {
      for(int i = 0; i < -1 * sizeDifferences[i]; i++) {
        config.initialDevelopmentLocations.erase(
          std::find(config.initialDevelopmentLocations.begin(),
                    config.initialDevelopmentLocations.end(),
                    static_cast<DevelopmentType>(i)));
      }
    }
    std::uniform_int_distribution<size_t> developRand(i, i);
    initialize(config.initialDevelopmentConfig, sizeDifferences[i],
          config.initialDevelopmentLocations, DevelopmentType::OTHER, rengine,
          developRand);
  }

  config.initialNumberLocations.push_back(7);
  config.initialResources.push_back(ResourceType::OTHER);
  config.initialTileLocations.push_back(config.initialRobberLocation);
  return config;
}
} // namespace Dogan