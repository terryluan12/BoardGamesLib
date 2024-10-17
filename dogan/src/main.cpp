#include "DoganConfigBuilder.h"
#include "DoganGame.h"

int main(int argc, char *argv[]) {
  DoganConfig config = DoganConfigBuilder().build();
  DoganGame *game = new DoganGame(config);
  game->addPlayer("Dogan", 0);
  game->printBoard();
}