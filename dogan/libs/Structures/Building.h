#pragma once

#include "Coordinate.h"
#include "DoganExceptions.h"
#include "Structure.h"
#include <vector>

namespace Dogan {
class Building : public Structure {
public:
  Building(int pid, StructureType t);
  void upgradeToCity(void);
  int getWorth(void) const;
};
} // namespace Dogan