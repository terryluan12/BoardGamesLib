#pragma once

#include "DoganConfig.h"
#include "DoganBank.h"
#include "DoganBoard.h"
#include "DoganPlayer.h"
#include <random>

class DoganGame {
public:
  DoganGame(DoganConfig config = DoganConfig());
  friend std::ostream &operator<<(std::ostream &os, DoganGame const &dg);
  void addPlayer(std::string pn, int pid);
  void purchaseDevelopmentCard(int playerID, std::array<size_t, 5> c);
  
  void tradeResources(int playerID1, std::array<size_t, 5> resources1,
                               int playerID2, std::array<size_t, 5> resources2);
  const std::array<size_t, 5> getResourceCount(int playerID);
  const std::array<size_t, 5> getDevelopmentCount(int playerID);
  void buildStructure(int playerID, size_t structType,
                      Coordinate2D tileLocation, std::string dir,
                      std::array<size_t, 5> cost);
  void giveResources(int playerID, std::array<size_t, 5> r);
  bool hasStructure(Coordinate2D coord, std::string dir, int structureType);
private:
  DoganConfig config;
  std::mt19937 rengine;
  std::uniform_int_distribution<pip> die;
  DoganBank bank;
  DoganBoard board;
  std::map<int, DoganPlayer> players;
};