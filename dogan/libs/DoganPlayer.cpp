#include "DoganPlayer.h"
#include "DoganExceptions.h"

// Victory Point Functions
int DoganPlayer::getVictoryPoints(void) const { return victoryPoints; }
void DoganPlayer::setVictoryPoints(const int vp) { victoryPoints = vp; }

void DoganPlayer::setAvailableStructures(const std::array<size_t, 3> as) {
  availableStructures = as;
}

DoganBank DoganPlayer::getInventory(void) const { return inventory; }

std::string DoganPlayer::getName(void) const { return name; }

int DoganPlayer::getPlayerID(void) const { return playerID; }

void DoganPlayer::purchaseDevelopment(DevelopmentType d,
                                      std::array<size_t, 5> c) {
  if (!inventory.canAfford(c)) {
    throw InsufficientFundsException(
        "Error: Player does not have enough resources to purchase development "
        "card");
  }
  inventory.removeResources(c);
  addDevelopment(d);
}

void DoganPlayer::buildStructure(StructureType s, std::array<size_t, 5> c) {
  if (!inventory.canAfford(c)) {
    throw InsufficientFundsException(
        "Error: Player does not have enough resources to build structure");
  }
  if (availableStructures[static_cast<int>(s)] <= 0) {
    throw InsufficientStructuresException(
        "Error: Player does not have enough structures");
  }

  inventory.removeResources(c);
  buildStructure(s);
  availableStructures[static_cast<int>(s)] -= 1;
}

void DoganPlayer::addDevelopment(DevelopmentType d) {
  if (d == DevelopmentType::VICPOINT) {
    victoryPoints += 1;
  }
  inventory.addDevelopment(d);
}
void DoganPlayer::buildStructure(StructureType s) {
  if (s == StructureType::VILLAGE) {
    DoganBuilding db = DoganBuilding<StructureType::VILLAGE>(playerID);
    villages.push_back(db);
    victoryPoints += 1;
  } else if (s == StructureType::CITY) {
    DoganBuilding db = DoganBuilding<StructureType::CITY>(playerID);
    cities.push_back(db);
    victoryPoints += 1;
  }
}

std::ostream &operator<<(std::ostream &os, const DoganPlayer &p) {
  os << "Player " << p.getName() << ": \n  VP: " << p.getVictoryPoints()
     << "\n  Resource Cards:\n";
  for (size_t i = 0; i < 5; ++i) {
    os << "    " << static_cast<ResourceType>(i) << ": "
       << p.getInventory().getResourceCount()[i] << "\n";
  }
  os << "  Development Cards:\n";
  for (size_t i = 0; i < 5; ++i) {
    os << "    " << static_cast<DevelopmentType>(i) << ": "
       << p.getInventory().getDevelopmentCount()[i] << "\n";
  }
  os << "\n";
  return os;
}