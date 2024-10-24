#include "Player.h"
#include "DoganExceptions.h"

namespace Dogan {
Player::Player(int pid, std::array<int, 3> as)
    : playerID(pid), inventory(), availableStructures(as), victoryPoints(0),
      soldierCount(0){};

void Player::giveDevelopment(DevelopmentType d) { addDevelopment(d); }

// Victory Point Functions
int Player::getVictoryPoints(void) const { return victoryPoints; }
void Player::setVictoryPoints(const int vp) { victoryPoints = vp; }
void Player::addVictoryPoints(const int vp) { victoryPoints += vp; }

void Player::addResources(std::array<int, 5> r) { inventory.addResources(r); }
void Player::addResource(const ResourceType r, int n) {
  inventory.addResource(r, n);
}

void Player::buildStructure(StructureType st) {
  if (availableStructures[static_cast<int>(st)] == 0) {
    throw InsufficientStructuresException("Error: Not enough structures");
  }
  availableStructures[static_cast<int>(st)] -= 1;
  victoryPoints += 1;
  if (st == StructureType::CITY) {
    availableStructures[static_cast<int>(StructureType::VILLAGE)] += 1;
  }
}

int Player::getSoldierCount(void) const { return soldierCount; }
void Player::increaseSoldierCount(void) { ++soldierCount; }

bool Player::canAfford(const std::array<int, 5> r) const {
  return inventory.canAfford(r);
}
std::array<int, 5> Player::getResourceCount(void) const {
  return inventory.getResourceCount();
}
std::array<int, 5> Player::getDevelopmentCount(void) const {
  return inventory.getDevelopmentCount();
}
int Player::getPlayerID(void) const { return playerID; }

void Player::addDevelopment(DevelopmentType d) {
  if (d == DevelopmentType::VICPOINT) {
    victoryPoints += 1;
  }
  inventory.addDevelopment(d);
}

std::ostream &operator<<(std::ostream &os, const Player &p) {
  os << "Player " << p.playerID << ": \n  VP: " << p.victoryPoints
     << "\n  Resource Cards:\n";
  for (size_t i = 0; i < 5; ++i) {
    os << "    " << static_cast<ResourceType>(i) << ": " << p.resources[i]
       << "\n";
  }
  os << "  Development Cards:\n";
  for (size_t i = 0; i < 5; ++i) {
    os << "    " << static_cast<DevelopmentType>(i) << ": "
       << p.inventory.getDevelopmentCount()[i] << "\n";
  }
  os << "\n";
  return os;
}
} // namespace Dogan