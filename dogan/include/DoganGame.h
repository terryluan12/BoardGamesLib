#pragma once

#include "DoganBoard.h"
#include <random>

class DoganGame {
    public:
        DoganGame(void) : rengine(std::random_device{}()), die(1, 6), board(DoganBoard()){};
        void printBoard(void);
    private:
        std::mt19937 rengine;
        std::uniform_int_distribution<u_int32_t> die;
        DoganBoard board;
};