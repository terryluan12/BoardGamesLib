#include "DoganConfigBuilder.h"
#include "DoganGame.h"

int main(int argc, char *argv[]) {
  DoganConfig config = DoganConfigBuilder().build();
  DoganGame *game = new DoganGame(config);
  DoganPlayer *player = new DoganPlayer("Dogan", 0);
  game->addPlayer(*player);
  game->printBoard();
}