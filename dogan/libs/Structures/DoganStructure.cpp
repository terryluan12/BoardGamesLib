#include "DoganStructure.h"

StructureType DoganStructure::getStructureType(void) const { return type; }

void DoganStructure::setPlayerID(int pid) { playerID = pid; }

void DoganStructure::setStructureType(StructureType t) { type = t; }

int DoganStructure::getPlayerID(void) const { return playerID; }
