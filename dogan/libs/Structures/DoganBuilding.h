#pragma once

#include "Coordinate.h"
#include "DoganStructure.h"
#include "DoganExceptions.h"
#include "DoganVertex.h"
#include <vector>

class DoganBuilding : public DoganStructure {
public:
  DoganBuilding(int pid, StructureType t, Coordinate2D c, Direction d);

private:
  std::vector<DoganVertex> graphElements;
  void addCorrespondingVertices(void);
};
