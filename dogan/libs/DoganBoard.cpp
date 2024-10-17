#include "DoganBoard.h"
#include "enums.h"
#include <memory>
#include <sstream>

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
    this->cells[c] = std::make_shared<DoganCell>(
        DoganCell(false, c, numbers[i], resources[i]));
    ++i;
  }
  cells[config.getRobberLocation()]->setRobber(true);
}

void DoganBoard::buildStructure(Coordinate2D c, Direction d, int pid,
                                StructureType st) {
  auto it = cells.find(c);
  if (it == cells.end()) {
    throw std::invalid_argument("Error: Invalid Coordinate");
  }
  if (st == StructureType::ROAD) {
    
    DoganRoad dr = DoganRoad(pid);
    DoganEdge de = DoganEdge(d, c);
    if (this->roads.find(c) != this->roads.end()) {
      throw std::invalid_argument("Error: Road already exists");
    }
    dr.addEdge(de);
    DoganEdge corrEdge = de.getCorrespondingEdge();
    if(this->cells.find(corrEdge.getCoordinate()) != this->cells.end()) {
      dr.addEdge(de.getCorrespondingEdge());
    }

    this->roads[c] = dr;
  } else if (st == StructureType::VILLAGE) {
    DoganBuilding db = DoganBuilding<StructureType::VILLAGE>(pid);
    DoganVertex dv = DoganVertex(d, c);
    db.addVertex(dv);
    this->villages[c] = db;
  } else {
    DoganBuilding db = DoganBuilding<StructureType::CITY>(pid);
    DoganVertex dv = DoganVertex(d, c);
    db.addVertex(dv);
    this->cities[c] = db;
  }
}

Coordinate2D DoganBoard::getRobberLocation(void) const {
  return robberLocation;
}

size_t DoganBoard::getBoardSize(void) const { return boardSize; }

const std::vector<DoganPort> DoganBoard::getPorts(void) const { return ports; }

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
    os << *(c.second);
  }
  size_t i = 1;
  for (auto &pl : db.getPorts()) {
    os << pl;
    ++i;
  }
  return os;
}