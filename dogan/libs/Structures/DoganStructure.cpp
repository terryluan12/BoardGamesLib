#include "DoganStructure.h"

const std::size_t DoganStructure::NUM_STRUCTURE_TYPES = 3;

StructureType DoganStructure::getStructureType(void) {
    return type;
}
std::vector<DoganGraphElement> DoganStructure::getGraphElements(void) {
    return graphElements;
}

void DoganStructure::setPlayerID(int pid) { playerID = pid; }

void DoganStructure::setStructureType(StructureType t) {
    type = t;
}