#pragma once

#include "BoardInterface.h"
#include "Coordinate.h"
#include "DoganBank.h"
#include "DoganCell.h"
#include "DoganBuilding.h"
#include "DoganConfig.h"
#include "DoganPort.h"
#include "DoganRoad.h"
#include <memory>
#include <random>

class DoganBoard : public BoardInterface<100> {
public:
  DoganBoard(DoganConfig config);
  ~DoganBoard(void){};
  void buildStructure(std::shared_ptr<DoganStructure> ds, std::array<size_t, 5> c);
  size_t getBoardSize(void) const override;
  const std::vector<DoganPort> getPorts(void) const;
  Coordinate2D getRobberLocation(void) const;
  bool hasTile(const Coordinate2D c) const;
  void setBoardSize(size_t bs) override;
  friend std::ostream &operator<<(std::ostream &os, DoganBoard const &db);

private:
  size_t boardSize;
  Coordinate2D robberLocation;
  std::map<Coordinate2D, DoganCell> cells;
  std::map<DoganVertex, std::shared_ptr<DoganBuilding>> buildings;
  std::map<DoganEdge, std::shared_ptr<DoganRoad>> roads;
  std::vector<DoganPort> ports;
  std::mt19937 rengine;
};