#pragma once

#include "Coordinate.h"
#include "DoganExceptions.h"
#include "DoganStructure.h"
#include "DoganVertex.h"
#include <vector>

class DoganBuilding : public DoganStructure {
public:
  DoganBuilding(int pid, StructureType t, Coordinate2D c, Direction d);

private:
  void addCorrespondingVertices(void);
};
