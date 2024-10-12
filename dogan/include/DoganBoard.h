#pragma once

#include <random>
#include "Board.h"
#include "DoganConfig.h"
#include "DoganVertex.h"

class DoganBoard : public Board<100> {
    public:
        DoganBoard(DoganConfig config=DoganConfig());
        ~DoganBoard(void) {};
        Cell* operator [](const Coordinate i);
        std::string toString(void);
    private:
        std::vector<std::tuple<DoganVertex, DoganVertex>> portLocations;
        std::mt19937 rengine;

};