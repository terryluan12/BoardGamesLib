#pragma once

#include <map>
#include <memory>
#include "Cell.h"
#include "common.h"

template <size_t N>
class Board {
    public:
        static const size_t MAX_BOARD_SIZE=N;
        virtual ~Board(void) = default;
        virtual Cell* operator [](const Coordinate i)=0;
        virtual std::string toString()=0;
    protected:
        std::map<Coordinate, std::unique_ptr<Cell>> cells;
        size_t boardSize;
};