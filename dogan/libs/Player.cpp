#include "Player.h"
#include "DoganExceptions.h"

namespace Dogan {
Player::Player(int pid, std::array<int, 3> as)
    : playerID(pid), inventory(), availableStructures(as), victoryPoints(0),
      soldierCount(0){};

void Player::giveDevelopment(DevelopmentType d) { addDevelopment(d); }
void Player::buildStructure(std::shared_ptr<Structure> s,
                            std::array<int, 5> c) {
  if (availableStructures[static_cast<int>(s->getStructureType())] <= 0) {
    throw InsufficientStructuresException(
        "Error: Player does not have enough structures");
  }
  std::array<int, 5> cost;
  std::transform(c.begin(), c.end(), cost.begin(), [](int x) { return -x; });
  inventory.addResources(cost);
  buildStructure(s);
  availableStructures[static_cast<int>(s->getStructureType())] -= 1;
}

// Victory Point Functions
int Player::getVictoryPoints(void) const { return victoryPoints; }
void Player::setVictoryPoints(const int vp) { victoryPoints = vp; }
void Player::addVictoryPoints(const int vp) { victoryPoints += vp; }

void Player::addResources(std::array<int, 5> r) { inventory.addResources(r); }
void Player::addResource(const ResourceType r, int n) {
  inventory.addResource(r, n);
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
void Player::buildStructure(std::shared_ptr<Structure> s) {
  switch (s->getStructureType()) {
  case (StructureType::VILLAGE):
  case (StructureType::CITY):
    buildings.emplace_back(std::dynamic_pointer_cast<Building>(s));
    victoryPoints += 1;
    break;
  case (StructureType::ROAD):
    roads.emplace_back(std::dynamic_pointer_cast<Road>(s));
    break;
  case (StructureType::PORT):
    throw InvalidTypeException("Error: Cannot build a port");
  }
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