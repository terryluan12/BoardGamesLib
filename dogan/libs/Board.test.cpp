#include "Board.h"
#include "Config.h"
#include "DoganConfigBuilder.h"
#include "DoganExceptions.h"
#include <gtest/gtest.h>

using namespace Dogan;
TEST(BoardTest, AddDuplicateCellTest) {
  ConfigBuilder config = ConfigBuilder();
  config.setTileLocations({{0, 0}, {0, 0}});
  EXPECT_THROW({ Board board = Board(config.build()); }, std::invalid_argument);
}

TEST(BoardTest, UpgradeVillageFailTest) {
  Config config = Config();
  Board board{config};
  std::shared_ptr<Structure> dv =
      std::make_shared<Building>(Building(0, StructureType::CITY));
  EXPECT_THROW(
      {
        board.buildStructure(dv, {0, 0}, Direction::NORTH, {0, 0, 0, 0, 0});
      },
      NoVillageException);
}
TEST(BoardTest, UpgradeVillageSuccessTest) {
  Config config = Config();
  Board board{config};
  auto dv1 = std::make_shared<Building>(Building(0, StructureType::VILLAGE));
  auto dv2 = std::make_shared<Building>(Building(0, StructureType::CITY));
  EXPECT_NO_THROW({
    board.buildStructure(dv1, Coordinate2D{0, 0}, Direction::NORTH,
                         {0, 0, 0, 0, 0});
    board.buildStructure(dv2, Coordinate2D{0, 0}, Direction::NORTH,
                         {0, 0, 0, 0, 0});
  });
}