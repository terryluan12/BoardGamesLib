#pragma once

#include <memory>
#include <random>
#include "DoganBoard.h"

class DoganGame {
    public:
        DoganGame(void) : rengine(std::random_device{}()), die(0, 6), board(DoganBoard()){};
        void printBoard(void);
    private:
        std::mt19937 rengine;
        std::uniform_int_distribution<u_int32_t> die;
        DoganBoard board;
};