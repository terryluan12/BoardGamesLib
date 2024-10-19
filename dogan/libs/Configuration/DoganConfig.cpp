#include "DoganConfig.h"
#include <algorithm>
#include <iostream>
#include <random>

std::vector<pip> DoganConfig::getNumbers(std::mt19937 rengine) {
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
          initialNumberLocations.push_back(pipRand(rengine));
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

std::vector<ResourceType> DoganConfig::getPortResources(std::mt19937 rengine) {
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
          initialPortResources.push_back(
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

std::vector<ResourceType> DoganConfig::getResources(std::mt19937 rengine) {
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
          initialResources.push_back(
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

std::vector<DevelopmentType>
DoganConfig::getDevelopments(std::mt19937 rengine) {
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
          initialDevelopmentLocations.push_back(
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

std::vector<DoganPort> DoganConfig::getPorts(std::mt19937 rengine) {
  std::vector<DoganPort> ports;
  std::vector<ResourceType> portConfiguration = getPortResources(rengine);

  for (size_t i = 0; i < portConfiguration.size(); i++) {
    ports.emplace_back(portConfiguration[i], initialPortLocations[i]);
  }
  return ports;
}

// Getters

size_t DoganConfig::getBoardSize(void) const { return boardSize; }

std::array<int, 3> DoganConfig::getTotalStructureCount(void) const {
  return totalStructureCount;
}

Coordinate2D DoganConfig::getRobberLocation(void) const {
  return initialRobberLocation;
}

const std::vector<Coordinate2D> DoganConfig::getTileLocations(void) const {
  return initialTileLocations;
}

const std::array<size_t, 5> DoganConfig::getResourceCount(void) const {
  return initialResourceCount;
}
const std::array<size_t, 5> DoganConfig::getDevelopmentCount(void) const {
  return initialDevelopmentCount;
}

// Setters

void DoganConfig::setBoardSize(size_t s) { boardSize = s; }

void DoganConfig::setTotalStructureCount(std::array<int, 3> tsc) {
  totalStructureCount = tsc;
}

void DoganConfig::setResourceCount(std::array<size_t, 5> rc) {
  initialResourceCount = rc;
}

void DoganConfig::setDevelopmentCount(std::array<size_t, 5> dc) {
  initialDevelopmentCount = dc;
}

void DoganConfig::setDevelopmentConfig(Configuration dc) {
  initialDevelopmentConfig = dc;
}

void DoganConfig::setNumberConfig(Configuration nc) {
  initialNumberConfig = nc;
}

void DoganConfig::setPortResourceConfig(Configuration prc) {
  initialPortResourceConfig = prc;
}

void DoganConfig::setResourceConfig(Configuration rc) {
  initialResourceConfig = rc;
}

void DoganConfig::setDevelopmentLocations(std::vector<DevelopmentType> dl) {
  initialDevelopmentLocations = dl;
}

void DoganConfig::setNumberLocations(std::vector<pip> nl) {
  initialNumberLocations = nl;
}

void DoganConfig::setPortLocations(
    std::vector<std::vector<std::pair<std::array<int, 2>, std::string>>> pls) {
  std::vector<std::vector<DoganVertex>> pvs;
  for (auto portVertices : pls) {
    std::vector<DoganVertex> pv;
    for (auto [coord, direction] : portVertices) {
      pv.emplace_back(coord, direction);
    }
    pvs.push_back(pv);
  }
  initialPortLocations = pvs;
}

void DoganConfig::setRobberLocation(Coordinate2D irl) {
  initialRobberLocation = irl;
}

void DoganConfig::setTileLocations(std::vector<Coordinate2D> tl) {
  initialTileLocations = tl;
}

void DoganConfig::setResources(std::vector<ResourceType> r) {
  initialResources = r;
}

void DoganConfig::setPortResources(std::vector<ResourceType> pr) {
  initialPortResources = pr;
}