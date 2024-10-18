#include "DoganStructure.h"

const std::size_t DoganStructure::NUM_STRUCTURE_TYPES = 3;

StructureType DoganStructure::getStructureType(void) {
    return type;
}

void DoganStructure::setPlayerID(int pid) {
    playerID = pid;
}

void DoganStructure::setStructureType(StructureType t) {
    type = t;
}

std::vector<std::shared_ptr<DoganGraphElement>> DoganStructure::getGraphElements(void) {
    return graphElements;
}

void DoganStructure::setGraphElements(std::vector<std::shared_ptr<DoganGraphElement>> ge) {
    graphElements = ge;
}

