#pragma once

#include "DoganBank.h"
#include "DoganBoard.h"
#include "DoganPlayer.h"
#include <random>

class DoganGame {
public:
  DoganGame(DoganConfig config= DoganConfig());
  friend std::ostream &operator<<(std::ostream &os, DoganGame const &dg);
  void addPlayer(std::string pn, int pid);
  void purchaseDevelopmentCard(DoganPlayer p, std::array<size_t, 5> c);
  void buildStructure(Coordinate2D t, Direction d, DoganPlayer p,
                      StructureType st, std::array<size_t, 5> c);

private:
  DoganConfig config;
  std::mt19937 rengine;
  std::uniform_int_distribution<pip> die;
  DoganBank bank;
  DoganBoard board;
  std::map<int, DoganPlayer> players;
};