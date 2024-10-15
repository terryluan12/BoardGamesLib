#pragma once

#include "DoganBoard.h"
#include "DoganPlayer.h"
#include <random>

class DoganGame {
    public:
        DoganGame(void) : rengine(std::random_device{}()), die(1, 6), board(DoganBoard()){};
        void addPlayer(DoganPlayer p);
        void printBoard(void);
    private:
        std::mt19937 rengine;
        std::uniform_int_distribution<pip> die;
        DoganBoard board;
        std::vector<DoganPlayer> players;
};