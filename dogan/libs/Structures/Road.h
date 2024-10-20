#pragma once

#include "Structure.h"
#include <vector>

namespace Dogan {
class Road : public Structure {
public:
  Road(int pid) : Structure(StructureType::ROAD) { playerID = pid; };
};
} // namespace Dogan