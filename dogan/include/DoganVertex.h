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
        DoganVertex(std::shared_ptr<DoganCell> dc, Direction d);
        DoganVertex(Direction d, Coordinate2D c) : direction(d), coordinate(c), isReady(false) {};
        std::vector<DoganVertex> getCorrespondingVertices(void);
        Direction getDirection(void);
        std::shared_ptr<DoganCell> getDoganCell(void); 
        void ready(std::map<Coordinate2D, std::shared_ptr<DoganCell>> cells);
    private:
        std::shared_ptr<DoganCell> doganCell;
        Direction direction;
        Coordinate2D coordinate;
        bool isReady;

};