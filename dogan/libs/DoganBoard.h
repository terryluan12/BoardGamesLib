#pragma once

#include "Coordinate.h"
#include "DoganBank.h"
#include "DoganBuilding.h"
#include "DoganCell.h"
#include "DoganConfig.h"
#include "DoganPort.h"
#include "DoganRoad.h"
#include <memory>
#include <random>

class DoganBoard {
public:
  DoganBoard(DoganConfig config);

  // Getters
  size_t getBoardSize(void) const;
  DoganBuilding getBuilding(Coordinate2D c, Direction d) const;
  const std::vector<DoganPort> getPorts(void) const;
  Coordinate2D getRobberLocation(void) const;
  std::map<int, std::array<size_t, 5>>
  getResourceDistribution(int numberRolled) const;

  // Hassers
  bool hasBuilding(const Coordinate2D c, const Direction d) const;
  bool hasStructure(const Coordinate2D c, const Direction d,
                    StructureType st) const;
  bool hasTile(const Coordinate2D c) const;

  // Game moves
  void buildStructure(std::shared_ptr<DoganStructure> ds, Coordinate2D coord, Direction dir, std::array<int, 5> c);
  void moveRobber(Coordinate2D nl);

  friend std::ostream &operator<<(std::ostream &os, DoganBoard const &db);

private:
  size_t boardSize;
  Coordinate2D robberLocation;
  std::map<Coordinate2D, std::shared_ptr<DoganCell>> cells;
  std::map<pip, std::vector<std::shared_ptr<DoganCell>>> numbers;
  std::map<Coordinate2D, std::map<Direction, std::shared_ptr<DoganBuilding>>>
      buildings;
  std::map<Coordinate2D, std::map<Direction, std::shared_ptr<DoganRoad>>> roads;
  std::map<Coordinate2D, std::map<Direction, std::shared_ptr<DoganPort>>> ports;
  std::mt19937 rengine;
};