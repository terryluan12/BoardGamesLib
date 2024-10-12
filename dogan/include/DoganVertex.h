#pragma once

#include <initializer_list>
#include <optional>
#include <map>
#include <variant>
#include "DoganCell.h"
#include "enums.h"

class DoganVertex {
    public:
        DoganVertex(Direction d, DoganCell &dc);
        DoganVertex(std::initializer_list<std::variant<Direction, Coordinate>> parameters);
        std::vector<DoganVertex> getCorrespondingVertices(void);
        Direction getDirection(void);
        std::optional<DoganCell> getDoganCell(void); 
        void ready(std::map<Coordinate, std::shared_ptr<Cell>> cells);
    private:
        Direction direction;
        std::optional<std::reference_wrapper<DoganCell>> doganCell;
        Coordinate coordinate;
        bool isReady;

};