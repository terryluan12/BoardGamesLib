#include "DoganConfigBuilder.h"
#include "DoganGame.h"
#include <iostream>

int main(int argc, char *argv[]) {
  DoganConfig config = DoganConfigBuilder().build();
  DoganGame game = DoganGame(config);
  game.addPlayer("Dogan", 0);

  for (int i = 0; i < 4; i++) {
    // game.buildStructure(0 (PlayerID i), 0 (int StructureType), {0, 0, 0, 0,
    // 0} (array Resources1)) game.giveResources(0 (PlayerID i), Coordinate(0,
    // 0), HexagonalDirection::NORTHWEST) game.buildStructure(0 (PlayerID i), 2
    // (int StructureType), {0, 0, 0, 0, 0} (array Resources1))
  }
  while (true) {
    // Roll Dice - game.RollDice()
    // Get input - enum::Action action; std::string input; cin >> action >>
    // input; Based on action:
    //   Trade Cards - game.tradeResources(0 (playerID 1), input[1] (array
    //   Resources 1), input[0] (playerID 2), input[1] (array Resources 2))
    //   Build Structure - game.buildStructure(0 (PlayerID 1), input[0] (int
    //   StructureType), input[1] (array Resources1))
  }
  std::cout << game;
}