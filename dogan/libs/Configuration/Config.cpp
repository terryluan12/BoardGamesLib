#include "Config.h"
#include <algorithm>
#include <iostream>
#include <random>

namespace Dogan {
std::vector<pip> Config::getNumbers(std::mt19937 rengine) {
  auto &[orderConfig, replaceConfig] = initialNumberConfig;
  std::uniform_int_distribution<pip> pipRand(1, 6);
  int sizeDifference = boardSize - initialNumberLocations.size();

  switch (replaceConfig) {
  case ReplaceConfiguration::DEFAULT:
  case ReplaceConfiguration::REPLACE:
    std::replace(initialNumberLocations.begin(), initialNumberLocations.end(),
                 7, pipRand(rengine));
    break;
  case ReplaceConfiguration::EXACT:
    break;
  }

  switch (orderConfig) {
  case OrderConfiguration::DEFAULT:
  case OrderConfiguration::SHUFFLE:

    if (sizeDifference - 1 != 0) {
      std::cerr << "WARNING: Board size (" << boardSize
                << ") does not match Tile Number Config size ("
                << initialNumberLocations.size()
                << "). You should not include 7 as a number. If this is not "
                   "intended, please fix this\n";
      if (sizeDifference - 1 > 0) {
        for (int i = 0; i < sizeDifference; i++) {
          initialNumberLocations.emplace_back(pipRand(rengine));
        }
      }
    }

    std::shuffle(initialNumberLocations.begin(), initialNumberLocations.end(),
                 rengine);
    initialNumberLocations.insert(initialNumberLocations.begin() + robberIndex,
                                  7);
    break;
  case OrderConfiguration::EXACT:
    if (sizeDifference != 0) {
      throw std::invalid_argument("Error: Exact Number Configuration requires "
                                  "number of numbers equal to board size");
    }
    break;
  }

  return initialNumberLocations;
}

std::vector<ResourceType> Config::getPortResources(std::mt19937 rengine) {
  auto &[orderConfig, replaceConfig] = initialPortResourceConfig;
  std::uniform_int_distribution<size_t> resourceRand(0, 4);
  int sizeDifference =
      initialPortLocations.size() - initialPortResources.size();

  switch (replaceConfig) {
  case ReplaceConfiguration::DEFAULT:
  case ReplaceConfiguration::REPLACE:
    std::replace(initialPortResources.begin(), initialPortResources.end(),
                 ResourceType::OTHER,
                 static_cast<ResourceType>(resourceRand(rengine)));
    break;
  case ReplaceConfiguration::EXACT:
    break;
  }

  switch (orderConfig) {
  case OrderConfiguration::DEFAULT:
  case OrderConfiguration::SHUFFLE:

    if (sizeDifference != 0) {
      std::cerr << "WARNING: Amount of Ports (" << initialPortLocations.size()
                << ") does not match Port Resources Config size ("
                << initialPortResources.size()
                << "). If this is not intended, please fix this\n";
      if (sizeDifference > 0) {
        for (int i = 0; i < sizeDifference; i++) {
          initialPortResources.emplace_back(
              static_cast<ResourceType>(resourceRand(rengine)));
        }
      }
    }

    std::shuffle(initialPortResources.begin(), initialPortResources.end(),
                 rengine);
    break;
  case OrderConfiguration::EXACT:
    if (sizeDifference != 0) {
      throw std::invalid_argument(
          "Error: Exact Port Resource Configuration requires number of "
          "resources equal to board size");
    }
    break;
  }
  return initialPortResources;
}

std::vector<ResourceType> Config::getResources(std::mt19937 rengine) {
  auto &[orderConfig, replaceConfig] = initialResourceConfig;
  std::uniform_int_distribution<size_t> resourceRand(0, 4);
  size_t sizeDifference = boardSize - initialResources.size();

  switch (replaceConfig) {
  case ReplaceConfiguration::DEFAULT:
  case ReplaceConfiguration::REPLACE:
    std::replace(initialResources.begin(), initialResources.end(),
                 ResourceType::OTHER,
                 static_cast<ResourceType>(resourceRand(rengine)));
    break;
  case ReplaceConfiguration::EXACT:
    break;
  }

  switch (orderConfig) {
  case OrderConfiguration::DEFAULT:
  case OrderConfiguration::SHUFFLE:

    if (sizeDifference - 1 != 0) {
      std::cerr << "WARNING: Board size (" << boardSize
                << ") does not match Resource size (" << initialResources.size()
                << "). Do not include the ResourceType::OTHER for the Robber."
                << "If this is not intended, please fix this\n";
      if (sizeDifference > 0) {
        for (size_t i = 0; i < sizeDifference; i++) {
          initialResources.emplace_back(
              static_cast<ResourceType>(resourceRand(rengine)));
        }
      }
    }
    std::shuffle(initialResources.begin(), initialResources.end(), rengine);
    initialResources.insert(initialResources.begin() + robberIndex,
                            ResourceType::OTHER);
    break;
  case OrderConfiguration::EXACT:
    if (sizeDifference != 0) {
      throw std::invalid_argument(
          "Error: Exact Resource Configuration requires number of resources "
          "equal to board size");
    }
    break;
  }
  return initialResources;
}

std::vector<DevelopmentType> Config::getDevelopments(std::mt19937 rengine) {
  auto &[orderConfig, replaceConfig] = initialDevelopmentConfig;
  std::uniform_int_distribution<size_t> developRand(0, 5);
  std::array<size_t, 5> sizeDifferences{initialDevelopmentCount};

  switch (replaceConfig) {
  case ReplaceConfiguration::DEFAULT:
  case ReplaceConfiguration::REPLACE:
    std::replace(initialDevelopmentLocations.begin(),
                 initialDevelopmentLocations.end(), DevelopmentType::OTHER,
                 static_cast<DevelopmentType>(developRand(rengine)));
    break;
  case ReplaceConfiguration::EXACT:
    break;
  }

  bool allZero = true;
  for (auto &d : initialDevelopmentLocations) {
    sizeDifferences[static_cast<int>(d)] -= 1;
  }
  switch (orderConfig) {
  case OrderConfiguration::DEFAULT:
  case OrderConfiguration::SHUFFLE:
    for (size_t i = 0; i < sizeDifferences.size(); i++) {
      if (sizeDifferences[i] != 0) {
        allZero = false;
      } else if (sizeDifferences[i] > 0) {
        for (size_t j = 0; j < sizeDifferences[i]; j++) {
          initialDevelopmentLocations.emplace_back(
              static_cast<DevelopmentType>(i));
        }
      } else {
        for (size_t j = 0; j < sizeDifferences[i]; j++) {
          initialDevelopmentLocations.erase(
              std::find(initialDevelopmentLocations.begin(),
                        initialDevelopmentLocations.end(),
                        static_cast<DevelopmentType>(i)));
        }
      }
    }
    if (!allZero) {
      std::cerr << "WARNING: Development Card Locations does not match "
                << "initial development card count given."
                << "If this is not intended, please fix this\n";
    }
    std::shuffle(initialDevelopmentLocations.begin(),
                 initialDevelopmentLocations.end(), rengine);
    break;
  case OrderConfiguration::EXACT:
    for (size_t i = 0; i < sizeDifferences.size(); i++) {
      if (sizeDifferences[i] != 0) {
        throw std::invalid_argument(
            "Error: Exact Development Configuration requires number of "
            "development cards equal to board size");
      }
    }
    break;
  }
  return initialDevelopmentLocations;
}

std::vector<Port> Config::getPorts(std::mt19937 rengine) {
  std::vector<Port> ports;
  std::vector<ResourceType> portConfiguration = getPortResources(rengine);

  for (size_t i = 0; i < portConfiguration.size(); i++) {
    ports.emplace_back(portConfiguration[i]);
  }
  return ports;
}

// Getters

size_t Config::getBoardSize(void) const { return boardSize; }

std::array<int, 3> Config::getTotalStructureCount(void) const {
  return totalStructureCount;
}

Coordinate2D Config::getRobberLocation(void) const {
  return initialRobberLocation;
}

const std::vector<Coordinate2D> Config::getTileLocations(void) const {
  return initialTileLocations;
}

const std::vector<std::vector<std::pair<Coordinate2D, Direction>>>
Config::getPortLocations(void) const {
  return initialPortLocations;
}

const std::array<size_t, 5> Config::getResourceCount(void) const {
  return initialResourceCount;
}
const std::array<size_t, 5> Config::getDevelopmentCount(void) const {
  return initialDevelopmentCount;
}

// Setters

void Config::setBoardSize(size_t s) { boardSize = s; }

void Config::setTotalStructureCount(std::array<int, 3> tsc) {
  totalStructureCount = tsc;
}

void Config::setResourceCount(std::array<size_t, 5> rc) {
  initialResourceCount = rc;
}

void Config::setDevelopmentCount(std::array<size_t, 5> dc) {
  initialDevelopmentCount = dc;
}

void Config::setDevelopmentConfig(Configuration dc) {
  initialDevelopmentConfig = dc;
}

void Config::setNumberConfig(Configuration nc) { initialNumberConfig = nc; }

void Config::setPortResourceConfig(Configuration prc) {
  initialPortResourceConfig = prc;
}

void Config::setResourceConfig(Configuration rc) { initialResourceConfig = rc; }

void Config::setDevelopmentLocations(std::vector<DevelopmentType> dl) {
  initialDevelopmentLocations = dl;
}

void Config::setNumberLocations(std::vector<pip> nl) {
  initialNumberLocations = nl;
}

void Config::setPortLocations(
    std::vector<std::vector<std::pair<Coordinate2D, Direction>>> pls) {
  initialPortLocations = pls;
}

void Config::setRobberLocation(Coordinate2D irl) {
  initialRobberLocation = irl;
}

void Config::setTileLocations(std::vector<Coordinate2D> tl) {
  initialTileLocations = tl;
}

void Config::setResources(std::vector<ResourceType> r) { initialResources = r; }

void Config::setPortResources(std::vector<ResourceType> pr) {
  initialPortResources = pr;
}
} // namespace Dogan