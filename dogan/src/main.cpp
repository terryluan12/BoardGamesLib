#include "DoganConfigBuilder.h"
#include "DoganGame.h"
#include <iostream>

int main(int argc, char *argv[]) {
  DoganConfig config = DoganConfigBuilder().build();
  DoganGame game = DoganGame(config);
  game.addPlayer("Dogan", 0);
  std::cout << game;
}