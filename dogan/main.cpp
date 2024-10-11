#include <iostream>
#include "DoganGame.h"
#include "enums.h"

int main(int argc, char* argv[]) {
    DoganGame *game = new DoganGame();
    game->printBoard();
}