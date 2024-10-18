#pragma once

#include "BoardInterface.h"
#include "Coordinate.h"
#include "DoganBank.h"
#include "DoganBuilding.h"
#include "DoganCell.h"
#include "DoganConfig.h"
#include "DoganPort.h"
#include "DoganRoad.h"
#include <memory>
#include <random>

class DoganBoard : public BoardInterface<100> {
public:
  DoganBoard(DoganConfig config);
  ~DoganBoard(void){};
  void buildStructure(std::shared_ptr<DoganStructure> ds,
                      std::array<int, 5> c);
  size_t getBoardSize(void) const override;
  const std::vector<DoganPort> getPorts(void) const;
  Coordinate2D getRobberLocation(void) const;
  void moveRobber(Coordinate2D nl);
  bool hasTile(const Coordinate2D c) const;
  bool hasStructure(const Coordinate2D c, const Direction d, StructureType st) const;
  void setBoardSize(size_t bs) override;
  
  std::map<int, std::array<size_t, 5>> getResourceDistribution(int numberRolled);

  friend std::ostream &operator<<(std::ostream &os, DoganBoard const &db);

private:
  size_t boardSize;
  Coordinate2D robberLocation;
  std::map<Coordinate2D, std::shared_ptr<DoganCell>> cells;
  std::map<pip, std::vector<std::shared_ptr<DoganCell>>> numbers;
  std::map<Coordinate2D, std::map<Direction, std::shared_ptr<DoganBuilding>>> buildings;
  std::map<Coordinate2D, std::map<Direction, std::shared_ptr<DoganRoad>>> roads;
  std::vector<DoganPort> ports;
  std::mt19937 rengine;
};