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

void DoganGame::addPlayer(std::string pn, int pid) {
  DoganPlayer p = DoganPlayer(pn, pid);
  p.setAvailableStructures(config.getTotalStructureCount());
  this->players.push_back(p);
};

void DoganGame::purchaseDevelopmentCard(DoganPlayer p, std::array<size_t, 5> c) {
  DevelopmentType dt = bank.popDevelopment();
  p.purchaseDevelopment(dt, c);
  bank.addResources(c);
}

void DoganGame::buildStructure(Coordinate2D t, Direction d, DoganPlayer p,
                               StructureType st, std::array<size_t, 5> c) {
    p.buildStructure(st, c);
    board.buildStructure(t, d, p.getPlayerID(), st);
}

void DoganGame::printBoard(void) {
  std::cout << this->board;
  for (auto &p : this->players) {
    std::cout << p;
  }
  std::cout << this->bank;
}