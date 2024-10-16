#include "DoganGame.h"
#include "DoganExceptions.h"
#include <iostream>

DoganGame::DoganGame(DoganConfig config)
    : config(config), rengine(std::random_device{}()), die(1, 6),
      board(DoganBoard(config)) {
  std::array<size_t, 5> resourceCount = config.getResourceCount();
  std::vector<DevelopmentType> developments = config.getDevelopments(rengine);
  bank = DoganBank(resourceCount, developments);
}

void DoganGame::addPlayer(DoganPlayer p) {
  p.setAvailableStructures(config.getTotalStructureCount());
  this->players.push_back(p);
};

void DoganGame::givePlayerDevCard(DoganPlayer p, std::array<size_t, 5> c) {
  if (p.getInventory().canAfford(c)) {
    p.getInventory().removeResources(c);
    p.giveDevelopment(bank.popDevelopment());
  } else {
    throw InsufficientResourcesException(
        "Error: Player does not have enough resources to purchase development "
        "card");
  }
}
void DoganGame::buildStructure(Coordinate2D t, Direction d, DoganPlayer p,
                               StructureType st, std::array<size_t, 5> c) {
  if (p.getInventory().canAfford(c)) {
    board.buildStructure(t, d, p.getPlayerID(), st);
    p.buildStructure(st);
  } else {
    throw InsufficientResourcesException(
        "Error: Player does not have enough resources to build city");
  }
}

void DoganGame::printBoard(void) {
  std::cout << this->board;
  for (auto &p : this->players) {
    std::cout << p;
  }
  std::cout << this->bank;
}