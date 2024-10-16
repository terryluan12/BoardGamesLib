#pragma once

#include "Coordinate.h"
#include "DoganCell.h"
#include "enums.h"
#include <vector>

class DoganEdge {
    public:
        DoganEdge(Direction d, Coordinate2D c);
        std::vector<DoganEdge> getCorrespondingEdge(class DoganCell &dc);
        Direction getDirection(void);
    private:
        Direction direction;
        Coordinate2D coordinate;

};