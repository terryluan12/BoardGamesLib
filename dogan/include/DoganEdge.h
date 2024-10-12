#pragma once
#include <vector>
#include "enums.h"
#include "DoganCell.h"
class DoganEdge {
    public:
        DoganEdge(Direction d, DoganCell &dc);
        std::vector<DoganEdge> getCorrespondingEdge(void);
        Direction getDirection(void);
        DoganCell getDoganCell(void); 
    private:
        Direction direction;
        DoganCell doganCell;

};