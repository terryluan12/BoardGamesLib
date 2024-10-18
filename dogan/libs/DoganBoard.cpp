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
    if (this->cells.find(c) != this->cells.end()) {
      throw std::invalid_argument("Error: Cell already exists");
    }
    this->cells.insert(std::make_pair(c, 
        DoganCell(false, c, numbers[i], resources[i])));
        
    ++i;
  }
  cells.at(config.getRobberLocation()).setRobber(true);
}

void DoganBoard::buildStructure(std::shared_ptr<DoganStructure> ds, std::array<size_t, 5> c) {
  for(auto& el: ds->getGraphElements()) {
    if (this->cells.find(el.getCoordinate()) == this->cells.end()) {
      throw CoordinateNotFoundException("Error: Invalid Coordinate");
    }
  }

  switch(ds->getStructureType()) {
    case(StructureType::VILLAGE):
      for(auto& el: ds->getGraphElements()) {
        if (this->villages.find(el.getCoordinate()) != this->villages.end()) {
          throw std::invalid_argument("Error: Village already exists");
        }
      }
      for(auto& el: ds->getGraphElements()) {
      villages.insert(std::make_pair(el.getCoordinate(), std::dynamic_pointer_cast<DoganBuilding>(ds)));
      }
      break;
    case(StructureType::CITY):
      for(auto& el: ds->getGraphElements()) {
        if (this->cities.find(el.getCoordinate()) != this->cities.end()) {
          throw std::invalid_argument("Error: City already exists");
        }
      }
      for(auto& el: ds->getGraphElements()) {
      cities.insert(std::make_pair(el.getCoordinate(), std::dynamic_pointer_cast<DoganBuilding>(ds)));
      }
      break;
    case(StructureType::ROAD):
      for(auto& el: ds->getGraphElements()) {
        if (this->roads.find(el.getCoordinate()) != this->roads.end()) {
          throw std::invalid_argument("Error: Road already exists");
        }
      }
      for(auto& el: ds->getGraphElements()) {
      roads.insert(std::make_pair(el.getCoordinate(), std::dynamic_pointer_cast<DoganRoad>(ds)));
      }
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
    os << c.second;
  }
  // size_t i = 1;
  // for (auto &pl : db.getPorts()) {
  //   os << pl;
  //   ++i;
  // }
  return os;
}