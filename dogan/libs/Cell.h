#pragma once

#include "Building.h"
#include "Coordinate.h"
#include "Node.h"
#include "Port.h"
#include "Road.h"
#include "Structure.h"
#include "enums.h"
#include <memory>
#include <unordered_map>
#include <vector>

namespace Dogan {
class Cell {
public:
  Cell(bool cr, Coordinate2D c, int n, ResourceType t);
  Coordinate2D getCoordinate(void) const;
  ResourceType getResource(void) const;

  bool hasAdjacentBuildings(Direction d) const;
  bool hasOwnConnectedRoads(int pid, Direction d, StructureType st) const;
  void buildStructure(int pid, Direction direction,
                      std::shared_ptr<Structure> ds, bool mustBeAdjacent);
  void addAdjacentCell(Direction direction, std::shared_ptr<Cell> cell);
  bool hasStructure(Direction d, StructureType st) const;

  bool hasBuilding(Direction d) const;
  std::shared_ptr<Building> getBuilding(Direction d) const;
  std::vector<std::shared_ptr<Building>> getBuildings(void) const;

  bool hasRoad(Direction d) const;
  std::shared_ptr<Road> getRoad(Direction d) const;

  void upgradeToCity(Direction d);

  friend std::ostream &operator<<(std::ostream &os, Cell const &dc);

private:
  std::map<Direction, std::shared_ptr<Cell>> adjacentCells;
  std::unordered_map<Direction, std::shared_ptr<Building>> buildings;
  std::unordered_map<Direction, std::shared_ptr<Road>> roads;
  std::map<Direction, std::shared_ptr<Port>> ports;
  Coordinate2D coordinate;
  ResourceType type;
};
} // namespace Dogan