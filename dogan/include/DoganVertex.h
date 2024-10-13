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
        DoganVertex(std::initializer_list<std::variant<Direction, Coordinate<2>>> parameters);
        std::vector<DoganVertex> getCorrespondingVertices(void);
        Direction getDirection(void);
        std::shared_ptr<DoganCell> getDoganCell(void); 
        void ready(std::map<Coordinate<2>, std::shared_ptr<DoganCell>> cells);
    private:
        Direction direction;
        std::shared_ptr<DoganCell> doganCell;
        Coordinate<2> coordinate;
        bool isReady;

};