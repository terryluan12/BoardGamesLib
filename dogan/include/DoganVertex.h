#pragma once

#include "Coordinate.h"
#include "DoganCell.h"
#include "enums.h"

class DoganVertex {
    public:
        DoganVertex(Direction d, Coordinate2D c);
        std::vector<DoganVertex> getCorrespondingVertices(class DoganCell &dc);
        Direction getDirection(void);
    private:
        Direction direction;
        Coordinate2D coordinate;

};