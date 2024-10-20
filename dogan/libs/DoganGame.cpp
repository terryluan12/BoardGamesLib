#include "DoganGame.h"
#include "DoganBuilding.h"
#include "DoganExceptions.h"
#include "DoganRoad.h"
#include "enums.h"
#include <memory>
#include <sstream>

DoganGame::DoganGame(DoganConfig config)
    : config(config), die(1, 6),
      board(DoganBoard(config)), rengine(std::random_device{}()) {
  std::array<int, 5> resourceCount{};
  for (size_t i = 0; i < 5; i++) {
    resourceCount[i] = config.getResourceCount()[i];
  }
  std::vector<DevelopmentType> developments = config.getDevelopments(rengine);
  bank = DoganBank(resourceCount, developments);
}

void DoganGame::addPlayer(std::string pn, int pid) {
  if (players.find(pid) != players.end()) {
    throw SamePlayerException("Cannot add same player twice");
  }
  DoganPlayer p = DoganPlayer(pn, pid);
  p.setAvailableStructures(config.getTotalStructureCount());
  this->players.emplace(pid, p);
};

void DoganGame::giveResources(int playerID, std::array<int, 5> resources) {
  checkPlayerExists(playerID);
  players.at(playerID).addResources(resources);
}

int DoganGame::rollDice(void) { return die(rengine) + die(rengine); }

void DoganGame::distributeResources(int numberRolled) {
  auto buildings = board.getResourceDistribution(numberRolled);
  for (auto [pid, resources] : buildings) {
    checkPlayerExists(pid);
    for (size_t i = 0; i < resources.size(); i++) {
      checkBankCanAfford(static_cast<ResourceType>(i), resources[i]);
      bank.addResource(static_cast<ResourceType>(i), -1 * resources[i]);
      players.at(pid).addResource(static_cast<ResourceType>(i), resources[i]);
    }
  }
}

void DoganGame::buildStructure(int playerID, StructureType structType,
                               Coordinate2D tileLocation, Direction direction,
                               std::array<int, 5> cost) {
  std::shared_ptr<DoganStructure> element;
  checkPlayerExists(playerID);
  checkPlayerCanAfford(playerID, cost);
  checkCoordinateValid(tileLocation);
  checkStructureExists(tileLocation, direction, structType);

  switch (structType) {
  case StructureType::VILLAGE:
  case StructureType::CITY:
    element = std::make_shared<DoganBuilding>(DoganBuilding(
        playerID, structType, DoganVertex(tileLocation, direction)));
    break;
  case StructureType::ROAD:
    element = std::make_shared<DoganRoad>(
        DoganRoad(playerID, structType, DoganEdge(tileLocation, direction)));
    break;
  }
  board.buildStructure(element, cost);
  players.at(playerID).buildStructure(element, cost);
  bank.addResources(cost);
}

void DoganGame::purchaseDevelopmentCard(int playerID, std::array<int, 5> cost) {
  checkPlayerExists(playerID);
  checkPlayerCanAfford(playerID, cost);

  DevelopmentType dt = bank.popDevelopment();
  players.at(playerID).giveDevelopment(dt);
  bank.addResources(cost);
}

void DoganGame::tradeResources(int playerID1, std::array<int, 5> resources1,
                               int playerID2, std::array<int, 5> resources2) {
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
}

void DoganGame::useRobber(int playerID, Coordinate2D tileLocation,
                          Direction direction) {
  checkPlayerExists(playerID);
  checkCoordinateValid(tileLocation);
  if (!board.hasBuilding(tileLocation, direction))
    throw NoSuchStructureException("Error: No Building at given location");

  board.moveRobber(tileLocation);

  int stolenPID = board.getBuilding(tileLocation, direction).getPlayerID();
  stealResource(playerID, stolenPID);
}

void DoganGame::useMonopolyDevelopmentCard(int playerID,
                                           ResourceType resource) {
  checkPlayerExists(playerID);
  checkPlayerHasDevelopmentCard(playerID, DevelopmentType::MONOPOLY);
  checkResourceType(resource);

  int resourceIndex = static_cast<int>(resource);

  for (auto &[pid, p] : players) {
    if (pid == playerID)
      continue;
    int stolenCount = p.getResourceCount()[resourceIndex];
    players.at(playerID).addResource(resource, stolenCount);
    p.addResource(resource, -1 * stolenCount);
  }
}

