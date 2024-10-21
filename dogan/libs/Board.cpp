#include "Board.h"
#include "ElementHelpers.h"
#include "enums.h"
#include <memory>
#include "AxialHexDirection.h"
#include <iostream>

namespace Dogan {
Board::Board(Config config) {
  rengine.seed(std::random_device{}());

  this->boardSize = config.getBoardSize();
  this->robberLocation = config.getRobberLocation();
  std::vector<pip> numberOrder = config.getNumbers(rengine);
  std::vector<ResourceType> resources = config.getResources(rengine);
  auto portLocations = config.getPortLocations();
  auto portResources = config.getPortResources(rengine);

  // create all tiles
  size_t i = 0;
  for (const auto &c : config.getTileLocations()) {
    if (this->hasTile(c)) {
      throw std::invalid_argument("Error: Cell already exists");
    }
    std::shared_ptr<Cell> dc =
        std::make_shared<Cell>(Cell(false, c, numberOrder[i], resources[i]));
    this->cells.insert(std::make_pair(c, dc));
    if (numbers.find(numberOrder[i]) == numbers.end()) {
      this->numbers.emplace(numberOrder[i],
                            std::vector<std::shared_ptr<Cell>>{});
    }
    this->numbers.at(numberOrder[i]).emplace_back(dc);

    ++i;
  }

  // Add all Ports
  for (size_t i = 0; i < config.getPortLocations().size(); i++) {
    const auto portVertices = portLocations[i];
    for (auto vertex : portVertices) {
      for (auto [coordinate, direction] : getAllVertexRepresentations(vertex)) {
        if (this->ports.find(coordinate) == this->ports.end()) {
          this->ports.emplace(coordinate,
                              std::map<Direction, std::shared_ptr<Port>>());
        }
        std::shared_ptr<Port> dp =
            std::make_shared<Port>(Port(portResources[i]));
        this->ports.at(coordinate).emplace(direction, dp);
      }
    }
  }
}

size_t Board::getBoardSize(void) const { return boardSize; }

Building Board::getBuilding(Coordinate2D c, Direction d) const {
  const auto &map = buildings.find(c);
  if (map == buildings.end() || map->second.find(d) == map->second.end()) {
    throw NoSuchStructureException("Error: No Building at given location");
  }
  return *(map->second.at(d));
}

Road Board::getRoad(Coordinate2D c, Direction d) const {
  const auto &map = roads.find(c);
  if (map == roads.end() || map->second.find(d) == map->second.end()) {
    throw NoSuchStructureException("Error: No Building at given location");
  }
  return *(map->second.at(d));
}

Coordinate2D Board::getRobberLocation(void) const { return robberLocation; }

std::map<int, std::array<size_t, 5>>
Board::getResourceDistribution(int numberRolled) const {
  std::map<int, std::array<size_t, 5>> playerDistribution;
  for (auto &cell : this->numbers.at(numberRolled)) {
    if (this->buildings.find(cell->getCoordinate()) == this->buildings.end()) {
      continue;
    }
    for (auto &[direction, building] :
         this->buildings.at(cell->getCoordinate())) {
      if (cell->getCoordinate() == robberLocation) {
        continue;
      }
      int pid = building->getPlayerID();
      if (playerDistribution.find(pid) == playerDistribution.end()) {
        std::array<size_t, 5> resources{0, 0, 0, 0, 0};
        playerDistribution.emplace(pid, resources);
      }
      playerDistribution.at(pid)[static_cast<int>(cell->getResource())] +=
          building->getWorth();
    }
  }
  return playerDistribution;
}

bool Board::hasBuilding(const Coordinate2D c, const Direction d) const {
  const auto &map = buildings.find(c);
  if (map == buildings.end()) {
    return false;
  }
  return map->second.find(d) != map->second.end();
}

bool Board::hasStructure(const Coordinate2D c, const Direction d,
                         StructureType st) const {
  switch (st) {
  case StructureType::VILLAGE:
  case StructureType::CITY: {
    const auto &map = buildings.find(c);
    if (map == buildings.end()) {
      return false;
    }
    const auto &building = map->second.find(d);
    if (building == map->second.end()) {
      return false;
    }
    return building->second->getStructureType() == st;
  }
  case StructureType::ROAD: {
    const auto &map = roads.find(c);
    if (map == roads.end()) {
      return false;
    }
    return map->second.find(d) != map->second.end();
  }
  case StructureType::PORT: {
    const auto &map = ports.find(c);
    if (map == ports.end()) {
      return false;
    }
    return map->second.find(d) != map->second.end();
  }
  default: {
    throw InvalidTypeException("Error: Invalid StructureType");
  }
  }
}

bool Board::hasTile(const Coordinate2D c) const {
  return cells.find(c) != cells.end();
}

void Board::buildStructure(std::shared_ptr<Structure> ds, Coordinate2D c,
                           Direction d) {
  switch (ds->getStructureType()) {
  case (StructureType::VILLAGE): {
    if(this->hasStructure(c, d, StructureType::VILLAGE)){
      throw SameStructureException("Error: Cannot build on existing structure");
    }
    std::shared_ptr<Building> db = std::dynamic_pointer_cast<Building>(ds);
    // Check for proximity
    for(auto [coordinate, direction] :
         getAllVertexRepresentations({c, d})) {
      if (this->cells.find(coordinate) == this->cells.end()) {
        // If cell is outside map (e.g. the cell is on the edge of the map)
        continue;
      }
      if(buildings.find(coordinate) != buildings.end()){
        const auto cwDir = AxialHexDirection::vertexDirections[((AxialHexDirection::getVertexIndex(direction)+1)%7)];
        const auto ccwDir = AxialHexDirection::vertexDirections[((AxialHexDirection::getVertexIndex(direction)-1+7)%7)];
        if(hasBuilding(coordinate, cwDir) || hasBuilding(coordinate, ccwDir)){
          throw AdjacentBuildingException("Error: Building too close to another building");
        }
      }
    }
    for (auto [coordinate, direction] :
         getAllVertexRepresentations({c, d})) {
      if (this->cells.find(coordinate) == this->cells.end()) {
        // If cell is outside map (e.g. the cell is on the edge of the map)
        continue;
      }
      if (buildings.find(coordinate) == buildings.end()) {
        buildings.emplace(coordinate,
                          std::map<Direction, std::shared_ptr<Building>>());
      }
      buildings.at(coordinate)
          .emplace(std::make_pair(direction,
                                  std::dynamic_pointer_cast<Building>(ds)));
    }
    break;
  }
  case (StructureType::ROAD): {
    if(this->hasStructure(c, d, StructureType::ROAD)){
      throw SameStructureException("Error: Cannot build on existing structure");
    }
    for (auto [coordinate, direction] :
         getAllEdgeRepresentations({c, d})) {
      if (this->cells.find(coordinate) == this->cells.end()) {
        continue;
      }
      if (roads.find(coordinate) == roads.end()) {
        roads.emplace(coordinate, std::map<Direction, std::shared_ptr<Road>>());
      }
      roads.at(coordinate)
          .emplace(
              std::make_pair(direction, std::dynamic_pointer_cast<Road>(ds)));
    }
    break;
  }
  default:
    throw InvalidTypeException("Error: Invalid type. Must be a village or a road. City must be upgraded from upgradeToCity function");
  }
}

void Board::upgradeToCity(Coordinate2D c, Direction d) {
  if (!this->hasStructure(c, d, StructureType::VILLAGE)) {
    throw NoVillageException("Error: Must build city on village");
  }
  buildings.at(c).at(d)->upgradeToCity();
}

void Board::moveRobber(Coordinate2D nl) { robberLocation = nl; }

std::ostream &operator<<(std::ostream &os, Board const &db) {
  for (const auto &[coordinate, cell] : db.cells) {
    os << coordinate << ": " << *cell << "\n";
  }
  for(const auto &[coordinate, map] : db.buildings){
    for(const auto &[direction, building] : map){
      os << "Building " << coordinate << "-" << direction << ": " << *building << "\n";
    }
  }
  for(const auto &[coordinate, map] : db.roads){
    for(const auto &[direction, road] : map){
      os << "Road " << coordinate << "-" << direction << ": " << *road << "\n";
    }
  }
  for(const auto &[coordinate, map] : db.ports){
    for(const auto &[direction, port] : map){
      os << "Port " << coordinate << "-" << direction << ": " << *port << "\n";
    }
  }
  return os;
}
} // namespace Dogan