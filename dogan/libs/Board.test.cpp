#include "Board.h"
#include "Config.h"
#include "DoganConfigBuilder.h"
#include "DoganExceptions.h"
#include <gtest/gtest.h>
#include <utility>

using namespace Dogan;

class BoardFixture : public ::testing::Test {
protected:
  void SetUp() override {}
  Board board{Config()};
};

TEST(BoardTest, AddDuplicateCellTest) {
  ConfigBuilder config = ConfigBuilder();
  config.setTileLocations({{0, 0}, {0, 0}});
  EXPECT_THROW({ Board board = Board(config.build()); }, std::invalid_argument);
}

TEST_F(BoardFixture, BuildNonAdjacentStructuresTest) {
  auto villageNormal = std::make_shared<Building>(0, StructureType::VILLAGE);
  auto roadNormal = std::make_shared<Road>(0);

  // Villages
  board.buildStructure(0, villageNormal, {1, 1}, Direction::NORTHWEST, false);
  EXPECT_EQ((board.hasStructure({1, 1}, Direction::NORTHWEST,
                                StructureType::VILLAGE)),
            true);
  EXPECT_EQ(
      (board.hasStructure({1, 0}, Direction::SOUTH, StructureType::VILLAGE)),
      true);
  EXPECT_EQ((board.hasStructure({0, 1}, Direction::NORTHEAST,
                                StructureType::VILLAGE)),
            true);

  // Cities
  board.upgradeToCity(0, {1, 0}, Direction::SOUTH);
  EXPECT_EQ(
      (board.hasStructure({1, 1}, Direction::NORTHWEST, StructureType::CITY)),
      true);
  EXPECT_EQ((board.hasStructure({1, 0}, Direction::SOUTH, StructureType::CITY)),
            true);
  EXPECT_EQ(
      (board.hasStructure({0, 1}, Direction::NORTHEAST, StructureType::CITY)),
      true);

  // Roads
  board.buildStructure(0, roadNormal, {1, 0}, Direction::SOUTHEAST, false);
  EXPECT_EQ(
      (board.hasStructure({1, 0}, Direction::SOUTHEAST, StructureType::ROAD)),
      true);
  EXPECT_EQ(
      (board.hasStructure({1, 1}, Direction::NORTHWEST, StructureType::ROAD)),
      true);
}

TEST_F(BoardFixture, BuildNonAdjacentEdgeStructuresTest) {
  auto villageEdge = std::make_shared<Building>(0, StructureType::VILLAGE);
  auto roadEdge = std::make_shared<Road>(0);
  // Edge Villages
  board.buildStructure(0, villageEdge, {0, 0}, Direction::NORTHWEST, false);
  EXPECT_EQ((board.hasStructure({0, 0}, Direction::NORTHWEST,
                                StructureType::VILLAGE)),
            true);
  EXPECT_EQ(
      (board.hasStructure({-1, 0}, Direction::SOUTH, StructureType::VILLAGE)),
      false);

  // Edge Cities
  board.upgradeToCity(0, {0, 0}, Direction::NORTHWEST);
  EXPECT_EQ(
      (board.hasStructure({0, 0}, Direction::NORTHWEST, StructureType::CITY)),
      true);
  EXPECT_EQ(
      (board.hasStructure({-1, 0}, Direction::SOUTH, StructureType::CITY)),
      false);

  // Edge Roads
  board.buildStructure(0, roadEdge, {0, 0}, Direction::NORTHWEST, false);
  EXPECT_EQ(
      (board.hasStructure({0, 0}, Direction::NORTHWEST, StructureType::ROAD)),
      true);
  EXPECT_EQ(
      (board.hasStructure({-1, 0}, Direction::SOUTHEAST, StructureType::ROAD)),
      false);
}

// Structures
TEST_F(BoardFixture, BuildExistingStructuresTest) {
  auto village = std::make_shared<Building>(0, StructureType::VILLAGE);
  auto existingVillage = std::make_shared<Building>(0, StructureType::VILLAGE);
  auto road = std::make_shared<Road>(0);
  auto existingRoad = std::make_shared<Road>(0);

  // Buildings
  board.buildStructure(0, village, {1, 1}, Direction::NORTHWEST, false);
  EXPECT_THROW(
      {
        board.buildStructure(0, village, {1, 1}, Direction::NORTHWEST, false);
      },
      Dogan::BuildStructureException);
  EXPECT_THROW(
      {
        board.buildStructure(0, existingVillage, {1, 0}, Direction::SOUTH,
                             false);
      },
      Dogan::BuildStructureException);

  // Roads
  board.buildStructure(0, road, {1, 0}, Direction::SOUTHEAST, false);
  EXPECT_THROW(
      {
        board.buildStructure(0, road, {1, 0}, Direction::SOUTHEAST, false);
      },
      Dogan::BuildStructureException);

  EXPECT_THROW(
      {
        board.buildStructure(0, existingRoad, {1, 1}, Direction::NORTHWEST,
                             false);
      },
      Dogan::BuildStructureException);
}

TEST_F(BoardFixture, EmptyStructureTest) {

  // Buildings
  EXPECT_EQ((board.hasStructure({1, 1}, Direction::NORTHWEST,
                                StructureType::VILLAGE)),
            false);
  EXPECT_EQ((board.hasStructure({1, 0}, Direction::SOUTHEAST,
                                StructureType::VILLAGE)),
            false);
  EXPECT_EQ((board.hasStructure({0, 1}, Direction::NORTHEAST,
                                StructureType::VILLAGE)),
            false);

  // Roads
  EXPECT_EQ(
      (board.hasStructure({1, 0}, Direction::SOUTHEAST, StructureType::ROAD)),
      false);
  EXPECT_EQ(
      (board.hasStructure({1, 1}, Direction::NORTHWEST, StructureType::ROAD)),
      false);
}

TEST_F(BoardFixture, UpgradeEmptyTest) {
  EXPECT_THROW(
      {
        board.upgradeToCity(0, {1, 1}, Direction::NORTHWEST);
      },
      BuildStructureException);
}

TEST_F(BoardFixture, UpgradeCityTest) {
  board.buildStructure(0, std::make_shared<Building>(0, StructureType::VILLAGE),
                       {1, 1}, Direction::NORTHWEST, false);
  board.upgradeToCity(0, {1, 1}, Direction::NORTHWEST);
  EXPECT_THROW(
      {
        board.upgradeToCity(0, {1, 1}, Direction::NORTHWEST);
      },
      BuildStructureException);
}

TEST_F(BoardFixture, BuildAdjacentBuildingTest) {
  auto village1 = std::make_shared<Building>(0, StructureType::VILLAGE);
  auto village2 = std::make_shared<Building>(0, StructureType::VILLAGE);
  board.buildStructure(0, village1, {1, 1}, Direction::NORTHWEST, false);
  EXPECT_THROW(
      {
        board.buildStructure(0, village2, {1, 0}, Direction::SOUTHEAST, true);
      },
      BuildStructureException);

  EXPECT_THROW(
      {
        board.buildStructure(0, village2, {0, 1}, Direction::SOUTHEAST, true);
      },
      BuildStructureException);
  EXPECT_THROW(
      {
        board.buildStructure(0, village2, {0, 2}, Direction::NORTH, true);
      },
      BuildStructureException);
  EXPECT_THROW(
      {
        board.buildStructure(0, village2, {2, 0}, Direction::SOUTHWEST, true);
      },
      BuildStructureException);
}