#include "DoganRoad.h"
#include <cassert>

DoganRoad::DoganRoad(int pid, StructureType t, Coordinate2D c, Direction d) : DoganStructure(pid, t), graphElements{{c, d}} {
    if ( t != StructureType::ROAD) {
        throw InvalidTypeException("Error: Invalid Building Type");
    }
    addCorrespondingEdge();
}

void DoganRoad::addCorrespondingEdge(void) {
    assert((graphElements.size() == 1));

    graphElements.push_back(graphElements[0].getCorrespondingEdge());
}
