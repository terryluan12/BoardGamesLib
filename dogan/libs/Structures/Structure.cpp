#include "Structure.h"

namespace Dogan {
StructureType Structure::getStructureType(void) const { return type; }

void Structure::setPlayerID(int pid) { playerID = pid; }

void Structure::setStructureType(StructureType t) { type = t; }

int Structure::getPlayerID(void) const { return playerID; }
} // namespace Dogan