#include "DoganPlayer.h"

// Victory Point Functions

int DoganPlayer::getVictoryPoints(void) const { return victoryPoints; }
void DoganPlayer::setVictoryPoints(const int vp) { victoryPoints = vp; }

void DoganPlayer::setAvailableStructures(const std::array<size_t, 3> as) {
  availableStructures = as;
}

DoganBank DoganPlayer::getInventory(void) const { return inventory; }

std::string DoganPlayer::getName(void) const { return name; }

int DoganPlayer::getPlayerID(void) const { return playerID; }

void DoganPlayer::giveDevelopment(DevelopmentType dt) {
  if (dt == DevelopmentType::VICPOINT) {
    ++victoryPoints;
  }
  inventory.addDevelopment(dt);
}

void DoganPlayer::buildStructure(StructureType st) {
  if (st == StructureType::VILLAGE || st == StructureType::CITY) {
    ++victoryPoints;
  }

  if (availableStructures[static_cast<int>(st)] == 0) {
    throw std::invalid_argument(
        "Error: Player does not have enough structures");
  }
  availableStructures[static_cast<int>(st)] -= 1;
}

std::ostream &operator<<(std::ostream &os, const DoganPlayer &p) {
  os << "Player " << p.getName() << ": \n  VP: " << p.getVictoryPoints()
     << "\n  Resource Cards:\n";
  for (size_t i = 0; i < 5; ++i) {
    os << "    " << static_cast<ResourceType>(i) << ": " << p.getInventory().getResourceCount()[i] << "\n";
  }
  os << "  Development Cards:\n";
  for (size_t i = 0; i < 5; ++i) {
    os << "    " << static_cast<DevelopmentType>(i) << ": " << p.getInventory().getDevelopmentCount()[i]
       << "\n";
  }
  os << "\n";
  return os;
}