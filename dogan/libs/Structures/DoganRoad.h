#pragma once

#include "DoganEdge.h"
#include "DoganExceptions.h"
#include "DoganStructure.h"
#include <vector>

class DoganRoad : public DoganStructure {
public:
  DoganRoad(int pid, StructureType t, Coordinate2D c, Direction d);

private:
  void addCorrespondingEdge(void);
};