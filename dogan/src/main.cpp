#include "DoganConfigBuilder.h"
#include "DoganGame.h"
#include <iostream>

int main(int argc, char *argv[]) {
  Dogan::Config config = Dogan::ConfigBuilder().build();
  Dogan::Game game = Dogan::Game(config);
  game.addPlayer(0);
  std::cout << game;
}