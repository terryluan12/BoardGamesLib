#include "Cell.h"
#include "Board.h"
#include "DoganExceptions.h"
#include "Vertex.h"
#include "Edge.h"

namespace Dogan {
Cell::Cell(Board &b, bool cr, Coordinate2D c, int n, ResourceType t)
    : board(b), coordinate(c), type(t) {
    }

Coordinate2D Cell::getCoordinate(void) const { return coordinate; }

ResourceType Cell::getResource(void) const { return this->type; }

void Cell::setBoard(Board &b) {
  board = b;
}


bool Cell::hasAdjacentBuildings(Direction d) const {
  std::array<HexPath, 4> potentialPaths = Vertex::getAdjacentVertices(d);
  for (auto [travelDirection, vertexDirection] : potentialPaths) {
  Coordinate2D adjCell = coordinate + AxialDirection::toCoordinate(travelDirection);
  if (board.hasTile(adjCell)) {
  return board.getTile(adjCell)->hasBuilding(vertexDirection);
    }
  }
  return false;
}

bool Cell::hasOwnConnectedRoads(int pid, Direction d, StructureType st) const {
  std::vector<HexPath> potentialPaths{};
    if (st == StructureType::ROAD) {
    auto edges = Edge::getAdjacentEdges(d);
    potentialPaths.insert(potentialPaths.end(), edges.begin(), edges.end());
  } else if (st == StructureType::VILLAGE || st == StructureType::CITY) {
    auto edges = Vertex::getAdjacentEdges(d);
    potentialPaths.insert(potentialPaths.end(), edges.begin(), edges.end());
  }
  for (auto [travelDirection, edgeDirection] : potentialPaths) {
    Coordinate2D adjCell = coordinate + AxialDirection::toCoordinate(travelDirection);
    if (board.hasTile(adjCell)){
      auto cell = board.getTile(adjCell);
      if(cell->hasRoad(edgeDirection) && cell->getRoad(edgeDirection)
      ->getPlayerID() == pid){
        return true;
      }
    }
}
  return false;
}

bool Cell::hasStructure(Direction d, StructureType st) const {
  switch (st) {
  case StructureType::CITY:
  case StructureType::VILLAGE:
    if (!hasBuilding(d))
      return false;
    return buildings.at(d)->getStructureType() == st;
  case StructureType::ROAD:
    return hasRoad(d);
  case StructureType::PORT:
    return ports.contains(d);
  default:
    throw std::invalid_argument("Error: Invalid Structure Type");
  }
}

void Cell::buildStructure(int pid, Direction direction,
                          std::shared_ptr<Structure> ds, bool mustBeAdjacent) {
  if (ds->getStructureType() == StructureType::CITY) {
    throw BuildStructureException("Error: Cannot build city on its own. Must "
                                  "upgrade using upgradeToCity");
  }
  if (hasStructure(direction, ds->getStructureType())) {
    throw BuildStructureException("Error: Cannot build on existing structure");
  }
  if (ds->getStructureType() == StructureType::VILLAGE &&
      hasAdjacentBuildings(direction)) {
    throw BuildStructureException(
        "Error: Building too close to another building");
  }
  if (mustBeAdjacent &&
      !hasOwnConnectedRoads(pid, direction, ds->getStructureType())) {
    throw BuildStructureException("Error: Must build adjacent to road");
  }
  switch (ds->getStructureType()) {
  case StructureType::VILLAGE:
    if (hasStructure(direction, StructureType::CITY)) {
      throw BuildStructureException(
          "Error: Cannot build on existing structure");
    }
    buildings.emplace(direction, std::dynamic_pointer_cast<Building>(ds));
    break;
  case StructureType::ROAD:
    roads.emplace(direction, std::dynamic_pointer_cast<Road>(ds));
    break;
  case StructureType::PORT:
    ports.emplace(direction, std::dynamic_pointer_cast<Port>(ds));
    break;
  default:
    break;
  }
}

bool Cell::hasBuilding(Direction d) const { return buildings.contains(d); }
std::shared_ptr<Building> Cell::getBuilding(Direction d) const {
  return buildings.at(d);
}
std::vector<std::shared_ptr<Building>> Cell::getBuildings(void) const {
  std::vector<std::shared_ptr<Building>> buildingsVector;
  for (auto [d, b] : buildings) {
    buildingsVector.push_back(b);
  }
  return buildingsVector;
}

bool Cell::hasRoad(Direction d) const { return roads.contains(d); }
std::shared_ptr<Road> Cell::getRoad(Direction d) const { return roads.at(d); }

void Cell::upgradeToCity(int pid, Direction d) {
  if (!hasStructure(d, StructureType::VILLAGE)) {
    throw BuildStructureException("Error: Must build city on village");
  }
  if (buildings.at(d)->getPlayerID() != pid) {
    throw BuildStructureException(
        "Error: Cannot upgrade another player's building");
  }
  buildings.at(d)->upgradeToCity();
}

std::ostream &operator<<(std::ostream &os, Cell const &dc) {
  os << "Cell " << dc.getCoordinate() << ": " << dc.getResource() << "\n";
  return os;
}
} // namespace Dogan