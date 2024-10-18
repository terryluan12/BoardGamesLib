#include "DoganBoard.h"
#include "enums.h"
#include <memory>

DoganBoard::DoganBoard(DoganConfig config) {
  rengine.seed(std::random_device{}());

  this->boardSize = config.getBoardSize();
  this->robberLocation = config.getRobberLocation();
  this->ports = config.getPorts(rengine);
  std::vector<pip> numbers = config.getNumbers(rengine);
  std::vector<ResourceType> resources = config.getResources(rengine);

  // create all tiles
  size_t i = 0;
  for (const auto &c : config.getTileLocations()) {
    if (this->cells.find(c) != this->cells.end()) {
      throw std::invalid_argument("Error: Cell already exists");
    }
    this->cells.insert(
        std::make_pair(c, DoganCell(false, c, numbers[i], resources[i])));

    ++i;
  }
  cells.at(config.getRobberLocation()).setRobber(true);
}

void DoganBoard::buildStructure(std::shared_ptr<DoganStructure> ds,
                                std::array<size_t, 5> c) {
  DoganGraphElement dg = *ds->getGraphElements()[0];
  if (this->cells.find(dg.getCoordinate()) == this->cells.end()) {
    throw CoordinateNotFoundException("Error: Invalid Coordinate");
  }
  std::shared_ptr<DoganVertex> fdv = nullptr;
  std::shared_ptr<DoganEdge> fde = nullptr;
  switch (ds->getStructureType()) {
  case (StructureType::VILLAGE):
  case (StructureType::CITY):
    fdv = std::dynamic_pointer_cast<DoganVertex>(ds->getGraphElements()[0]);
    if (this->buildings.find(*fdv) != this->buildings.end()) {
      throw SameStructureException("Error: Structure already exists");
    }

    for (auto el : ds->getGraphElements()) {
      auto dv = std::dynamic_pointer_cast<DoganVertex>(el);
      if (this->cells.find(dv->getCoordinate()) == this->cells.end()) {
        continue;
      }
      buildings.insert(
          std::make_pair(*dv, std::dynamic_pointer_cast<DoganBuilding>(ds)));
    }

    break;
  case (StructureType::ROAD):
    fde = std::dynamic_pointer_cast<DoganEdge>(ds->getGraphElements()[0]);

    if (this->roads.find(*fde) != this->roads.end()) {
      throw SameStructureException("Error: Road already exists");
    }

    for (auto el : ds->getGraphElements()) {
      auto de = std::dynamic_pointer_cast<DoganEdge>(el);
      if (this->cells.find(de->getCoordinate()) == this->cells.end()) {
        continue;
      }
      roads.insert(
          std::make_pair(*de, std::dynamic_pointer_cast<DoganRoad>(ds)));
    }
    break;
  }
}

size_t DoganBoard::getBoardSize(void) const { return boardSize; }

const std::vector<DoganPort> DoganBoard::getPorts(void) const { return ports; }

Coordinate2D DoganBoard::getRobberLocation(void) const {
  return robberLocation;
}

bool DoganBoard::hasStructure(const Coordinate2D c, const Direction d, StructureType st) const {
  if(st == StructureType::ROAD) {
    DoganEdge de(c, d);
    return roads.find(de) != roads.end();
  }
  else {
    DoganVertex dv(c, d);
    return buildings.find(dv) != buildings.end();
  }
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