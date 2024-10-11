#include <random>
#include <iostream>
#include "DoganBoard.h"
#include "DoganGame.h"
#include "DoganCell.h"


void DoganGame::printBoard(void) {
    std::cout << this->board.toString();
}