#include "DoganBoard.h"
#include "enums.h"
#include <memory>

DoganBoard::DoganBoard(DoganConfig config) {
  rengine.seed(std::random_device{}());

  this->boardSize = config.getBoardSize();
  this->robberLocation = config.getRobberLocation();
  this->ports = config.getPorts(rengine);
  std::vector<pip> numberOrder = config.getNumbers(rengine);
  std::vector<ResourceType> resources = config.getResources(rengine);

  // create all tiles
  size_t i = 0;
  for (const auto &c : config.getTileLocations()) {
    if (this->hasTile(c)) {
      throw std::invalid_argument("Error: Cell already exists");
    }
    std::shared_ptr<DoganCell> dc = std::make_shared<DoganCell>(DoganCell(false, c, numberOrder[i], resources[i]));
    this->cells.insert(
        std::make_pair(c, dc));
    if(numbers.find(numberOrder[i]) == numbers.end()) {
      this->numbers.emplace(numberOrder[i], std::vector<std::shared_ptr<DoganCell>>{});
    }
    this->numbers.at(numberOrder[i]).push_back(dc);

    ++i;
  }
  cells.at(config.getRobberLocation())->setRobber(true);
}

void DoganBoard::buildStructure(std::shared_ptr<DoganStructure> ds,
                                std::array<int, 5> c) {
  DoganGraphElement dg = *ds->getGraphElements()[0];
  std::shared_ptr<DoganVertex> fdv = nullptr;
  std::shared_ptr<DoganEdge> fde = nullptr;
  switch (ds->getStructureType()) {
  case (StructureType::VILLAGE):
  case (StructureType::CITY):
    fdv = std::dynamic_pointer_cast<DoganVertex>(ds->getGraphElements()[0]);
    for (auto el : ds->getGraphElements()) {
      auto dv = std::dynamic_pointer_cast<DoganVertex>(el);
      if (this->cells.find(dv->getCoordinate()) == this->cells.end()) {
        continue;
      }
      if(buildings.find(dv->getCoordinate()) == buildings.end()) {
        auto coordinate = dv->getCoordinate();
        buildings.emplace(coordinate, std::map<Direction, std::shared_ptr<DoganBuilding>>());
      }
      buildings.at(dv->getCoordinate()).emplace( 
          std::make_pair(dv->getDirection(), std::dynamic_pointer_cast<DoganBuilding>(ds)));
    }

    break;
  case (StructureType::ROAD):
    fde = std::dynamic_pointer_cast<DoganEdge>(ds->getGraphElements()[0]);

    for (auto el : ds->getGraphElements()) {
      auto de = std::dynamic_pointer_cast<DoganEdge>(el);
      if (this->cells.find(de->getCoordinate()) == this->cells.end()) {
        continue;
      }
      if(roads.find(de->getCoordinate()) == roads.end()) {
        roads.emplace(de->getCoordinate(), std::map<Direction, std::shared_ptr<DoganRoad>>());
      }
      roads.at(de->getCoordinate()).emplace(
          std::make_pair(de->getDirection(), std::dynamic_pointer_cast<DoganRoad>(ds)));
    }
    break;
  }
}

size_t DoganBoard::getBoardSize(void) const { return boardSize; }

const std::vector<DoganPort> DoganBoard::getPorts(void) const { return ports; }

Coordinate2D DoganBoard::getRobberLocation(void) const {
  return robberLocation;
}

DoganBuilding DoganBoard::getBuilding(Coordinate2D c, Direction d) const {
  DoganVertex dv(c, d);
  const auto &map = buildings.find(c); 
  if(map == buildings.end() || map->second.find(d) == map->second.end()) {
    throw NoSuchStructureException("Error: No Building at given location");
  }
  return *(map->second.at(d));
}


void DoganBoard::moveRobber(Coordinate2D nl) {
  cells.at(robberLocation)->setRobber(false);
  cells.at(nl)->setRobber(true);
  robberLocation = nl;
}

bool DoganBoard::hasStructure(const Coordinate2D c, const Direction d, StructureType st) const {
  if(st == StructureType::ROAD) {
    DoganEdge de(c, d);
    const auto &map = roads.find(c);
    if(map == roads.end()) {
      return false;
    }
    return map->second.find(d) != map->second.end();
    
  }
  else {
    DoganVertex dv(c, d);
    const auto &map = buildings.find(c); 
    if(map == buildings.end()) {
      return false;
    }
    const auto &building = map->second.find(d);
    if(building == map->second.end()) {
      return false;
    }
    return building->second->getStructureType() == st;
  }
}


bool DoganBoard::hasBuilding(const Coordinate2D c, const Direction d) const {
  DoganVertex dv(c, d);
  const auto &map = buildings.find(c); 
  if(map == buildings.end()) {
    return false;
  }
  return map->second.find(d) != map->second.end();
}

bool DoganBoard::hasTile(const Coordinate2D c) const {
  return cells.find(c) != cells.end();
}

void DoganBoard::setBoardSize(size_t bs) {
  if (bs > MAX_BOARD_SIZE) {
    throw std::out_of_range("Error, attempting to set Board Size to greater "
                            "than limit. Must be less than " +
                            MAX_BOARD_SIZE);
  } else {
    boardSize = bs;
  }
}

std::map<int, std::array<size_t, 5>> DoganBoard::getResourceDistribution(int numberRolled) {
  std::map<int, std::array<size_t, 5>> playerDistribution;
  for(auto& cell : this->numbers.at(numberRolled)) {
    if(this->buildings.find(cell->getCoordinate()) == this->buildings.end()) {
      continue;
    }
    for(auto &[direction, building] : this->buildings.at(cell->getCoordinate())) {
      if(cell->getCoordinate() == robberLocation) {
        continue;
      }
      int pid = building->getPlayerID();
      if(playerDistribution.find(pid) == playerDistribution.end()) {
        std::array<size_t, 5> resources{0, 0, 0, 0, 0};
        playerDistribution.emplace(pid, resources);
      }
      playerDistribution.at(pid)[static_cast<int>(cell->getResource())] += building->getWorth();
    }
  }
  return playerDistribution;
}

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