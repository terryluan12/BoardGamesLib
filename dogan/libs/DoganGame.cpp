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

void DoganGame::purchaseDevelopmentCard(DoganPlayer p,
                                        std::array<size_t, 5> c) {
  DevelopmentType dt = bank.popDevelopment();
  p.purchaseDevelopment(dt, c);
  bank.addResources(c);
}

void DoganGame::buildStructure(int playerID, size_t structType,
                               Coordinate2D tileLocation, std::string dir,
                               std::array<size_t, 5> cost) {

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
  this->players.at(playerID).buildStructure(element, cost);
  bank.removeResources(cost);
}

void DoganGame::giveResources(int playerID, std::array<size_t, 5> r) {
  this->players.at(playerID).getInventory().addResources(r);
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