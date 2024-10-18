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
  DoganPlayer(std::string n, int pid)
      : name(n), playerID(pid), victoryPoints(0){};
  friend std::ostream &operator<<(std::ostream &os, const DoganPlayer &p);

  int getVictoryPoints(void) const;
  void setVictoryPoints(const int vp);

  void setAvailableStructures(const std::array<size_t, 3> as);

  DoganBank getInventory(void) const;

  // Other Functions
  std::string getName(void) const;
  int getPlayerID(void) const;
  void purchaseDevelopment(DevelopmentType d, std::array<size_t, 5> c);
  void buildStructure(std::shared_ptr<DoganStructure> s,
                      std::array<size_t, 5> c);

private:
  std::string name;
  int playerID;
  DoganBank inventory;
  std::array<size_t, 3> availableStructures;
  std::array<size_t, 5> resources;
  std::array<size_t, 5> developments;
  std::vector<std::shared_ptr<DoganBuilding>> buildings;
  std::vector<std::shared_ptr<DoganRoad>> roads;
  int victoryPoints;
  void addDevelopment(DevelopmentType d);
  void buildStructure(std::shared_ptr<DoganStructure> s);
};