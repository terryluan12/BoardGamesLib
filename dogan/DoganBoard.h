#pragma once

#include <random>
#include "DoganConfig.h"
#include "../Board.h"

class DoganBoard : public Board<100> {
    public:
        DoganBoard(DoganConfig config=DoganConfig());
        ~DoganBoard(void) {};
        Cell* operator [](const Coordinate i);
        std::string toString(void);
    private:
        std::mt19937 rengine;

};