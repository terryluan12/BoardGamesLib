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
      DoganBuilding(0, StructureType::CITY, {{0, 0}, Direction::NORTH}));
  EXPECT_THROW(
      {
        board.buildStructure(dv, {0, 0, 0, 0, 0});
      },
      NoVillageException);
}
TEST(BoardTest, UpgradeVillageSuccessTest) {
  DoganConfig config = DoganConfig();
  DoganBoard board{config};
  std::shared_ptr<DoganStructure> dv1 = std::make_shared<DoganBuilding>(
      DoganBuilding(0, StructureType::VILLAGE, {{0, 0}, Direction::NORTH}));
  std::shared_ptr<DoganStructure> dv2 = std::make_shared<DoganBuilding>(
      DoganBuilding(0, StructureType::CITY, {{0, 0}, Direction::NORTH}));
  EXPECT_NO_THROW({
    board.buildStructure(dv1, {0, 0, 0, 0, 0});
    board.buildStructure(dv2, {0, 0, 0, 0, 0});
  });
}