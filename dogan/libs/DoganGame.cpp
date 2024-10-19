#include "DoganGame.h"
#include "DoganBuilding.h"
#include "DoganExceptions.h"
#include "DoganRoad.h"
#include "enums.h"
#include <memory>

DoganGame::DoganGame(DoganConfig config)
    : config(config), rengine(std::random_device{}()), die(1, 6),
      board(DoganBoard(config)) {
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

void DoganGame::purchaseDevelopmentCard(int playerID,
                                        std::array<int, 5> cost) {
  const auto pe = players.find(playerID);
  if(pe == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID) + " invalid");
  DoganPlayer &p = players.at(playerID);
  if(!p.canAfford(cost))
    throw InsufficientResourcesException(p.getName() + " can't afford this trade");
  DevelopmentType dt = bank.popDevelopment();
  p.giveDevelopment(dt);
  bank.addResources(cost);
}


void DoganGame::tradeResources(int playerID1, std::array<int, 5> resources1,
                               int playerID2, std::array<int, 5> resources2) {
  auto pe1 = players.find(playerID1), pe2 = players.find(playerID2);
  if(pe1 == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID1) + " invalid");
  if(pe2 == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID2) + " invalid");

  DoganPlayer &p1 = players.at(playerID1), &p2 = players.at(playerID2);
  if(!p1.canAfford(resources1))
    throw InsufficientResourcesException(p1.getName() + " can't afford this trade");
  if(!p2.canAfford(resources2))
    throw InsufficientResourcesException(p2.getName() + " can't afford this trade");
  
  p1.removeResources(resources1);
  p2.addResources(resources1);
  p2.removeResources(resources2);
  p1.addResources(resources2);
  }

const std::array<int, 5> DoganGame::getResourceCount(int playerID) const {
  if(playerID == -1) {
    return bank.getResourceCount();
  }
  auto pe = players.find(playerID);
  if(pe == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID) + " invalid");
  return players.at(playerID).getResourceCount();
}
const std::array<int, 5> DoganGame::getDevelopmentCount(int playerID) const {
  if(playerID == -1) {
    return bank.getDevelopmentCount();
  }
  auto pe = players.find(playerID);
  if(pe == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID) + " invalid");
  return players.at(playerID).getDevelopmentCount();
}


void DoganGame::buildStructure(int playerID, size_t structType,
                               Coordinate2D tileLocation, std::string dir,
                               std::array<int, 5> cost) {
  auto pe = players.find(playerID);
  if(pe == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID) + " invalid");
  
  if (!pe->second.canAfford(cost)) 
    throw InsufficientFundsException(
        "Error: Player does not have enough resources to build structure");
  DoganPlayer &p = players.at(playerID);

  Direction d = AxialHexDirection::fromString(dir);
  StructureType st = DoganStructureType::fromInt(structType);

  if(!board.hasTile(tileLocation))
    throw CoordinateNotFoundException("Error: Invalid Coordinate");

  if (board.hasStructure(tileLocation, d, st))
    throw SameStructureException("Error: Structure already exists");

  std::shared_ptr<DoganStructure> element;


  switch (st) {
  case StructureType::VILLAGE:
  case StructureType::CITY:
    element = std::make_shared<DoganBuilding>(
        DoganBuilding(playerID, st, DoganVertex(tileLocation, d)));
    break;
  case StructureType::ROAD:
    element =
        std::make_shared<DoganRoad>(DoganRoad(playerID, st, DoganEdge(tileLocation, d)));
    break;
  }
  board.buildStructure(element, cost);
  p.buildStructure(element, cost);
  bank.addResources(cost);
}

void DoganGame::giveResources(int playerID, std::array<int, 5> resources) {
  auto pe = players.find(playerID);
  if(pe == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID) + " invalid");
  players.at(playerID).addResources(resources);
}

bool DoganGame::hasStructure(Coordinate2D coord, std::string dir, int structureType) {
  StructureType st = DoganStructureType::fromInt(structureType);
  return board.hasStructure(coord, AxialHexDirection::fromString(dir), st);
}

