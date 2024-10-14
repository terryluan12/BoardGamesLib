#pragma once

#include "BoardInterface.h"
#include "Coordinate.h"
#include "DoganCell.h"
#include "DoganConfig.h"
#include "DoganVertex.h"
#include <random>

class DoganBoard : public BoardInterface<100> {
    public:
        DoganBoard(DoganConfig config=DoganConfig());
        ~DoganBoard(void) {};
        DoganCell &operator [](const Coordinate2D i) override;
        std::map<Coordinate2D, std::shared_ptr<DoganCell>> getBoard(void);
        std::string toString(void) const override;
        size_t getBoardSize(void) const override;
        void setBoardSize(size_t bs) override;
        Coordinate2D getRobberPosition(void) const;
    private:
        size_t boardSize;
        Coordinate2D robberPosition;
        std::map<Coordinate2D, std::shared_ptr<DoganCell>> cells;
        std::vector<std::tuple<DoganVertex, DoganVertex>> portLocations;
        std::mt19937 rengine;

};