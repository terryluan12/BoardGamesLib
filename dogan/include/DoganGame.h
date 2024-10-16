#pragma once

#include "DoganBank.h"
#include "DoganBoard.h"
#include "DoganPlayer.h"
#include <random>

class DoganGame {
    public:
        DoganGame(DoganConfig config);
        void addPlayer(DoganPlayer p);
        void printBoard(void);
        void givePlayerDevCard(DoganPlayer p, std::array<size_t, 5> c);
        void addCity(Coordinate2D t, Direction d, DoganPlayer p, std::array<size_t, 5> c);

    private:
        DoganConfig config;
        std::mt19937 rengine;
        std::uniform_int_distribution<pip> die;
        DoganBank bank;
        DoganBoard board;
        std::vector<DoganPlayer> players;
};