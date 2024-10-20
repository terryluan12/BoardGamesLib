#include "DoganBoard.h"
#include "DoganEdge.h"
#include "enums.h"
#include <memory>

DoganBoard::DoganBoard(DoganConfig config) {
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
    std::shared_ptr<DoganCell> dc = std::make_shared<DoganCell>(
        DoganCell(false, c, numberOrder[i], resources[i]));
    this->cells.insert(std::make_pair(c, dc));
    if (numbers.find(numberOrder[i]) == numbers.end()) {
      this->numbers.emplace(numberOrder[i],
                            std::vector<std::shared_ptr<DoganCell>>{});
    }
    this->numbers.at(numberOrder[i]).push_back(dc);

    ++i;
  }

  // Add all Ports
  for(size_t i = 0; i < config.getPortLocations().size(); i++) {
    const auto portVertices = portLocations[i];
    for(auto pv : portVertices) {
      for(auto vr : pv.getAllRepresentations()) {
        auto vertexRep = std::dynamic_pointer_cast<DoganVertex>(vr);
        if (this->ports.find(vertexRep->getCoordinate()) == this->ports.end()) {
          this->ports.emplace(vertexRep->getCoordinate(),
                              std::map<Direction, std::shared_ptr<DoganPort>>());
        }
      std::shared_ptr<DoganPort> dp = std::make_shared<DoganPort>(DoganPort(portResources[i]));
      this->ports.at(pv.getCoordinate()).emplace(pv.getDirection(), dp);
      }
    }
  }
}

size_t DoganBoard::getBoardSize(void) const { return boardSize; }

DoganBuilding DoganBoard::getBuilding(Coordinate2D c, Direction d) const {
  DoganVertex dv(c, d);
  const auto &map = buildings.find(c);
  if (map == buildings.end() || map->second.find(d) == map->second.end()) {
    throw NoSuchStructureException("Error: No Building at given location");
  }
  return *(map->second.at(d));
}

Coordinate2D DoganBoard::getRobberLocation(void) const {
  return robberLocation;
}

std::map<int, std::array<size_t, 5>>
DoganBoard::getResourceDistribution(int numberRolled) const {
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

bool DoganBoard::hasBuilding(const Coordinate2D c, const Direction d) const {
  DoganVertex dv(c, d);
  const auto &map = buildings.find(c);
  if (map == buildings.end()) {
    return false;
  }
  return map->second.find(d) != map->second.end();
}

bool DoganBoard::hasStructure(const Coordinate2D c, const Direction d,
                              StructureType st) const {
  switch(st) {
    case StructureType::VILLAGE:
    case StructureType::CITY: {
      DoganVertex dv(c, d);
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
      DoganEdge de(c, d);
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
    default : {
      throw InvalidTypeException("Error: Invalid StructureType");
    }
  }
}

bool DoganBoard::hasTile(const Coordinate2D c) const {
  return cells.find(c) != cells.end();
}

void DoganBoard::buildStructure(std::shared_ptr<DoganStructure> ds, std::shared_ptr<DoganGraphElement> dg,
                                std::array<int, 5> c) {
  switch (ds->getStructureType()) {
  case (StructureType::CITY): {
    auto dv = std::dynamic_pointer_cast<DoganVertex>(dg);
    std::shared_ptr<DoganBuilding> db = std::dynamic_pointer_cast<DoganBuilding>(ds);
    if (!this->hasStructure(dv->getCoordinate(), dv->getDirection(),
                            StructureType::VILLAGE)) {
      throw NoVillageException("Error: Must build city on village");
    }
    for (auto el : dv->getAllRepresentations()) {
      if (this->cells.find(dv->getCoordinate()) == this->cells.end()) {
        continue;
      }
      buildings.at(dv->getCoordinate()).at(dv->getDirection())->upgradeToCity();
      break;
    }
    break;
  }
  case (StructureType::VILLAGE): {
    auto dv = std::dynamic_pointer_cast<DoganVertex>(dg);
    std::shared_ptr<DoganBuilding> db = std::dynamic_pointer_cast<DoganBuilding>(ds);
    for (auto el : dv->getAllRepresentations()) {
      auto dv = std::dynamic_pointer_cast<DoganVertex>(el);
      if (this->cells.find(dv->getCoordinate()) == this->cells.end()) {
        // If cell is outside map (e.g. the cell is on the edge of the map)
        continue;
      }
      if (buildings.find(dv->getCoordinate()) == buildings.end()) {
        auto coordinate = dv->getCoordinate();
        buildings.emplace(
            coordinate, std::map<Direction, std::shared_ptr<DoganBuilding>>());
      }
      buildings.at(dv->getCoordinate())
          .emplace(
              std::make_pair(dv->getDirection(),
                             std::dynamic_pointer_cast<DoganBuilding>(ds)));
    }

    break;
  }
  case (StructureType::ROAD):{
    auto de = std::dynamic_pointer_cast<DoganEdge>(dg);

    for (auto el : de->getAllRepresentations()) {
      auto de = std::dynamic_pointer_cast<DoganEdge>(el);
      if (this->cells.find(de->getCoordinate()) == this->cells.end()) {
        continue;
      }
      if (roads.find(de->getCoordinate()) == roads.end()) {
        roads.emplace(de->getCoordinate(),
                      std::map<Direction, std::shared_ptr<DoganRoad>>());
      }
      roads.at(de->getCoordinate())
          .emplace(std::make_pair(de->getDirection(),
                                  std::dynamic_pointer_cast<DoganRoad>(ds)));
    }
    break;
  }
    case(StructureType::PORT):
      throw InvalidTypeException("Error: Cannot build a port");
  }
}

void DoganBoard::moveRobber(Coordinate2D nl) { robberLocation = nl; }

std::ostream &operator<<(std::ostream &os, DoganBoard const &db) {
  for (const auto &c : db.cells) {
    os << c.second;
  }
  // size_t i = 1;
  // for (auto &pl : db.getPorts()) {
  //   os << pl;
  //   ++i;
  // }
  return os;
}