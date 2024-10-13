#pragma once

#include <unordered_map>
#include <memory>
#include <vector>
#include "CellInterface.h"
#include "common.h"
#include "enums.h"


class DoganCell : public CellInterface {
    public:
        DoganCell(bool cr, Coordinate c, Resource t, int n) 
            : containsRobber(cr), coordinate(c), number(n), type(t) {}
        DoganCell() {}
        void addAdjacentCell(const Direction d, std::shared_ptr<DoganCell> ac);
        std::shared_ptr<DoganCell> getAdjacentCell(Direction d);
        Coordinate getCoordinate(void) const;
        Resource getType(void) const;
        int getNumber(void) const;
        bool hasRobber(void) const;
        void setRobber(bool robber);
        std::string toString(void) const override;
        bool hasAdjacentCell(Direction d) const;
    private:
        std::vector<std::shared_ptr<class DoganBuilding>> buildings;
        std::vector<std::shared_ptr<class DoganRoad>> roads;
        std::unordered_map<Direction, std::shared_ptr<DoganCell>> adjacentCells;
        bool containsRobber;
        Coordinate coordinate;
        int number;
        Resource type;
};