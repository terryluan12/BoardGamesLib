#include "DoganGame.h"

int main(int argc, char* argv[]) {
    DoganGame *game = new DoganGame();
    DoganPlayer *player = new DoganPlayer("Dogan");
    game->addPlayer(*player);
    game->printBoard();
}