#pragma once

#include <initializer_list>
#include <optional>
#include <map>
#include <variant>
#include "Coordinate.h"
#include "DoganCell.h"
#include "enums.h"

class DoganVertex {
    public:
        DoganVertex(Direction d, std::shared_ptr<DoganCell> dc);
        DoganVertex(std::initializer_list<std::variant<Direction, Coordinate2D>> parameters);
        std::vector<DoganVertex> getCorrespondingVertices(void);
        Direction getDirection(void);
        std::shared_ptr<DoganCell> getDoganCell(void); 
        void ready(std::map<Coordinate2D, std::shared_ptr<DoganCell>> cells);
    private:
        Direction direction;
        std::shared_ptr<DoganCell> doganCell;
        Coordinate2D coordinate;
        bool isReady;

};