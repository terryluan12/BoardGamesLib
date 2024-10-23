#pragma once

#include "Bank.h"
#include "Board.h"
#include "Config.h"
#include "Player.h"
#include <random>

namespace Dogan {
class Game {
public:
  Game(Config config = Config());

  // Start phase functions
  void addPlayer(int pid);
  void giveResources(int playerID, std::array<int, 5> resources);

  // General Game functions (to be used during turn phases)
  int rollDice(void);
  void distributeResources(int numberRolled);

  void buildStructure(int playerID, StructureType structType,
                      Coordinate2D tileLocation, Direction direction,
                      std::array<int, 5> cost, bool mustBeAdjacent = true);
  void purchaseDevelopmentCard(int playerID, std::array<int, 5> c);
  void tradeResources(int playerID1, std::array<int, 5> resources1,
                      int playerID2, std::array<int, 5> resources2);

  void useRobber(int playerID, Coordinate2D tileLocation, Direction direction);

  // Development Cards
  void useMonopolyDevelopmentCard(int playerID, ResourceType resource);
  void useSoldierDevelopmentCard(int playerID, Coordinate2D tileLocation,
                                 Direction d);
  void useRoadDevelopmentCard(int playerID,
                              std::array<Coordinate2D, 2> tileLocations,
                              std::array<Direction, 2> directions);
  void useTakeTwoDevelopmentCard(int playerID,
                                 std::array<ResourceType, 2> resources);

  // Accessor functions
  const std::array<int, 5> getResourceCount(int playerID) const;
  const std::array<int, 5> getDevelopmentCount(int playerID) const;
  int getVictoryPoints(int playerID) const;
  bool hasStructure(Coordinate2D coord, Direction direction,
                    StructureType structureType) const;

  friend std::ostream &operator<<(std::ostream &os, Game const &dg);

private:
  Config config;
  std::uniform_int_distribution<pip> die;
  Bank bank;
  Board board;
  std::map<int, Player> players;
  std::pair<int, int> mostSoldiers;
  std::pair<int, int> longestRoad;
  std::mt19937 rengine;

  void stealResource(int playerID, int stolenPlayerID);
  // Check functions
  void checkPlayerExists(int playerID) const;
  void checkPlayerCanAfford(int playerID, std::array<int, 5> cost) const;
  void checkBankCanAfford(ResourceType resourceType, int num) const;
  void checkPlayerHasDevelopmentCard(int playerID,
                                     DevelopmentType devType) const;
  void checkCoordinateValid(Coordinate2D coord) const;
  void checkStructureExists(Coordinate2D coord, Direction direction,
                            StructureType structureType) const;
  void checkResourceType(ResourceType resourceType) const;
};
} // namespace Dogan