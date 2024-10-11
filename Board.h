#pragma once

#include <array>
#include <memory>
#include "Cell.h"

template <size_t N>
class Board {
    public:
        static const size_t BOARDSIZE=N;
        virtual ~Board(void) = default;
        virtual Cell* operator [](int i)=0; // Possibly overload [][]?
        virtual std::string toString()=0;
    protected:
        std::array<std::unique_ptr<Cell>, N> cells;
};