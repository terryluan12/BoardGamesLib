#pragma once

#include <vector>
#include "Coordinate.h"
#include "enums.h"
#include "DoganCell.h"

class DoganEdge {
    public:
        DoganEdge(Direction d, Coordinate2D c);
        std::vector<DoganEdge> getCorrespondingEdge(class DoganCell &dc);
        Direction getDirection(void);
    private:
        Direction direction;
        Coordinate2D coordinate;

};