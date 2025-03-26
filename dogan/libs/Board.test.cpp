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
  auto Coordinate_1_1 = Coordinate2D(1, 1);
  auto Coordinate_1_0 = Coordinate2D(1, 0);

  auto villageNormal = std::make_shared<Building>(
      0, StructureType::VILLAGE, Coordinate_1_1, Direction::NORTHWEST);
  auto roadNormal =
      std::make_shared<Road>(0, Coordinate_1_0, Direction::SOUTHEAST);

  // Villages
  board.buildStructure(0, villageNormal, false);
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
  board.buildStructure(0, roadNormal, false);
  EXPECT_EQ(
      (board.hasStructure({1, 0}, Direction::SOUTHEAST, StructureType::ROAD)),
      true);
  EXPECT_EQ(
      (board.hasStructure({1, 1}, Direction::NORTHWEST, StructureType::ROAD)),
      true);
}

TEST_F(BoardFixture, BuildNonAdjacentEdgeStructuresTest) {
  auto Coordinate_0_0 = Coordinate2D(0, 0);
  auto villageEdge = std::make_shared<Building>(
      0, StructureType::VILLAGE, Coordinate_0_0, Direction::NORTHWEST);
  auto roadEdge =
      std::make_shared<Road>(0, Coordinate_0_0, Direction::NORTHWEST);
  // Edge Villages
  board.buildStructure(0, villageEdge, false);
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
  board.buildStructure(0, roadEdge, false);
  EXPECT_EQ(
      (board.hasStructure({0, 0}, Direction::NORTHWEST, StructureType::ROAD)),
      true);
  EXPECT_EQ(
      (board.hasStructure({-1, 0}, Direction::SOUTHEAST, StructureType::ROAD)),
      false);
}

// Structures
TEST_F(BoardFixture, BuildExistingStructuresTest) {
  auto Coordinate_1_1 = Coordinate2D(1, 1);
  auto Coordinate_1_0 = Coordinate2D(1, 0);
  auto village = std::make_shared<Building>(
      0, StructureType::VILLAGE, Coordinate_1_1, Direction::NORTHWEST);
  auto existingVillage = std::make_shared<Building>(
      0, StructureType::VILLAGE, Coordinate_1_0, Direction::SOUTH);
  auto road = std::make_shared<Road>(0, Coordinate_1_0, Direction::SOUTHEAST);
  auto existingRoad =
      std::make_shared<Road>(0, Coordinate_1_1, Direction::NORTHWEST);

  // Buildings
  board.buildStructure(0, village, false);
  EXPECT_THROW({ board.buildStructure(0, village, false); },
               Dogan::BuildStructureException);
  EXPECT_THROW({ board.buildStructure(0, existingVillage, false); },
               Dogan::BuildStructureException);

  // Roads
  board.buildStructure(0, road, false);
  EXPECT_THROW({ board.buildStructure(0, road, false); },
               Dogan::BuildStructureException);

  EXPECT_THROW({ board.buildStructure(0, existingRoad, false); },
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
  auto Coordinate_1_1 = Coordinate2D(1, 1);
  auto building = std::make_shared<Building>(
      0, StructureType::VILLAGE, Coordinate_1_1, Direction::NORTHWEST);
  board.buildStructure(0, building, false);
  board.upgradeToCity(0, {1, 1}, Direction::NORTHWEST);
  EXPECT_THROW(
      {
        board.upgradeToCity(0, {1, 1}, Direction::NORTHWEST);
      },
      BuildStructureException);
}

TEST_F(BoardFixture, BuildAdjacentBuildingTest) {
  auto Coordinate_1_1 = Coordinate2D(1, 1);
  auto Coordinate_1_0 = Coordinate2D(1, 0);
  auto Coordinate_0_2 = Coordinate2D(0, 2);
  auto Coordinate_2_0 = Coordinate2D(2, 0);
  auto village1 = std::make_shared<Building>(
      0, StructureType::VILLAGE, Coordinate_1_1, Direction::NORTHWEST);
  auto village2 = std::make_shared<Building>(
      0, StructureType::VILLAGE, Coordinate_1_0, Direction::SOUTHEAST);
  auto identical_village2 = std::make_shared<Building>(
      0, StructureType::VILLAGE, Coordinate_0_2, Direction::NORTH);
  auto identical1_village2 = std::make_shared<Building>(
      0, StructureType::VILLAGE, Coordinate_2_0, Direction::SOUTHWEST);
  board.buildStructure(0, village1, false);
  EXPECT_THROW({ board.buildStructure(0, village2, true); },
               BuildStructureException);

  EXPECT_THROW({ board.buildStructure(0, village2, true); },
               BuildStructureException);
  EXPECT_THROW({ board.buildStructure(0, village2, true); },
               BuildStructureException);
  EXPECT_THROW({ board.buildStructure(0, village2, true); },
               BuildStructureException);
}