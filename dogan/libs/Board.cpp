#include "Board.h"
#include "AxialHexDirection.h"
#include "enums.h"
#include <memory>

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

  // Populate adjacent cells
  for (const auto &[coords, tile] : this->tiles) {
    for (auto d : AxialHexDirection::edgeDirections) {
      if (!hasTile(coords + AxialHexDirection::toCoordinate(d))) {
        continue;
      }
      tile->addAdjacentCell(
          d, this->tiles.at(coords + AxialHexDirection::toCoordinate(d)));
    }
  }

  // Add all Ports
  for (size_t i = 0; i < config.getPortLocations().size(); i++) {
    const auto portVertices = portLocations[i];
    for (auto [coordinate, d] : portVertices) {
      for (auto [travelDirection, vertexDirection] :
           AxialHexDirection::getAllVertexRepresentations(d)) {
        Coordinate2D newCoordinate =
            coordinate + AxialHexDirection::toCoordinate(travelDirection);
        if (hasTile(newCoordinate)) {
          std::shared_ptr<Port> dp =
              std::make_shared<Port>(Port(portResources[i]));
          this->tiles.at(newCoordinate)
              ->buildStructure(-1, vertexDirection, dp, false);
        }
      }
    }
  }
}

size_t Board::getBoardSize(void) const { return boardSize; }

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
                           Coordinate2D c, Direction d, bool mustBeAdjacent) {
  std::vector<elementRepresentation> elementRepresentations;
  if (ds->getStructureType() == StructureType::VILLAGE) {
    auto allVertexRepresentations =
        AxialHexDirection::getAllVertexRepresentations(d);
    elementRepresentations.insert(elementRepresentations.end(),
                                  allVertexRepresentations.begin(),
                                  allVertexRepresentations.end());
  } else if (ds->getStructureType() == StructureType::ROAD) {
    auto allEdgeRepresentations =
        AxialHexDirection::getAllEdgeRepresentations(d);
    elementRepresentations.insert(elementRepresentations.end(),
                                  allEdgeRepresentations.begin(),
                                  allEdgeRepresentations.end());
  }
  for (auto [travelDirection, targetDirection] : elementRepresentations) {
    Coordinate2D newCoordinate =
        c + AxialHexDirection::toCoordinate(travelDirection);
    if (!hasTile(newCoordinate)) {
      continue;
    }
    tiles.at(newCoordinate)
        ->buildStructure(pid, targetDirection, ds, mustBeAdjacent);
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
} // namespace Dogan