#pragma once

#include "BoardInterface.h"
#include "Coordinate.h"
#include "DoganBank.h"
#include "DoganCell.h"
#include "DoganConfig.h"
#include "DoganPlayer.h"
#include "DoganPort.h"
#include "DoganRoad.h"
#include "DoganVertex.h"
#include <random>

class DoganBoard : public BoardInterface<100> {
    public:
        DoganBoard(DoganConfig config);
        ~DoganBoard(void) {};
        DoganCell &operator [](const Coordinate2D i) override;
        const DoganBank getBank(void) const;
        const std::map<Coordinate2D, std::shared_ptr<DoganCell>> getBoard(void) const;
        const std::vector<DoganPort> getPorts(void) const;
        size_t getBoardSize(void) const override;
        void setBoardSize(size_t bs) override;
        Coordinate2D getRobberLocation(void) const;
        bool hasTile(const Coordinate2D c) const;
    private:
        size_t boardSize;
        Coordinate2D robberLocation;
        std::map<Coordinate2D, std::shared_ptr<DoganCell>> cells;
        std::vector<DoganPort> ports;
        std::mt19937 rengine;
};

std::ostream &operator<< (std::ostream &os, DoganBoard const &db);