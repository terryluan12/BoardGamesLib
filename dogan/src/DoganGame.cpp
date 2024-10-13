#include "DoganGame.h"
#include <iostream>


void DoganGame::printBoard(void) {
    std::cout << this->board.toString();
}