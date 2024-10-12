#pragma once

#include "../Cell.h"
#include "enums.h"

class DoganCell : public Cell {
    public:
        DoganCell(Resource t, bool hr, int n) 
            : type(t), containsRobber(hr), number(n) {}
        Resource getType() { return this->type;}
        bool hasRobber() { return this->containsRobber;}
        int getNumber() { return this->number;}
        std::string toString(void);
        void setRobber(bool robber);
    private:
        Resource type;
        bool containsRobber;
        int number;
};