#include "Cell.h"
#include "DoganExceptions.h"

namespace Dogan {
Cell::Cell(bool cr, Coordinate2D c, int n, ResourceType t)
    : coordinate(c), type(t) {}

Coordinate2D Cell::getCoordinate(void) const { return coordinate; }

ResourceType Cell::getResource(void) const { return this->type; }

bool Cell::hasAdjacentBuildings(Direction d) const {
  const auto cwDir = AxialHexDirection::vertexDirections[((AxialHexDirection::getVertexIndex(d)+1)%7)];
  const auto ccwDir = AxialHexDirection::vertexDirections[((AxialHexDirection::getVertexIndex(d)-1+7)%7)];
  return (hasBuilding(cwDir) || hasBuilding(ccwDir));
}

bool Cell::hasStructure(Direction d, StructureType st) const {
  switch (st) {
  case StructureType::CITY:
  case StructureType::VILLAGE:
    if(!hasBuilding(d)) return false;
    return buildings.at(d)->getStructureType() == st;
    break;
  case StructureType::ROAD:
    return hasRoad(d);
    break;
  default:
    throw InvalidTypeException("Error: Invalid type");
    break;
  }
}


void Cell::addStructure(Direction d, StructureType st,
                  std::shared_ptr<Structure> ds) {
  switch (st) {
  case StructureType::VILLAGE:
    buildings.emplace(d, std::dynamic_pointer_cast<Building>(ds));
    break;
  case StructureType::ROAD:
    roads.emplace(d, std::dynamic_pointer_cast<Road>(ds));
    break;
  case StructureType::PORT:
    ports.emplace(coordinate, std::dynamic_pointer_cast<Port>(ds));
    break;
  default:
    throw InvalidTypeException("Error: Invalid type. Must be a village or a road. City must be upgraded from upgradeToCity function");
    break;
  }
}
bool Cell::hasBuilding(Direction d) const {
  return buildings.contains(d);
}
std::shared_ptr<Building> Cell::getBuilding(Direction d) const {
  return buildings.at(d);
}
std::vector<std::shared_ptr<Building>> Cell::getBuildings(void) const {
  std::vector<std::shared_ptr<Building>> buildingsVector;
  for(auto [d, b] : buildings){
    buildingsVector.push_back(b);
  }
  return buildingsVector;
}


bool Cell::hasRoad(Direction d) const {
  return roads.contains(d);
}
std::shared_ptr<Road> Cell::getRoad(Direction d) const {
  return roads.at(d);
}

void Cell::upgradeToCity(Direction d) {
  if (!hasStructure(d, StructureType::VILLAGE)){
    throw NoVillageException("Error: Must build city on village");
  }
  buildings.at(d)->upgradeToCity();
}


std::ostream &operator<<(std::ostream &os, Cell const &dc) {
  os << "Cell " << dc.getCoordinate() << ": " << dc.getResource() << "\n";
  return os;
}
} // namespace Dogan