#pragma once

#include <unordered_map>
#include <memory>
#include <vector>
#include "Cell.h"
#include "enums.h"


class DoganCell : public Cell {
    public:
        DoganCell(bool cr, Resource t, int n) 
            : containsRobber(cr), number(n), type(t) {}
        void addAdjacentCell(const Direction d, std::shared_ptr<DoganCell> ac);
        std::shared_ptr<DoganCell> getAdjacentCell(Direction d);
        Resource getType() { return this->type;}
        int getNumber() { return this->number;}
        bool hasRobber() { return this->containsRobber;}
        void setRobber(bool robber);
        std::string toString(void);
    private:
        std::vector<std::shared_ptr<class DoganBuilding>> buildings;
        std::vector<std::shared_ptr<class DoganRoad>> roads;
        std::unordered_map<Direction, std::shared_ptr<DoganCell>> adjacentCells;
        bool containsRobber;
        int number;
        Resource type;
};