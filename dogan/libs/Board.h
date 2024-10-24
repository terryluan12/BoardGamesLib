#pragma once

#include "Bank.h"
#include "Building.h"
#include "Cell.h"
#include "Config.h"
#include "Coordinate.h"
#include "Port.h"
#include "Road.h"
#include <memory>
#include <random>

namespace Dogan {
class Board {
public:
  Board(Config config);

  // Getters
  size_t getBoardSize(void) const;
  std::shared_ptr<Building> getBuilding(Coordinate2D c, Direction d) const;
  std::shared_ptr<Road> getRoad(Coordinate2D c, Direction d) const;
  const std::vector<Port> getPorts(void) const;
  Coordinate2D getRobberLocation(void) const;
  std::map<int, std::array<size_t, 5>>
  getResourceDistribution(int numberRolled) const;

  // Hassers
  bool hasBuilding(const Coordinate2D c, const Direction d) const;
  bool hasStructure(const Coordinate2D c, const Direction d,
                    StructureType st) const;
  bool hasTile(const Coordinate2D c) const;

  // Game moves
  void buildStructure(int pid, std::shared_ptr<Structure> ds,
                      Coordinate2D coord, Direction dir, bool mustBeAdjacent);
  void upgradeToCity(int pid, Coordinate2D c, Direction d);
  void moveRobber(Coordinate2D nl);

  friend std::ostream &operator<<(std::ostream &os, Board const &db);

private:
  size_t boardSize;
  Coordinate2D robberLocation;
  std::map<Coordinate2D, std::shared_ptr<Cell>> tiles;
  std::map<pip, std::vector<std::shared_ptr<Cell>>> numbers;
  std::mt19937 rengine;
  void checkCoordinateValid(Coordinate2D coord) const;
};
} // namespace Dogan