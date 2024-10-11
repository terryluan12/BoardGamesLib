#pragma once

#include "enums.h"
#include "../Board.h"

class DoganBoard : public Board<19> {
    typedef unsigned char pips;
    public:
        DoganBoard(void);
        ~DoganBoard(void) {};
        Cell *operator [](const int i); // Possibly overload [][]?
        std::string toString(void);
    private:
        std::mt19937 rengine;
        std::array<DoganBoard::pips, BOARDSIZE> getNumberConfiguration(const std::string configValue="default");
        std::array<Resource, BOARDSIZE> getResourceConfiguration(const std::string configValue="default");

};