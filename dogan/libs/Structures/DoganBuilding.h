#pragma once

#include "Coordinate.h"
#include "DoganExceptions.h"
#include "DoganStructure.h"
#include "DoganVertex.h"
#include <vector>

class DoganBuilding : public DoganStructure {
public:
  DoganBuilding(int pid, StructureType t, DoganVertex dv);
  void upgradeToCity(void);
  int getWorth(void);

private:
  void addCorrespondingVertices(void);
};
