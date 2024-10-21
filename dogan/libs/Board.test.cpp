#include "Board.h"
#include "Config.h"
#include "DoganConfigBuilder.h"
#include "DoganExceptions.h"
#include "ElementHelpers.h"
#include <utility>
#include <gtest/gtest.h>

using namespace Dogan;

class BoardFixture : public ::testing::Test {
  protected:
    void SetUp() override {
    }
    Board board{Config()};
};

TEST(BoardTest, AddDuplicateCellTest) {
  ConfigBuilder config = ConfigBuilder();
  config.setTileLocations({{0, 0}, {0, 0}});
  EXPECT_THROW({ Board board = Board(config.build()); }, std::invalid_argument);
}

TEST_F(BoardFixture, BuildStructuresTest) {
  auto villageNormal = std::make_shared<Building>(0, StructureType::VILLAGE);
  auto roadNormal = std::make_shared<Road>(0);

  // Villages
  board.buildStructure(villageNormal, {1, 1},
                       Direction::NORTHWEST);
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
  board.upgradeToCity({1, 0}, Direction::SOUTH);
  EXPECT_EQ((board.hasStructure({1, 1}, Direction::NORTHWEST,
                                StructureType::CITY)),
            true);
  EXPECT_EQ(
      (board.hasStructure({1, 0}, Direction::SOUTH, StructureType::CITY)),
      true);
  EXPECT_EQ((board.hasStructure({0, 1}, Direction::NORTHEAST,
                                StructureType::CITY)),
            true);

  // Roads
  board.buildStructure(roadNormal, {1, 0},
                       Direction::SOUTHEAST);
  EXPECT_EQ(
      (board.hasStructure({1, 0}, Direction::SOUTHEAST, StructureType::ROAD)),
      true);
  EXPECT_EQ(
      (board.hasStructure({1, 1}, Direction::NORTHWEST, StructureType::ROAD)),
      true);

}

TEST_F(BoardFixture, BuildEdgeStructuresTest) {
  auto villageEdge = std::make_shared<Building>(0, StructureType::VILLAGE);
  auto roadEdge = std::make_shared<Road>(0);
  // Edge Villages
  for (auto [i, j] : getAllVertexRepresentations(std::make_pair<Coordinate2D, Direction>({0, 0}, Direction::NORTHWEST)))
    std::cout << i << j;
  board.buildStructure(villageEdge, {0, 0},
                       Direction::NORTHWEST);
  EXPECT_EQ((board.hasStructure({0, 0}, Direction::NORTHWEST,
                                StructureType::VILLAGE)),
            true);
  EXPECT_EQ(
      (board.hasStructure({-1, 0}, Direction::SOUTH, StructureType::VILLAGE)),
      false);

  // Edge Cities
  board.upgradeToCity({0, 0}, Direction::NORTHWEST);
  EXPECT_EQ((board.hasStructure({0, 0}, Direction::NORTHWEST,
                                StructureType::CITY)),
            true);
  EXPECT_EQ(
      (board.hasStructure({-1, 0}, Direction::SOUTH, StructureType::CITY)),
      false);

  // Edge Roads
  board.buildStructure(roadEdge, {0, 0},
                       Direction::NORTHWEST);
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
  board.buildStructure(village, {1, 1},
                       Direction::NORTHWEST);
  EXPECT_THROW(
      {
        board.buildStructure(village, {1, 1},
                             Direction::NORTHWEST);
      },
      Dogan::SameStructureException);
  EXPECT_THROW(
      {
        board.buildStructure(existingVillage, {1, 0},
                             Direction::SOUTH);
      },
      Dogan::SameStructureException);

  // Roads
  board.buildStructure(road, {1, 0},
                       Direction::SOUTHEAST);
  EXPECT_THROW(
      {
        board.buildStructure(road, {1, 0},
                             Direction::SOUTHEAST);
      },
      Dogan::SameStructureException);

  EXPECT_THROW(
      {
        board.buildStructure(existingRoad, {1, 1},
                             Direction::NORTHWEST);
      },
      Dogan::SameStructureException);
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

TEST_F(BoardFixture, upgradeEmptyTest) {
  EXPECT_THROW(
      {
        board.upgradeToCity({1, 1}, Direction::NORTHWEST);
      },
      NoVillageException);
}

TEST_F(BoardFixture, upgradeCityTest) {
  board.buildStructure(std::make_shared<Building>(0, StructureType::VILLAGE), {1, 1}, Direction::NORTHWEST);
  board.upgradeToCity({1, 1}, Direction::NORTHWEST);
  EXPECT_THROW(
      {
        board.upgradeToCity({1, 1}, Direction::NORTHWEST);
      },
      NoVillageException);
}