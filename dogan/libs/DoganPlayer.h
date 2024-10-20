#pragma once

#include "DoganBank.h"
#include "DoganBuilding.h"
#include "DoganRoad.h"
#include "DoganStructure.h"
#include "enums.h"
#include <array>
#include <memory>

class DoganPlayer {
public:
  DoganPlayer(std::string n, int pid, std::array<int, 3> as);

  // Game Functions
  void giveDevelopment(DevelopmentType d);
  void buildStructure(std::shared_ptr<DoganStructure> s, std::array<int, 5> c);

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
  friend std::ostream &operator<<(std::ostream &os, const DoganPlayer &p);

private:
  int playerID;
  DoganBank inventory;
  std::array<int, 3> availableStructures;
  std::array<int, 5> resources;
  std::array<int, 5> developments;
  std::vector<std::shared_ptr<DoganBuilding>> buildings;
  std::vector<std::shared_ptr<DoganRoad>> roads;
  int victoryPoints;
  int soldierCount;
  void addDevelopment(DevelopmentType d);
  void buildStructure(std::shared_ptr<DoganStructure> s);
};