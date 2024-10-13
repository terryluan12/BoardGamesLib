#pragma once

#include <map>
#include <memory>
#include "CellInterface.h"
#include "common.h"
#include "Coordinate.h"

template <size_t N>
class BoardInterface {
    public:
        static const size_t MAX_BOARD_SIZE=N;
        virtual ~BoardInterface(void) = default;
        virtual CellInterface &operator [](const Coordinate<2> i)=0;
        virtual size_t getBoardSize(void) const=0;
        virtual void setBoardSize(size_t bs)=0;
        virtual std::string toString() const=0;
};