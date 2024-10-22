#include "Board.h"
#include "ElementHelpers.h"
#include "enums.h"
#include <memory>
#include "AxialHexDirection.h"

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
    this->tiles.insert(std::make_pair(c, dc));
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
        if (hasTile(coordinate)) {
          std::shared_ptr<Port> dp =
              std::make_shared<Port>(Port(portResources[i]));
          this->tiles.at(coordinate)->addStructure(direction, StructureType::PORT, dp);
        }
      }
    }
  }
}

size_t Board::getBoardSize(void) const { return boardSize; }

std::shared_ptr<Building> Board::getBuilding(Coordinate2D c, Direction d) const {
  if (!hasTile(c) || !tiles.at(c)->hasBuilding(d)) {
    throw NoSuchStructureException("Error: No Building at given location");
  }
  return tiles.at(c)->getBuilding(d);
}

std::shared_ptr<Road> Board::getRoad(Coordinate2D c, Direction d) const {
  if (!hasTile(c) || !tiles.at(c)->hasStructure(d, StructureType::ROAD)) {
    throw NoSuchStructureException("Error: No Building at given location");
  }
  return tiles.at(c)->getRoad(d);
}

Coordinate2D Board::getRobberLocation(void) const { return robberLocation; }

std::map<int, std::array<size_t, 5>>
Board::getResourceDistribution(int numberRolled) const {
  std::map<int, std::array<size_t, 5>> playerDistribution;
  for (auto &cell : this->numbers.at(numberRolled)) {
    if (cell->getCoordinate() == robberLocation) {
      continue;
    }
    for(auto building : cell->getBuildings()){
      auto pid = building->getPlayerID();
      if (!playerDistribution.contains(pid)) {
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
  if (!hasTile(c)) {
    return false;
  }
  return tiles.at(c)->hasBuilding(d);
}

bool Board::hasStructure(const Coordinate2D c, const Direction d,
                         StructureType st) const {
  if (!hasTile(c)) {
    return false;
  }
  return tiles.at(c)->hasStructure(d, st);
}

bool Board::hasTile(const Coordinate2D c) const {
  return tiles.contains(c);
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
      if (!hasTile(coordinate)) // If cell is outside map (e.g. the cell is on the edge of the map)
        continue;
      else if(tiles.at(coordinate)->hasAdjacentBuildings(direction))
          throw AdjacentBuildingException("Error: Building too close to another building");
    }

    for (auto [coordinate, direction] :
         getAllVertexRepresentations({c, d})) {
      if (!hasTile(coordinate)){ // If cell is outside map (e.g. the cell is on the edge of the map)
        continue;
      }
      tiles.at(coordinate)->addStructure(direction, StructureType::VILLAGE, db);
    }
    break;
  }
  case (StructureType::ROAD): {
    if(this->hasStructure(c, d, StructureType::ROAD)){
      throw SameStructureException("Error: Cannot build on existing structure");
    }
    for (auto [coordinate, direction] :
         getAllEdgeRepresentations({c, d})) {
      if (!hasTile(coordinate)) {
        continue;
      }
      tiles.at(coordinate)->addStructure(direction, StructureType::ROAD,
                                          std::dynamic_pointer_cast<Road>(ds));
    }
    break;
  }
  default:
    throw InvalidTypeException("Error: Invalid type. Must be a village or a road. City must be upgraded from upgradeToCity function");
  }
}

void Board::upgradeToCity(Coordinate2D c, Direction d) {
  if(!hasTile(c)) {
    throw CoordinateNotFoundException("Error: Cell does not exist");
  }
  tiles.at(c)->upgradeToCity(d);
}

void Board::moveRobber(Coordinate2D nl) { robberLocation = nl; }

std::ostream &operator<<(std::ostream &os, Board const &db) {
  for (const auto &[coordinate, cell] : db.tiles) {
    os << coordinate << ": " << *cell << "\n";
  }
  return os;
}
} // namespace Dogan