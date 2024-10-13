#pragma once

#include "Coordinate.h"
#include "DoganCell.h"
#include "enums.h"

class DoganVertex {
    public:
        DoganVertex(Direction d, Coordinate2D c);
        std::vector<DoganVertex> getCorrespondingVertices(class DoganCell &dc);
        Coordinate2D getCoordinate(void) const;
        Direction getDirection(void) const;
    private:
        Direction direction;
        Coordinate2D coordinate;

};