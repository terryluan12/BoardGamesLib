#include <iostream>
#include "DoganGame.h"


void DoganGame::printBoard(void) {
    std::cout << this->board.toString();
}