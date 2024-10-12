#pragma once

#include <memory>

class Cell {
    public:
        virtual ~Cell() = default;
        virtual std::string toString(void)=0;
    protected:
        const static int SIDES;
        std::shared_ptr<Cell> adjacentCells;
};