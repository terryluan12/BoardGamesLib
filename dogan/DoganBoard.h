#pragma once

#include "DoganConfig.h"
#include "enums.h"
#include "common.h"
#include "../Board.h"

class DoganBoard : public Board<100> {
    public:
        DoganBoard(DoganConfig config=DoganConfig());
        ~DoganBoard(void) {};
        Cell* operator [](const Coordinate i); // Possibly overload [][]?
        std::string toString(void);
    private:
        std::mt19937 rengine;
        std::vector<pip> getNumberConfiguration(const std::string configValue);
        std::vector<Resource> getResourceConfiguration(const std::string configValue);

};