int DoganGame::rollDice(void) {
  return die(rengine) + die(rengine);
}


void DoganGame::distributeResources(int numberRolled) {
  auto buildings = board.getResourceDistribution(numberRolled);
  for(auto [pid, resources] : buildings) {

    auto player = players.find(pid);
    if(player == players.end())
      throw PlayerNotFoundException("Player ID " + std::to_string(pid) + " invalid");
    
    for(size_t i = 0; i < resources.size(); i++) {
      if(bank.canAfford(i, resources[i])) {
        bank.removeResource(static_cast<ResourceType>(i), resources[i]);
        players.at(pid).addResource(static_cast<ResourceType>(i), resources[i]);
      }
      else {
        throw InsufficientResourcesException("Bank does not have enough resources to distribute");
      }
    }
  }
}

int DoganGame::getVictoryPoints(int playerID) {
  auto player = players.find(playerID);
  if(player == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID) + " invalid");
  return players.at(playerID).getVictoryPoints();
}


void DoganGame::useMonopolyDevelopmentCard(int playerID, ResourceType resource) {
  auto player = players.find(playerID);
  if(player == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID) + " invalid");
  if (player->second.getDevelopmentCount()[static_cast<int>(DevelopmentType::MONOPOLY)] == 0)
    throw InsufficientDevelopmentsException("Error: Player does not have a monopoly card");
  if(resource == ResourceType::OTHER)
    throw InvalidTypeException("Error: Resource type must be set");

  int resourceIndex = static_cast<int>(resource);
    
  for(auto &[pid, p] : players) {
    if(pid == playerID)
      continue;
    int stolenCount = p.getResourceCount()[resourceIndex];
    players.at(playerID).addResource(resource, stolenCount);
    p.removeResource(resource, stolenCount);
  }
}

void DoganGame::useSoldierDevelopmentCard(int playerID, Coordinate2D tileLocation, Direction direction) {
  players.at(playerID).increaseSoldierCount();
  int soldierCount = players.at(playerID).getSoldierCount();
  if(soldierCount >= 3 && soldierCount > mostSoldiers.second) {
    players.at(mostSoldiers.first).addVictoryPoints(-2);
    mostSoldiers = {playerID, soldierCount};
    players.at(playerID).addVictoryPoints(2);
  }

  useRobber(playerID, tileLocation, direction);
}

void DoganGame::useRobber(int playerID, Coordinate2D tileLocation, Direction direction) {
    if(!board.hasBuilding(tileLocation, direction))
      throw NoSuchStructureException("Error: No Building at given location");

    board.moveRobber(tileLocation);

    int stolenPID = board.getBuilding(tileLocation, direction).getPlayerID();
    stealResource(playerID, stolenPID);
}

void DoganGame::stealResource(int playerID, int stolenPlayerID) {
  auto player = players.find(playerID);
  if(player == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID) + " invalid");
  auto stolenPlayer = players.find(stolenPlayerID);
  if(stolenPlayer == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(stolenPlayerID) + " invalid");
    
  auto resourceCount = players.at(stolenPlayerID).getResourceCount();
  std::vector<int> availableIndices = {};

  for(int i = 0; i < 5; i++) {
    if(resourceCount[i] == 0) {
      continue;
    }
    availableIndices.push_back(i);
  }
  if(availableIndices.size() == 0) {
    throw InsufficientResourcesException("Error: Player does not have enough resources to steal");
  }
  std::uniform_int_distribution<std::size_t> randomPicker(0, availableIndices.size() - 1);
  ResourceType resourceStolen = static_cast<ResourceType>(availableIndices[randomPicker(rengine)]);

  players.at(stolenPlayerID).removeResource(resourceStolen, 1);
  players.at(playerID).addResource(resourceStolen, 1);
}



std::ostream &operator<<(std::ostream &os, DoganGame const &dg) {
  os << dg.board;
  for (auto &p : dg.players) {
    os << p.second;
  }
  os << dg.bank;
  return os;
}