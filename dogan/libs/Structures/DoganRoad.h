#pragma once

#include "DoganStructure.h"
#include "DoganEdge.h"
#include "DoganExceptions.h"
#include <vector>

class DoganRoad : public DoganStructure {
    public:
        DoganRoad(int pid, StructureType t, Coordinate2D c, Direction d);

    private:
        std::vector<DoganEdge> graphElements;
        void addCorrespondingEdge(void);
};