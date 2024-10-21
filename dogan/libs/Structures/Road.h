#pragma once

#include "Structure.h"
#include <vector>

namespace Dogan {
class Road : public Structure {
public:
  Road(int pid) : Structure(StructureType::ROAD) { playerID = pid; };
  friend std::ostream &operator<<(std::ostream &os, Road const &dp) {
    os << dp.structureType << "\n";
    return os;
  };
};
} // namespace Dogan