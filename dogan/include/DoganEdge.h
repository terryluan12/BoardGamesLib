#pragma once

#include "Coordinate.h"
#include "direction.enum.h"
#include "DoganCell.h"
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