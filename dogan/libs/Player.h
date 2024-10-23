#pragma once

#include "Bank.h"
#include "Building.h"
#include "Road.h"
#include "Structure.h"
#include "enums.h"
#include <array>
#include <memory>

namespace Dogan {
class Player {
public:
  Player(int pid, std::array<int, 3> as);

  // Game Functions
  void giveDevelopment(DevelopmentType d);

  int getVictoryPoints(void) const;
  void setVictoryPoints(const int vp);
  void addVictoryPoints(const int vp);

  void addResources(std::array<int, 5> r);
  void addResource(const ResourceType r, int n);

  int getSoldierCount(void) const;
  void increaseSoldierCount(void);

  // General Accessors
  bool canAfford(const std::array<int, 5> r) const;
  std::array<int, 5> getResourceCount(void) const;
  std::array<int, 5> getDevelopmentCount(void) const;
  int getPlayerID(void) const;
  friend std::ostream &operator<<(std::ostream &os, const Player &p);

private:
  int playerID;
  Bank inventory;
  std::array<int, 3> availableStructures;
  std::array<int, 5> resources;
  std::array<int, 5> developments;
  int victoryPoints;
  int soldierCount;
  void addDevelopment(DevelopmentType d);
};
} // namespace Dogan