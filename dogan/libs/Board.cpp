#include "Board.h"
#include "AxialDirection.h"
#include "Edge.h"
#include "Vertex.h"
#include "enums.h"
#include <iostream>
#include <memory>

namespace Dogan {
Board::Board(Config config) {

  this->robberLocation = config.getRobberLocation();
  std::vector<pip> numberOrder = config.getNumbers();
  std::vector<ResourceType> resources = config.getResources();
  auto portPrimitives = config.getPortLocations();
  std::vector<std::shared_ptr<Port>> ports;

  std::vector<ResourceType> portConfiguration = config.getPortResources();
  auto portLocations = config.getPortLocations();

  size_t i = 0;
  for (const auto &portLocation : portLocations) {
    std::set<Vertex> docks;
    for (const auto &[coordinate, direction] : portLocation) {
      docks.emplace(coordinate, direction);
    }
    ports.push_back(std::make_shared<Port>(portConfiguration[i], docks));
    ++i;
  }
  
  i = 0;
  // create all tiles
  for (const auto &c : config.getTileLocations()) {
    if (this->hasTile(c)) {
      throw std::invalid_argument("Error: Cell already exists");
    }
    std::shared_ptr<Cell> dc =
        std::make_shared<Cell>(*this, false, c, numberOrder[i], resources[i]);
    this->tiles.insert(std::make_pair(c, dc));
    if (numbers.find(numberOrder[i]) == numbers.end()) {
      this->numbers.emplace(numberOrder[i],
                            std::vector<std::shared_ptr<Cell>>{});
    }
    this->numbers.at(numberOrder[i]).emplace_back(dc);
    ++i;
  }

  // Add all Ports
  for (const auto &port : ports) {
    for (const auto &dock : port->getLocations()) {
      for (const auto &portRep : dock.getAllRepresentations()) {
        auto coordinate = portRep.getCoordinate();
        auto direction = portRep.getDirection();
        if (hasTile(coordinate)) {
          this->getTile(coordinate)->addPort(direction, port);
        }
      }
    }
  }
}

std::shared_ptr<Building> Board::getBuilding(Coordinate2D c,
                                             Direction d) const {
  checkCoordinateValid(c);
  if (!tiles.at(c)->hasBuilding(d)) {
    throw NoSuchStructureException("Error: No Building at given location");
  }
  return tiles.at(c)->getBuilding(d);
}

std::shared_ptr<Road> Board::getRoad(Coordinate2D c, Direction d) const {
  checkCoordinateValid(c);
  if (!tiles.at(c)->hasStructure(d, StructureType::ROAD)) {
    throw NoSuchStructureException("Error: No Building at given location");
  }
  return tiles.at(c)->getRoad(d);
}

std::shared_ptr<Cell> &Board::getTile(Coordinate2D c) { return tiles.at(c); }

Coordinate2D Board::getRobberLocation(void) const { return robberLocation; }

std::map<int, std::array<size_t, 5>>
Board::getResourceDistribution(int numberRolled) const {
  std::map<int, std::array<size_t, 5>> playerDistribution;
  for (auto &cell : this->numbers.at(numberRolled)) {
    if (cell->getCoordinate() == robberLocation) {
      continue;
    }
    for (auto building : cell->getBuildings()) {
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
  checkCoordinateValid(c);
  return tiles.at(c)->hasBuilding(d);
}

bool Board::hasStructure(const Coordinate2D c, const Direction d,
                         StructureType st) const {
  if (!hasTile(c)) {
    return false;
  }
  return tiles.at(c)->hasStructure(d, st);
}

bool Board::hasTile(const Coordinate2D c) const { return tiles.contains(c); }

void Board::buildStructure(int pid, std::shared_ptr<Structure> ds,
                           bool mustBeAdjacent) {
  if (ds->getStructureType() == StructureType::ROAD) {
    for (const auto &location : std::static_pointer_cast<Road>(ds)
                                    ->getLocation()
                                    .getAllRepresentations()) {
      if (!hasTile(location.getCoordinate())) {
        continue;
      }
      tiles.at(location.getCoordinate())
          ->buildStructure(pid, location.getDirection(), ds, mustBeAdjacent);
    }
  } else {
    for (const auto &location : std::static_pointer_cast<Building>(ds)
                                    ->getLocation()
                                    .getAllRepresentations()) {
      if (!hasTile(location.getCoordinate())) {
        continue;
      }
      tiles.at(location.getCoordinate())
          ->buildStructure(pid, location.getDirection(), ds, mustBeAdjacent);
    }
  }
}

void Board::upgradeToCity(int pid, Coordinate2D c, Direction d) {
  checkCoordinateValid(c);
  tiles.at(c)->upgradeToCity(pid, d);
}

void Board::moveRobber(Coordinate2D nl) { robberLocation = nl; }

void Board::checkCoordinateValid(Coordinate2D coord) const {
  if (!hasTile(coord))
    throw CoordinateNotFoundException("Error: Invalid Coordinate");
}

std::ostream &operator<<(std::ostream &os, Board const &db) {
  for (const auto &[coordinate, cell] : db.tiles) {
    os << coordinate << ": " << *cell << "\n";
  }
  return os;
}
Board &Board::operator=(const Board &B) {
  if (this != &B) {
    this->robberLocation = B.robberLocation;
    this->numbers = B.numbers;
    this->tiles = B.tiles;

    for (const auto &[key, cell] : B.tiles) {
      cell->setBoard(*this);
    }
  }
  return *this;
}

} // namespace Dogan