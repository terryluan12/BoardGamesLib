#pragma once
#include <vector>
#include "enums.h"
#include "DoganCell.h"
class DoganEdge {
    public:
        DoganEdge(Direction d, std::shared_ptr<DoganCell> dc);
        std::vector<DoganEdge> getCorrespondingEdge(void);
        Direction getDirection(void);
        std::shared_ptr<DoganCell> getDoganCell(void); 
    private:
        Direction direction;
        std::shared_ptr<DoganCell> doganCell;

};