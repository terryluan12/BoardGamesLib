#include "DoganStructure.h"

StructureType DoganStructure::getStructureType(void) { return type; }

void DoganStructure::setPlayerID(int pid) { playerID = pid; }

void DoganStructure::setStructureType(StructureType t) { type = t; }

int DoganStructure::getPlayerID(void) { return playerID; }
