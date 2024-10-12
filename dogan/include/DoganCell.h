#pragma once

#include "Cell.h"
#include "enums.h"

class DoganCell : public Cell {
    public:
        DoganCell(bool cr, Resource t, int n) 
            : containsRobber(cr), number(n), type(t) {}
        Resource getType() { return this->type;}
        int getNumber() { return this->number;}
        bool hasRobber() { return this->containsRobber;}
        void setRobber(bool robber);
        std::string toString(void);
    private:
        bool containsRobber;
        int number;
        Resource type;
};