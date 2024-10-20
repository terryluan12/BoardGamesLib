#include "DoganBoard.h"
#include "DoganConfig.h"
#include "DoganConfigBuilder.h"
#include "DoganExceptions.h"
#include <gtest/gtest.h>

TEST(BoardTest, AddDuplicateCellTest) {
  DoganConfigBuilder config = DoganConfigBuilder();
  config.setTileLocations({{0, 0}, {0, 0}});
  EXPECT_THROW({ DoganBoard board = DoganBoard(config.build()); },
               std::invalid_argument);
}

TEST(BoardTest, UpgradeVillageFailTest) {
  DoganConfig config = DoganConfig();
  DoganBoard board{config};
  std::shared_ptr<DoganStructure> dv = std::make_shared<DoganBuilding>(
      DoganBuilding(0, StructureType::CITY));
  auto coordinate = std::make_shared<DoganVertex>(Coordinate2D{0, 0}, Direction::NORTH);
  EXPECT_THROW(
      {
        board.buildStructure(dv, coordinate, {0, 0, 0, 0, 0});
      },
      NoVillageException);
}
TEST(BoardTest, UpgradeVillageSuccessTest) {
  DoganConfig config = DoganConfig();
  DoganBoard board{config};
  auto dv1 = std::make_shared<DoganBuilding>(
      DoganBuilding(0, StructureType::VILLAGE));
  auto dv2 = std::make_shared<DoganBuilding>(
      DoganBuilding(0, StructureType::CITY));
  auto coordinate = std::make_shared<DoganVertex>(Coordinate2D{0, 0}, Direction::NORTH);
  EXPECT_NO_THROW({
    board.buildStructure(dv1, coordinate, {0, 0, 0, 0, 0});
    board.buildStructure(dv2, coordinate, {0, 0, 0, 0, 0});
  });
}