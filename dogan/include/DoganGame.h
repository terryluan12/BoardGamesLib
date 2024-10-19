#pragma once

#include "DoganBank.h"
#include "DoganBoard.h"
#include "DoganConfig.h"
#include "DoganPlayer.h"
#include <random>

class DoganGame {
public:
  DoganGame(DoganConfig config = DoganConfig());
  void addPlayer(std::string pn, int pid);
  void purchaseDevelopmentCard(int playerID, std::array<int, 5> c);

  void tradeResources(int playerID1, std::array<int, 5> resources1,
                      int playerID2, std::array<int, 5> resources2);
  const std::array<int, 5> getResourceCount(int playerID) const;
  const std::array<int, 5> getDevelopmentCount(int playerID) const;
  void buildStructure(int playerID, StructureType structType,
                      Coordinate2D tileLocation, Direction direction,
                      std::array<int, 5> cost);
  void giveResources(int playerID, std::array<int, 5> resources);
  bool hasStructure(Coordinate2D coord, Direction direction,
                    StructureType structureType);
  int rollDice(void);
  void distributeResources(int numberRolled);

  int getVictoryPoints(int playerID) const;

  // Development Cards
  void useMonopolyDevelopmentCard(int playerID, ResourceType resource);
  void useSoldierDevelopmentCard(int playerID, Coordinate2D tileLocation,
                                 Direction d);
  void useRoadDevelopmentCard(int playerID,
                              std::array<Coordinate2D, 2> tileLocations,
                              std::array<Direction, 2> directions);
  void useTakeTwoDevelopmentCard(int playerID,
                                 std::array<ResourceType, 2> resources);
  void useRobber(int playerID, Coordinate2D tileLocation, Direction direction);

  friend std::ostream &operator<<(std::ostream &os, DoganGame const &dg);

private:
  DoganConfig config;
  std::mt19937 rengine;
  std::uniform_int_distribution<pip> die;
  DoganBank bank;
  DoganBoard board;
  std::map<int, DoganPlayer> players;
  std::pair<int, int> mostSoldiers;
  std::pair<int, int> longestRoad;

  void stealResource(int playerID, int stolenPlayerID);
  void checkPlayerExists(int playerID) const;
  void checkPlayerCanAfford(int playerID, std::array<int, 5> cost) const;
  void checkBankCanAfford(ResourceType resourceType, int num) const;
  void checkPlayerHasDevelopmentCard(int playerID, DevelopmentType devType) const;
  void checkCoordinateValid(Coordinate2D coord) const;
  void checkStructureExists(Coordinate2D coord, Direction direction, StructureType structureType) const;
  void checkResourceType(ResourceType resourceType) const;
};