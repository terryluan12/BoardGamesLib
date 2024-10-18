#include "DoganGame.h"
#include "DoganBuilding.h"
#include "DoganExceptions.h"
#include "DoganRoad.h"
#include "enums.h"
#include <memory>

DoganGame::DoganGame(DoganConfig config)
    : config(config), rengine(std::random_device{}()), die(1, 6),
      board(DoganBoard(config)) {
  std::array<size_t, 5> resourceCount = config.getResourceCount();
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
                                        std::array<size_t, 5> cost) {
  auto pe = players.find(playerID);
  if(pe == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID) + " invalid");
  DoganPlayer &p = pe->second;
  if(!p.canAfford(cost))
    throw InsufficientResourcesException(p.getName() + " can't afford this trade");

  DevelopmentType dt = bank.popDevelopment();
  p.giveDevelopment(dt);
  bank.addResources(cost);
}


void DoganGame::tradeResources(int playerID1, std::array<size_t, 5> resources1,
                               int playerID2, std::array<size_t, 5> resources2) {
  auto pe1 = players.find(playerID1), pe2 = players.find(playerID2);
  if(pe1 == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID1) + " invalid");
  if(pe2 == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID2) + " invalid");

  DoganPlayer &p1 = pe1->second, &p2 = pe2->second;
  if(!p1.canAfford(resources1))
    throw InsufficientResourcesException(p1.getName() + " can't afford this trade");
  if(!p2.canAfford(resources2))
    throw InsufficientResourcesException(p2.getName() + " can't afford this trade");
  
  p1.removeResources(resources1);
  p2.addResources(resources1);
  p2.removeResources(resources2);
  p1.addResources(resources2);
  }

const std::array<size_t, 5> DoganGame::getResourceCount(int playerID) {
  auto pe = players.find(playerID);
  if(pe == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID) + " invalid");
  return pe->second.getResourceCount();
}
const std::array<size_t, 5> DoganGame::getDevelopmentCount(int playerID) {
  auto pe = players.find(playerID);
  if(pe == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID) + " invalid");
  return pe->second.getDevelopmentCount();
}


void DoganGame::buildStructure(int playerID, size_t structType,
                               Coordinate2D tileLocation, std::string dir,
                               std::array<size_t, 5> cost) {
  auto pe = players.find(playerID);
  if(pe == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID) + " invalid");
  
  if (!pe->second.canAfford(cost)) 
    throw InsufficientFundsException(
        "Error: Player does not have enough resources to build structure");
  DoganPlayer &p = pe->second;

  Direction d = AxialHexDirection::fromString(dir);
  StructureType st = DoganStructureType::fromInt(structType);

  std::shared_ptr<DoganStructure> element;

  switch (st) {
  case StructureType::VILLAGE:
  case StructureType::CITY:
    element = std::make_shared<DoganBuilding>(
        DoganBuilding(playerID, st, tileLocation, d));
    break;
  case StructureType::ROAD:
    element =
        std::make_shared<DoganRoad>(DoganRoad(playerID, st, tileLocation, d));
    break;
  }
  board.buildStructure(element, cost);
  p.buildStructure(element, cost);
  bank.removeResources(cost);
}

void DoganGame::giveResources(int playerID, std::array<size_t, 5> r) {
  auto pe = players.find(playerID);
  if(pe == players.end())
    throw PlayerNotFoundException("Player ID " + std::to_string(playerID) + " invalid");
  pe->second.addResources(r);
}

bool DoganGame::hasStructure(Coordinate2D coord, std::string dir, int structureType) {
  StructureType st = DoganStructureType::fromInt(structureType);
  return board.hasStructure(coord, AxialHexDirection::fromString(dir), st);
}

std::ostream &operator<<(std::ostream &os, DoganGame const &dg) {
  os << dg.board;
  for (auto &p : dg.players) {
    os << p.second;
  }
  os << dg.bank;
  return os;
}