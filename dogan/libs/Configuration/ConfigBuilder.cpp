#include "Coordinate.h"
#include "DoganConfigBuilder.h"
#include "DoganExceptions.h"
#include "config.enum.h"
#include <iostream>
#include <sstream>

namespace Dogan {

ConfigBuilder &
ConfigBuilder::setTileLocations(std::vector<Coordinate> tileLocations) {
  std::vector<Coordinate2D> tls;
  for (Coordinate2D tileLocation : tileLocations) {
    tls.emplace_back(tileLocation);
  }
  config.setTileLocations(tls);
  return *this;
}

ConfigBuilder &
ConfigBuilder::setPortLocations(std::vector<std::vector<Point>> portLocations) {
  std::vector<std::set<VertexPrimitive>> sets;

  for (const auto &port : portLocations) {
    auto set = std::set<VertexPrimitive>();
    for (const auto &dock : port) {
      VertexPrimitive newDock{};
      std::get<0>(newDock) = std::get<0>(dock);
      std::get<1>(newDock) = static_cast<HexDirection>(std::get<1>(dock));
      set.insert(newDock);
    }
    if (set.size() != portLocations.size()) {
      std::cerr << "WARNING: Duplicate Port locations. please check your "
                   "configuration or data for errors."
                << std::endl;
    }
    sets.push_back(set);
  }
  config.setPortLocations(sets);
  return *this;
}

ConfigBuilder &ConfigBuilder::setRobberLocation(Coordinate robberLocations) {
  config.setRobberLocation(robberLocations);
  return *this;
}

ConfigBuilder &ConfigBuilder::setTotalStructureCount(
    std::array<int, 3> totalPlayerStructureCount) {
  config.setTotalStructureCount(totalPlayerStructureCount);
  return *this;
}

ConfigBuilder &ConfigBuilder::setResourceCount(std::array<int, 5> rc) {
  config.setResourceCount(rc);
  return *this;
}

ConfigBuilder &ConfigBuilder::setDevelopmentCount(std::array<int, 5> dc) {
  config.setDevelopmentCount(dc);
  return *this;
}

ConfigBuilder &
ConfigBuilder::setBoardResourceOrder(std::vector<int> resources) {
  std::vector<ResourceType> r;
  for (int resource : resources) {
    r.emplace_back(static_cast<ResourceType>(resource));
  }
  config.setBoardResourceOrder(r);
  return *this;
}

ConfigBuilder &
ConfigBuilder::setPortResourceOrder(std::vector<int> portResourceOrder) {
  std::vector<ResourceType> pr;
  for (int resource : portResourceOrder) {
    pr.emplace_back(static_cast<ResourceType>(resource));
  }
  config.setPortResourceOrder(pr);
  auto &[_, replaceConfig] = config.portResourceConfig;
  return *this;
}

ConfigBuilder &ConfigBuilder::setNumberOrder(std::vector<int> numberOrder) {
  config.setNumberOrder(numberOrder);
  return *this;
}

ConfigBuilder &
ConfigBuilder::setDevelopmentOrder(std::vector<int> developmentOrder) {
  std::vector<DevelopmentType> order;
  for (int i : developmentOrder) {
    order.emplace_back(static_cast<DevelopmentType>(i));
  }
  config.setDevelopmentOrder(order);
  return *this;
}

ConfigBuilder &
ConfigBuilder::setBoardResourceConfig(intConfig boardResourceConfig) {
  Configuration brConfig{};
  std::get<0>(brConfig) =
      static_cast<OrderConfiguration>(boardResourceConfig[0]);
  std::get<1>(brConfig) =
      static_cast<ReplaceConfiguration>(boardResourceConfig[1]);
  config.setBoardResourceConfig(brConfig);
  return *this;
}

ConfigBuilder &
ConfigBuilder::setPortResourceConfig(intConfig portResourceConfig) {
  Configuration prConfig{};
  std::get<0>(prConfig) =
      static_cast<OrderConfiguration>(portResourceConfig[0]);
  std::get<1>(prConfig) =
      static_cast<ReplaceConfiguration>(portResourceConfig[1]);
  config.setPortResourceConfig(prConfig);
  return *this;
}

ConfigBuilder &ConfigBuilder::setNumberConfig(intConfig numberConfiguration) {
  Configuration nConfig{};
  std::get<0>(nConfig) =
      static_cast<OrderConfiguration>(numberConfiguration[0]);
  std::get<1>(nConfig) =
      static_cast<ReplaceConfiguration>(numberConfiguration[1]);
  config.setNumberConfig(nConfig);
  return *this;
}

ConfigBuilder &
ConfigBuilder::setDevelopmentConfig(intConfig developmentConfiguration) {
  Configuration dConfig{};
  std::get<0>(dConfig) =
      static_cast<OrderConfiguration>(developmentConfiguration[0]);
  std::get<1>(dConfig) =
      static_cast<ReplaceConfiguration>(developmentConfiguration[1]);
  config.setDevelopmentConfig(dConfig);
  return *this;
}

bool followsReplaceExactConfiguration(Configuration c, int sizeDifference) {
  auto &[orderConfig, replaceConfig] = c;
  if (replaceConfig == ReplaceConfiguration::EXACT) {
    if (sizeDifference != 0) {
      return false;
    }
  }
  return true;
}

Response ConfigBuilder::validate(bool throwError) {
  std::stringstream ss;
  std::string message{};
  Response answer{};
  int sizeDifference =
      config.tileLocations.size() - config.boardResourceOrder.size();
  if (!followsReplaceExactConfiguration(config.boardResourceConfig,
                                        sizeDifference)) {
    ss << "Error: ReplaceConfiguration::EXACT set. "
       << "Therefore Resources size must equal to board size: "
       << config.tileLocations.size() << " not "
       << config.boardResourceOrder.size() << "\n";
  }

  sizeDifference = config.tileLocations.size() - config.numberOrder.size();
  if (!followsReplaceExactConfiguration(config.numberConfig, sizeDifference)) {
    ss << "Error: ReplaceConfiguration::EXACT set. "
       << "Therefore number location size must equal to board size: "
       << config.tileLocations.size() << " not " << config.numberOrder.size()
       << std::endl;
  }

  sizeDifference =
      config.portLocations.size() - config.portResourceOrder.size();
  if (!followsReplaceExactConfiguration(config.portResourceConfig,
                                        sizeDifference)) {
    ss << "Error: ReplaceConfiguration::EXACT set. "
       << "Therefore Port Resources size must equal to Port locations size: "
       << config.portLocations.size() << " not "
       << config.portResourceOrder.size() << "\n";
  }

  for (int i = 0; i < 5; i++) {
    sizeDifferences[i] = config.developmentCount[i];
  }
  for (auto &d : config.developmentOrder) {
    sizeDifferences[static_cast<int>(d)] -= 1;
  }
  for (int i = 0; i < 5; i++) {
    if (!followsReplaceExactConfiguration(config.developmentConfig,
                                          sizeDifferences[i])) {
      ss << "Error: ReplaceConfiguration::EXACT set. "
         << "Therefore Amount of DevelopmentCard type: "
         << static_cast<DevelopmentType>(i) << " must equal to "
         << config.developmentCount[i] << " not "
         << config.developmentCount[i] - sizeDifferences[i] << "\n";
    }
  }

  const auto &it = std::find(config.tileLocations.begin(),
                             config.tileLocations.end(), config.robberLocation);
  if (it != config.tileLocations.end()) {
    ss << "Error: Robber location " << config.robberLocation
       << " must be separate from TileLocations\n";
  }

  if (!ss.str().empty()) {
    if (throwError) {
      throw std::invalid_argument(ss.str());
    } else {
      answer.succeeded = false;
      answer.message = ss.str();
      return answer;
    }
  }

  answer.succeeded = true;
  return answer;
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
      config.portLocations.size() - config.portResourceOrder.size();
  initialize<ResourceType>(config.portResourceConfig, sizeDifference,
                           config.portResourceOrder, ResourceType::OTHER,
                           rengine, resourceRand);

  // Initialize Board Numbers with Configuration
  sizeDifference = config.tileLocations.size() - config.numberOrder.size();
  initialize(config.numberConfig, sizeDifference, config.numberOrder, 7,
             rengine, pipRand);

  // Initialize Board Resources with Configuration
  sizeDifference =
      config.tileLocations.size() - config.boardResourceOrder.size();
  initialize(config.boardResourceConfig, sizeDifference,
             config.boardResourceOrder, ResourceType::OTHER, rengine,
             resourceRand);

  // Initialize Development with Configuration
  for (int i = 0; i < 5; i++) {
    if (sizeDifferences[i] < 0) {
      for (int i = 0; i < -1 * sizeDifferences[i]; i++) {
        config.developmentOrder.erase(std::find(
            config.developmentOrder.begin(), config.developmentOrder.end(),
            static_cast<DevelopmentType>(i)));
      }
    }
    std::uniform_int_distribution<size_t> developRand(i, i);
    initialize(config.developmentConfig, sizeDifferences[i],
               config.developmentOrder, DevelopmentType::OTHER, rengine,
               developRand);
  }

  config.numberOrder.push_back(7);
  config.boardResourceOrder.push_back(ResourceType::OTHER);
  config.tileLocations.push_back(config.robberLocation);
  return config;
}
} // namespace Dogan