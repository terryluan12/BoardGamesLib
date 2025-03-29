#include "AxialDirection.h"
#include "Building.h"
#include "DoganExceptions.h"
#include "DoganGame.h"
#include "DoganResponse.h"
#include "Road.h"
#include "enums.h"
#include <memory>
#include <sstream>

namespace Dogan {
Game::Game(Config config, bool throwErrors)
    : config(config), throwErrors(throwErrors), die(1, 6), board(Board(config)),
      usedDevCard(false), rengine(std::random_device{}()) {
  std::array<int, 5> resourceCount{};
  for (size_t i = 0; i < 5; i++) {
    resourceCount[i] = config.getResourceCount()[i];
  }
  std::vector<DevelopmentType> developments = config.getDevelopmentOrder();
  bank = Bank(resourceCount, developments);
}

Response Game::addPlayer(int pid) {
  try {
    if (players.find(pid) != players.end()) {
      throw SamePlayerException("Cannot add same player twice");
    }
    Player p = Player(pid, config.getTotalStructureCount());
    this->players.emplace(pid, p);

  } catch (std::exception &e) {
    if (throwErrors) {
      throw e;
    } else {
      return Response{false, e.what()};
    }
  }
  return Response{true};
};

Response Game::removePlayer(int pid) {
  try {
    checkPlayerExists(pid);
    players.erase(pid);
  } catch (std::exception &e) {
    if (throwErrors) {
      throw e;
    } else {
      return Response{false, e.what()};
    }
  }
  return Response{true};
}

Response Game::giveResources(int playerID, std::array<int, 5> resources) {
  try {
    checkPlayerExists(playerID);
    players.at(playerID).addResources(resources);
  } catch (std::exception &e) {
    if (throwErrors) {
      throw e;
    } else {
      return Response{false, e.what()};
    }
  }
  return Response{true};
}

int Game::rollDice(void) { return die(rengine) + die(rengine); }

Response Game::distributeResources(int numberRolled) {
  try {
    auto buildings = board.getResourceDistribution(numberRolled);
    for (auto [pid, resources] : buildings) {
      checkPlayerExists(pid);
      for (size_t i = 0; i < resources.size(); i++) {
        checkBankCanAfford(static_cast<ResourceType>(i), resources[i]);
        bank.addResource(static_cast<ResourceType>(i), -1 * resources[i]);
        players.at(pid).addResource(static_cast<ResourceType>(i), resources[i]);
      }
    }
  } catch (std::exception &e) {
    if (throwErrors) {
      throw e;
    } else {
      return Response{false, e.what()};
    }
  }
  return Response{true};
}

Response Game::buildStructure(int playerID, StructureType structType,
                              Coordinate2D tileLocation, Direction direction,
                              std::array<int, 5> cost, bool mustBeAdjacent) {
  try {
    std::shared_ptr<Structure> element;
    checkPlayerExists(playerID);
    checkPlayerCanAfford(playerID, cost);
    checkCoordinateValid(tileLocation);
    switch (structType) {
    case StructureType::VILLAGE:
      element = std::make_shared<Building>(playerID, structType, tileLocation,
                                           direction);
    case StructureType::CITY:
      break;
    case StructureType::ROAD:
      element = std::make_shared<Road>(playerID, tileLocation, direction);
      break;
    }

    players.at(playerID).buildStructure(structType);

    if (structType == StructureType::CITY) {
      board.upgradeToCity(playerID, tileLocation, direction);
    } else {
      board.buildStructure(playerID, element, mustBeAdjacent);
    }
    bank.addResources(cost);
  } catch (std::exception &e) {
    if (throwErrors) {
      throw e;
    } else {
      return Response{false, e.what()};
    }
  }
  return Response{true};
}

Response Game::purchaseDevelopmentCard(int playerID, std::array<int, 5> cost) {
  try {
    checkPlayerExists(playerID);
    checkPlayerCanAfford(playerID, cost);

    DevelopmentType dt = bank.popDevelopment();
    players.at(playerID).giveDevelopment(dt);
    bank.addResources(cost);
  } catch (std::exception &e) {
    if (throwErrors) {
      throw e;
    } else {
      return Response{false, e.what()};
    }
  }
  return Response{true};
}

Response Game::tradeResources(int playerID1, std::array<int, 5> resources1,
                              int playerID2, std::array<int, 5> resources2) {
  try {
    checkPlayerExists(playerID1);
    checkPlayerExists(playerID2);

    std::array<int, 5> resourceDifference;
    std::array<int, 5> negativeResourceDifference;
    for (int i = 0; i < 5; i++) {
      resourceDifference[i] = resources1[i] - resources2[i];
      negativeResourceDifference[i] = -resourceDifference[i];
    }
    checkPlayerCanAfford(playerID1, resourceDifference);
    checkPlayerCanAfford(playerID2, negativeResourceDifference);

    players.at(playerID2).addResources(resourceDifference);
    players.at(playerID1).addResources(negativeResourceDifference);
  } catch (std::exception &e) {
    if (throwErrors) {
      throw e;
    } else {
      return Response{false, e.what()};
    }
  }
  return Response{true};
}

Response Game::useRobber(int playerID, Coordinate2D tileLocation,
                         Direction direction) {
  try {
    checkPlayerExists(playerID);
    checkCoordinateValid(tileLocation);

    if (direction == Direction::NONE) {
      return Response{false, "Error: Direction cannot be NONE"};
    }

    if (!board.hasBuilding(tileLocation, direction)) {
      if (throwErrors) {
        throw NoSuchStructureException("Error: No Building at given location");
      } else {
        return Response{false, "Error: No Building at given location"};
      }
    }

    board.moveRobber(tileLocation);

    int stolenPID = board.getBuilding(tileLocation, direction)->getPlayerID();
    stealResource(playerID, stolenPID);
  } catch (std::exception &e) {
    if (throwErrors) {
      throw e;
    } else {
      return Response{false, e.what()};
    }
  }
  return Response{true};
}

Response Game::useMonopolyDevelopmentCard(int playerID, ResourceType resource) {
  try {
    checkPlayerExists(playerID);
    checkPlayerHasDevelopmentCard(playerID, DevelopmentType::MONOPOLY);
    checkUsedDevCard();
    checkResourceType(resource);

    int resourceIndex = static_cast<int>(resource);

    for (auto &[pid, p] : players) {
      if (pid == playerID)
        continue;
      int stolenCount = p.getResourceCount()[resourceIndex];
      players.at(playerID).addResource(resource, stolenCount);
      p.addResource(resource, -1 * stolenCount);
    }
    usedDevCard = true;
  } catch (std::exception &e) {
    if (throwErrors) {
      throw e;
    } else {
      return Response{false, e.what()};
    }
  }
  return Response{true};
}

Response Game::useSoldierDevelopmentCard(int playerID,
                                         Coordinate2D tileLocation,
                                         Direction direction) {
  try {
    checkPlayerHasDevelopmentCard(playerID, DevelopmentType::SOLDIER);
    checkUsedDevCard();

    useRobber(playerID, tileLocation, direction);

    players.at(playerID).increaseSoldierCount();
    int soldierCount = players.at(playerID).getSoldierCount();
    if (soldierCount >= 3 && soldierCount > mostSoldiers.second) {
      players.at(mostSoldiers.first).addVictoryPoints(-2);
      mostSoldiers = {playerID, soldierCount};
      players.at(playerID).addVictoryPoints(2);
    }
    usedDevCard = true;
  } catch (std::exception &e) {
    if (throwErrors) {
      throw e;
    } else {
      return Response{false, e.what()};
    }
  }
  return Response{true};
}

Response Game::useRoadDevelopmentCard(int playerID,
                                      std::array<Coordinate2D, 2> tileLocations,
                                      std::array<Direction, 2> directions) {
  try {
    checkPlayerExists(playerID);
    checkPlayerHasDevelopmentCard(playerID, DevelopmentType::BUILDROAD);
    checkUsedDevCard();
    for (int i = 0; i < 2; i++) {
      buildStructure(playerID, StructureType::ROAD, tileLocations[i],
                     directions[i], {0, 0, 0, 0, 0});
    }
    usedDevCard = true;
  } catch (std::exception &e) {
    if (throwErrors) {
      throw e;
    } else {
      return Response{false, e.what()};
    }
  }
  return Response{true};
}
Response
Game::useTakeTwoDevelopmentCard(int playerID,
                                std::array<ResourceType, 2> resources) {
  try {
    checkPlayerExists(playerID);
    checkPlayerHasDevelopmentCard(playerID, DevelopmentType::TAKETWO);
    checkUsedDevCard();
    checkResourceType(resources[0]);
    checkResourceType(resources[1]);

    if (resources[0] == resources[1]) {
      checkBankCanAfford(resources[0], 2);
    } else {
      checkBankCanAfford(resources[0], 1);
      checkBankCanAfford(resources[1], 1);
    }

    for (int i = 0; i < 2; i++) {
      players.at(playerID).addResource(resources[i], 1);
      bank.addResource(resources[i], -1);
    }
    usedDevCard = true;
  } catch (std::exception &e) {
    if (throwErrors) {
      throw e;
    } else {
      return Response{false, e.what()};
    }
  }
  return Response{true};
}

const std::array<int, 5> Game::getResourceCount(int playerID) const {
  if (playerID == -1) {
    return bank.getResourceCount();
  }
  checkPlayerExists(playerID);
  return players.at(playerID).getResourceCount();
}
const std::array<int, 5> Game::getDevelopmentCount(int playerID) const {
  if (playerID == -1) {
    return bank.getDevelopmentCount();
  }
  checkPlayerExists(playerID);
  return players.at(playerID).getDevelopmentCount();
}

int Game::getVictoryPoints(int playerID) const {
  checkPlayerExists(playerID);
  return players.at(playerID).getVictoryPoints();
}

bool Game::hasStructure(Coordinate2D coord, Direction direction,
                        StructureType structureType) const {
  return board.hasStructure(coord, direction, structureType);
}

const bool Game::hasPlayer(int playerID) const {
  return players.contains(playerID);
}

void Game::resetTurn(void) { usedDevCard = false; }

void Game::stealResource(int playerID, int stolenPlayerID) {
  checkPlayerExists(playerID);
  checkPlayerExists(stolenPlayerID);
  auto resourceCount = players.at(stolenPlayerID).getResourceCount();
  std::vector<int> availableIndices = {};

  for (int i = 0; i < 5; i++) {
    if (resourceCount[i] == 0) {
      continue;
    }
    availableIndices.emplace_back(i);
  }
  if (availableIndices.size() == 0) {
    throw InsufficientResourcesException(
        "Error: Player does not have enough resources to steal");
  }
  std::uniform_int_distribution<std::size_t> randomPicker(
      0, availableIndices.size() - 1);
  ResourceType resourceStolen =
      static_cast<ResourceType>(availableIndices[randomPicker(rengine)]);

  players.at(stolenPlayerID).addResource(resourceStolen, -1);
  players.at(playerID).addResource(resourceStolen, 1);
}

// Utility Functions
void Game::checkPlayerExists(int playerID) const {
  if (players.find(playerID) == players.end()) {
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID) +
                                  " invalid");
  }
}
void Game::checkPlayerCanAfford(int playerID, std::array<int, 5> cost) const {
  if (!players.at(playerID).canAfford(cost)) {
    throw InsufficientResourcesException(
        "Error: Player does not have enough resources");
  }
}
void Game::checkBankCanAfford(ResourceType resourceType, int num) const {
  if (!bank.canAfford(resourceType, num)) {
    throw InsufficientResourcesException(
        "Error: Bank does not have enough resources");
  }
}
void Game::checkPlayerHasDevelopmentCard(int playerID,
                                         DevelopmentType devType) const {
  std::stringstream oss;
  oss << "Error: Player does not have " << devType << " card";
  if (players.at(playerID).getDevelopmentCount()[static_cast<int>(devType)] ==
      0) {
    throw InsufficientDevelopmentsException(oss.str());
  }
}
void Game::checkCoordinateValid(Coordinate2D coord) const {
  if (!board.hasTile(coord)) {
    throw CoordinateNotFoundException("Error: Invalid Coordinate");
  }
}
void Game::checkResourceType(ResourceType resourceType) const {
  if (resourceType == ResourceType::OTHER) {
    throw InvalidTypeException("Error: Resource type must be set");
  }
}
void Game::checkUsedDevCard(void) const {
  if (usedDevCard) {
    throw UsedDevelopmentCardException(
        "Error: Development card already used this turn");
  }
}

std::ostream &operator<<(std::ostream &os, Game const &dg) {
  os << dg.board;
  for (auto &p : dg.players) {
    os << p.second;
  }
  os << dg.bank;
  return os;
}
} // namespace Dogan