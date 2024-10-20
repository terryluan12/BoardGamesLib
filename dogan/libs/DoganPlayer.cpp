#include "DoganPlayer.h"
#include "DoganExceptions.h"

DoganPlayer::DoganPlayer(std::string n, int pid, std::array<int, 3> as)
    : playerID(pid), inventory(), availableStructures(as), victoryPoints(0),
      soldierCount(0){};

void DoganPlayer::giveDevelopment(DevelopmentType d) { addDevelopment(d); }
void DoganPlayer::buildStructure(std::shared_ptr<DoganStructure> s,
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
int DoganPlayer::getVictoryPoints(void) const { return victoryPoints; }
void DoganPlayer::setVictoryPoints(const int vp) { victoryPoints = vp; }
void DoganPlayer::addVictoryPoints(const int vp) { victoryPoints += vp; }

void DoganPlayer::addResources(std::array<int, 5> r) {
  inventory.addResources(r);
}
void DoganPlayer::addResource(const ResourceType r, int n) {
  inventory.addResource(r, n);
}

int DoganPlayer::getSoldierCount(void) const { return soldierCount; }
void DoganPlayer::increaseSoldierCount(void) { ++soldierCount; }

bool DoganPlayer::canAfford(const std::array<int, 5> r) const {
  return inventory.canAfford(r);
}
std::array<int, 5> DoganPlayer::getResourceCount(void) const {
  return inventory.getResourceCount();
}
std::array<int, 5> DoganPlayer::getDevelopmentCount(void) const {
  return inventory.getDevelopmentCount();
}
int DoganPlayer::getPlayerID(void) const { return playerID; }

void DoganPlayer::addDevelopment(DevelopmentType d) {
  if (d == DevelopmentType::VICPOINT) {
    victoryPoints += 1;
  }
  inventory.addDevelopment(d);
}
void DoganPlayer::buildStructure(std::shared_ptr<DoganStructure> s) {
  switch (s->getStructureType()) {
  case (StructureType::VILLAGE):
  case (StructureType::CITY):
    buildings.push_back(std::dynamic_pointer_cast<DoganBuilding>(s));
    victoryPoints += 1;
    break;
  case (StructureType::ROAD):
    roads.push_back(std::dynamic_pointer_cast<DoganRoad>(s));
    break;
  case (StructureType::PORT):
    throw InvalidTypeException("Error: Cannot build a port");
  }
}

std::ostream &operator<<(std::ostream &os, const DoganPlayer &p) {
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