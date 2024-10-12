#pragma once

#include <unordered_map>
#include <memory>
#include <vector>
#include "Cell.h"
#include "common.h"
#include "enums.h"


class DoganCell : public Cell {
    public:
        DoganCell(bool cr, Coordinate c, Resource t, int n) 
            : containsRobber(cr), coordinate(c), number(n), type(t) {}
        DoganCell(Coordinate c) : coordinate(c) {}
        void addAdjacentCell(const Direction d, std::shared_ptr<DoganCell> ac);
        std::shared_ptr<DoganCell> getAdjacentCell(Direction d);
        Coordinate getCoordinate(void);
        Resource getType();
        int getNumber();
        bool hasRobber();
        void setRobber(bool robber);
        std::string toString(void);
    private:
        std::vector<std::shared_ptr<class DoganBuilding>> buildings;
        std::vector<std::shared_ptr<class DoganRoad>> roads;
        std::unordered_map<Direction, std::shared_ptr<DoganCell>> adjacentCells;
        bool containsRobber;
        Coordinate coordinate;
        int number;
        Resource type;
};