void DoganGame::useSoldierDevelopmentCard(int playerID,
                                          Coordinate2D tileLocation,
                                          Direction direction) {
  checkPlayerHasDevelopmentCard(playerID, DevelopmentType::SOLDIER);

  useRobber(playerID, tileLocation, direction);

  players.at(playerID).increaseSoldierCount();
  int soldierCount = players.at(playerID).getSoldierCount();
  if (soldierCount >= 3 && soldierCount > mostSoldiers.second) {
    players.at(mostSoldiers.first).addVictoryPoints(-2);
    mostSoldiers = {playerID, soldierCount};
    players.at(playerID).addVictoryPoints(2);
  }
}

void DoganGame::useRoadDevelopmentCard(
    int playerID, std::array<Coordinate2D, 2> tileLocations,
    std::array<Direction, 2> directions) {
  checkPlayerExists(playerID);
  checkPlayerHasDevelopmentCard(playerID, DevelopmentType::BUILDROAD);

  for (int i = 0; i < 2; i++) {
    if (board.hasStructure(tileLocations[i], directions[i],
                           StructureType::ROAD))
      throw SameStructureException("Error: Road already exists");
  }
  for (int i = 0; i < 2; i++) {
    buildStructure(playerID, StructureType::ROAD, tileLocations[i],
                   directions[i], {0, 0, 0, 0, 0});
  }
}
void DoganGame::useTakeTwoDevelopmentCard(
    int playerID, std::array<ResourceType, 2> resources) {
  checkPlayerExists(playerID);
  checkPlayerHasDevelopmentCard(playerID, DevelopmentType::TAKETWO);
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
}

const std::array<int, 5> DoganGame::getResourceCount(int playerID) const {
  if (playerID == -1) {
    return bank.getResourceCount();
  }
  checkPlayerExists(playerID);
  return players.at(playerID).getResourceCount();
}
const std::array<int, 5> DoganGame::getDevelopmentCount(int playerID) const {
  if (playerID == -1) {
    return bank.getDevelopmentCount();
  }
  checkPlayerExists(playerID);
  return players.at(playerID).getDevelopmentCount();
}

int DoganGame::getVictoryPoints(int playerID) const {
  checkPlayerExists(playerID);
  return players.at(playerID).getVictoryPoints();
}

bool DoganGame::hasStructure(Coordinate2D coord, Direction direction,
                             StructureType structureType) const {
  return board.hasStructure(coord, direction, structureType);
}

void DoganGame::stealResource(int playerID, int stolenPlayerID) {
  checkPlayerExists(playerID);
  checkPlayerExists(stolenPlayerID);
  auto resourceCount = players.at(stolenPlayerID).getResourceCount();
  std::vector<int> availableIndices = {};

  for (int i = 0; i < 5; i++) {
    if (resourceCount[i] == 0) {
      continue;
    }
    availableIndices.push_back(i);
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
void DoganGame::checkPlayerExists(int playerID) const {
  if (players.find(playerID) == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID) +
                                  " invalid");
}
void DoganGame::checkPlayerCanAfford(int playerID,
                                     std::array<int, 5> cost) const {
  if (!players.at(playerID).canAfford(cost))
    throw InsufficientFundsException(
        "Error: Player does not have enough resources to build structure");
}
void DoganGame::checkBankCanAfford(ResourceType resourceType, int num) const {
  if (!bank.canAfford(resourceType, num))
    throw InsufficientFundsException(
        "Error: Bank does not have enough resources to build structure");
}
void DoganGame::checkPlayerHasDevelopmentCard(int playerID,
                                              DevelopmentType devType) const {
  std::stringstream oss;
  oss << "Error: Player does not have " << devType << " card";
  if (players.at(playerID).getDevelopmentCount()[static_cast<int>(devType)] ==
      0)
    throw InsufficientDevelopmentsException(oss.str());
}
void DoganGame::checkCoordinateValid(Coordinate2D coord) const {
  if (!board.hasTile(coord))
    throw CoordinateNotFoundException("Error: Invalid Coordinate");
}
void DoganGame::checkStructureExists(Coordinate2D coord, Direction direction,
                                     StructureType structureType) const {
  if (board.hasStructure(coord, direction, structureType))
    throw SameStructureException("Error: Structure already exists");
}
void DoganGame::checkResourceType(ResourceType resourceType) const {
  if (resourceType == ResourceType::OTHER)
    throw InvalidTypeException("Error: Resource type must be set");
}

std::ostream &operator<<(std::ostream &os, DoganGame const &dg) {
  os << dg.board;
  for (auto &p : dg.players) {
    os << p.second;
  }
  os << dg.bank;
  return os;
}