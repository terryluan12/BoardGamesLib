#pragma once

#include "DoganStructure.h"
#include <vector>

class DoganRoad : public DoganStructure {
public:
  DoganRoad(int pid) : DoganStructure(StructureType::ROAD) { playerID = pid; };
};