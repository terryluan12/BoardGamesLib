#pragma once

class Cell {
    public:
        virtual ~Cell() = default;
        virtual std::string toString(void)=0;
    protected:
        const static int SIDES;
        Cell *adjacentCells;
};