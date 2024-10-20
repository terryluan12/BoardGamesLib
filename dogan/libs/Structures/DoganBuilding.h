#pragma once

#include "Coordinate.h"
#include "DoganExceptions.h"
#include "DoganStructure.h"
#include <vector>

class DoganBuilding : public DoganStructure {
public:
  DoganBuilding(int pid, StructureType t);
  void upgradeToCity(void);
  int getWorth(void) const;
};
