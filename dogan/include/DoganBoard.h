#pragma once

#include <random>
#include "BoardInterface.h"
#include "Coordinate.h"
#include "DoganCell.h"
#include "DoganConfig.h"
#include "DoganVertex.h"

class DoganBoard : public BoardInterface<100> {
    public:
        DoganBoard(DoganConfig config=DoganConfig());
        ~DoganBoard(void) {};
        DoganCell &operator [](const Cell2D i) override;
        std::map<Cell2D, std::shared_ptr<DoganCell>> getBoard(void);
        std::string toString(void) const override;
        size_t getBoardSize(void) const override;
        void setBoardSize(size_t bs) override;
    private:
        size_t boardSize;
        std::map<Cell2D, std::shared_ptr<DoganCell>> cells;
        std::vector<std::tuple<DoganVertex, DoganVertex>> portLocations;
        std::mt19937 rengine;

};