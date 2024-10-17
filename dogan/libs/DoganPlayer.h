#pragma once

#include "DoganBank.h"
#include "DoganStructure.h"
#include "enums.h"
#include <array>

class DoganPlayer {
public:
  DoganPlayer(std::string n, int pid)
      : name(n), playerID(pid), victoryPoints(0){};

  int getVictoryPoints(void) const;
  void setVictoryPoints(const int vp);

  void setAvailableStructures(const std::array<size_t, 3> as);

  DoganBank getInventory(void) const;

  // Other Functions
  const std::array<size_t, 10> getFullCount(void) const;
  std::string getName(void) const;
  int getPlayerID(void) const;
  void giveDevelopment(DevelopmentType dt);
  void buildStructure(StructureType st);

private:
  std::string name;
  int playerID;
  DoganBank inventory;
  std::array<size_t, 3> availableStructures;
  std::array<size_t, 5> resources;
  std::array<size_t, 5> developments;
  std::vector<DoganBuilding<StructureType::VILLAGE>> villages;
  std::vector<DoganBuilding<StructureType::CITY>> cities;
  int victoryPoints;
};

std::ostream &operator<<(std::ostream &os, const DoganPlayer &p);