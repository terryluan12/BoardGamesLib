#include "DoganConfigBuilder.h"
#include "DoganExceptions.h"
#include "DoganGame.h"
#include "Edge.h"
#include "Vertex.h"
#include "config.enum.h"
#include "enums.h"
#include <gtest/gtest.h>

using Direction = Dogan::Direction;
using StructureType = Dogan::StructureType;
using ResourceType = Dogan::ResourceType;

class GameFixture : public ::testing::Test {
protected:
  void SetUp() override {
    playerID1 = 0;
    playerID2 = 1;
    playerID3 = 2;

    Dogan::Config config1 = Dogan::ConfigBuilder().build();
    Dogan::Configuration generalConfig{Dogan::OrderConfiguration::EXACT,
                                       Dogan::ReplaceConfiguration::EXACT};
    std::vector<int> numberOrder{2, 3, 3, 4, 4,  5,  5,  6,  6,
                                 8, 8, 9, 9, 10, 10, 11, 11, 12};
    Dogan::Config config2 =
        Dogan::ConfigBuilder()
            .setNumberConfig(generalConfig)
            .setNumberOrder(numberOrder)
            .setBoardResourceConfig(generalConfig)
            .setBoardResourceOrder(
                {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4})
            .setDevelopmentConfig(generalConfig)
            .setDevelopmentOrder({Dogan::DevelopmentType::TAKETWO,
                                  Dogan::DevelopmentType::BUILDROAD,
                                  Dogan::DevelopmentType::SOLDIER,
                                  Dogan::DevelopmentType::MONOPOLY,
                                  Dogan::DevelopmentType::VICPOINT})
            .setDevelopmentCount({1, 1, 1, 1, 1})
            .build();
    nGame = Dogan::Game(config1);
    iGame = Dogan::Game(config2);
    iGame.addPlayer(playerID1);
    iGame.addPlayer(playerID2);
    iGame.addPlayer(playerID3);
  }

  Dogan::Game nGame;
  Dogan::Game iGame;

  int playerID1;
  int playerID2;
  int playerID3;
};

class MidGameFixture : public ::testing::Test {
protected:
  void SetUp() override {
    StructureType villageInput = StructureType::VILLAGE;
    StructureType roadInput = StructureType::ROAD;

    playerID1 = 0;
    playerID2 = 1;
    playerID3 = 2;

    Dogan::Configuration generalConfig{Dogan::OrderConfiguration::EXACT,
                                       Dogan::ReplaceConfiguration::EXACT};
    std::vector<int> numberOrder{2, 3, 3, 4, 4,  5,  5,  6,  6,
                                 8, 8, 9, 9, 10, 10, 11, 11, 12};
    Dogan::Config config =
        Dogan::ConfigBuilder()
            .setNumberConfig(generalConfig)
            .setNumberOrder(numberOrder)
            .setBoardResourceConfig(generalConfig)
            .setBoardResourceOrder(
                {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4})
            .setDevelopmentConfig(generalConfig)
            .setDevelopmentOrder({Dogan::DevelopmentType::TAKETWO,
                                  Dogan::DevelopmentType::BUILDROAD,
                                  Dogan::DevelopmentType::SOLDIER,
                                  Dogan::DevelopmentType::MONOPOLY,
                                  Dogan::DevelopmentType::VICPOINT})
            .setDevelopmentCount({1, 1, 1, 1, 1})
            .build();
    game = Dogan::Game(config);
    game.addPlayer(playerID1);
    game.addPlayer(playerID2);
    game.addPlayer(playerID3);

    game.buildStructure(playerID1, StructureType::VILLAGE, {0, 0},
                        Dogan::Direction::NORTH, {0, 0, 0, 0, 0}, false);
    game.buildStructure(playerID2, StructureType::VILLAGE, {-1, 4},
                        Direction::SOUTH, {0, 0, 0, 0, 0}, false);
    game.buildStructure(playerID3, StructureType::VILLAGE, {0, 2},
                        Direction::SOUTH, {0, 0, 0, 0, 0}, false);
    game.buildStructure(playerID1, StructureType::ROAD, {0, 0},
                        Direction::NORTHWEST, {0, 0, 0, 0, 0}, false);
    game.buildStructure(playerID2, StructureType::ROAD, {0, 2},
                        Direction::SOUTHEAST, {0, 0, 0, 0, 0}, false);
    game.buildStructure(playerID3, StructureType::ROAD, {0, 2},
                        Direction::SOUTHWEST, {0, 0, 0, 0, 0}, false);

    game.giveResources(playerID1, {4, 4, 4, 4, 4});
    game.giveResources(playerID2, {1, 2, 3, 4, 5});
    game.giveResources(playerID3, {0, 0, 0, 0, 0});
  }
  int playerID1, playerID2, playerID3;
  Dogan::Game game;
};

class BuildingParameterizedTestFixture
    : public ::testing::TestWithParam<Direction> {
protected:
  void SetUp() override {
    auto config = Dogan::ConfigBuilder().build();
    game = Dogan::Game(config);
    game.addPlayer(0);
    game.giveResources(0, {10, 10, 10, 10, 10});
  }
  Dogan::Game game;
};

TEST_P(BuildingParameterizedTestFixture, BuildingBuildingOnVertexTest) {
  Direction d = GetParam();
  EXPECT_NO_THROW({
    game.buildStructure(0, StructureType::VILLAGE, {0, 0}, d, {0, 0, 0, 0, 0},
                        false);
  });
}

INSTANTIATE_TEST_SUITE_P(AllVertexBuildingTests,
                         BuildingParameterizedTestFixture,
                         ::testing::ValuesIn(Vertex::directions));

class RoadParameterizedTestFixture
    : public ::testing::TestWithParam<Direction> {
protected:
  void SetUp() override {
    auto config = Dogan::ConfigBuilder().build();
    game = Dogan::Game(config);
    game.addPlayer(0);
  }
  Dogan::Game game;
};

TEST_P(RoadParameterizedTestFixture, BuildRoadTest) {
  Direction d = GetParam();
  EXPECT_NO_THROW({
    game.buildStructure(0, StructureType::ROAD, {1, 1}, d, {0, 0, 0, 0, 0},
                        false);
  });
}

INSTANTIATE_TEST_SUITE_P(AllEdgeRoadTests, RoadParameterizedTestFixture,
                         ::testing::ValuesIn(Edge::directions));

TEST_F(GameFixture, AddExistingPlayersTest) {
  nGame.addPlayer(0);
  EXPECT_THROW({ nGame.addPlayer(0); }, Dogan::SamePlayerException);
}

TEST_F(GameFixture, BuildStructuresTest) {
  // Buildings
  iGame.buildStructure(playerID1, StructureType::VILLAGE, {1, 1},
                       Direction::NORTHWEST, {0, 0, 0, 0, 0}, false);
  EXPECT_EQ((iGame.hasStructure({1, 1}, Direction::NORTHWEST,
                                StructureType::VILLAGE)),
            true);
  EXPECT_EQ(
      (iGame.hasStructure({1, 0}, Direction::SOUTH, StructureType::VILLAGE)),
      true);
  EXPECT_EQ((iGame.hasStructure({0, 1}, Direction::NORTHEAST,
                                StructureType::VILLAGE)),
            true);

  // Roads
  iGame.buildStructure(playerID1, StructureType::ROAD, {1, 0},
                       Direction::SOUTHEAST, {0, 0, 0, 0, 0}, false);
  EXPECT_EQ(
      (iGame.hasStructure({1, 0}, Direction::SOUTHEAST, StructureType::ROAD)),
      true);
  EXPECT_EQ(
      (iGame.hasStructure({1, 1}, Direction::NORTHWEST, StructureType::ROAD)),
      true);

  // Edge Building
  iGame.buildStructure(playerID1, StructureType::VILLAGE, {0, 0},
                       Direction::NORTHWEST, {0, 0, 0, 0, 0}, false);
  EXPECT_EQ((iGame.hasStructure({0, 0}, Direction::NORTHWEST,
                                StructureType::VILLAGE)),
            true);
  EXPECT_EQ(
      (iGame.hasStructure({-1, 0}, Direction::SOUTH, StructureType::VILLAGE)),
      false);

  // Edge Road
  iGame.buildStructure(playerID1, StructureType::ROAD, {0, 0},
                       Direction::NORTHWEST, {0, 0, 0, 0, 0}, false);
  EXPECT_EQ(
      (iGame.hasStructure({0, 0}, Direction::NORTHWEST, StructureType::ROAD)),
      true);
  EXPECT_EQ(
      (iGame.hasStructure({-1, 0}, Direction::SOUTHEAST, StructureType::ROAD)),
      false);
}

TEST_F(GameFixture, EmptyStructureTest) {

  // Buildings
  EXPECT_EQ((iGame.hasStructure({1, 1}, Direction::NORTHWEST,
                                StructureType::VILLAGE)),
            false);
  EXPECT_EQ((iGame.hasStructure({1, 0}, Direction::SOUTHEAST,
                                StructureType::VILLAGE)),
            false);
  EXPECT_EQ((iGame.hasStructure({0, 1}, Direction::NORTHEAST,
                                StructureType::VILLAGE)),
            false);

  // Roads
  EXPECT_EQ(
      (iGame.hasStructure({1, 0}, Direction::SOUTHEAST, StructureType::ROAD)),
      false);
  EXPECT_EQ(
      (iGame.hasStructure({1, 1}, Direction::NORTHWEST, StructureType::ROAD)),
      false);
}

// Trading Tests

TEST_F(MidGameFixture, TradeSuccessTest) {
  ASSERT_EQ((game.getResourceCount(playerID1)),
            (std::array<int, 5>{4, 4, 4, 4, 4}));
  ASSERT_EQ((game.getResourceCount(playerID2)),
            (std::array<int, 5>{1, 2, 3, 4, 5}));

  game.tradeResources(playerID1, {0, 0, 0, 0, 0}, playerID2, {0, 0, 0, 0, 0});

  ASSERT_EQ((game.getResourceCount(playerID1)),
            (std::array<int, 5>{4, 4, 4, 4, 4}));
  ASSERT_EQ((game.getResourceCount(playerID2)),
            (std::array<int, 5>{1, 2, 3, 4, 5}));

  game.tradeResources(playerID1, {0, 1, 2, 3, 4}, playerID2, {0, 0, 0, 0, 0});

  std::array<int, 5> expected1 = {4, 3, 2, 1, 0};
  std::array<int, 5> expected2 = {1, 3, 5, 7, 9};

  EXPECT_EQ((game.getResourceCount(playerID1)), expected1);
  EXPECT_EQ((game.getResourceCount(playerID2)), expected2);
}

TEST_F(MidGameFixture, TradeDebtTest) {
  ASSERT_EQ((game.getResourceCount(playerID1)),
            (std::array<int, 5>{4, 4, 4, 4, 4}));
  ASSERT_EQ((game.getResourceCount(playerID2)),
            (std::array<int, 5>{1, 2, 3, 4, 5}));

  EXPECT_THROW(
      {
        game.tradeResources(playerID1, {5, 0, 0, 0, 0}, playerID2,
                            {0, 0, 0, 0, 0});
      },
      Dogan::InsufficientResourcesException);
}

// Structures
TEST_F(GameFixture, BuildExistingStructuresTest) {

  // Buildings
  iGame.buildStructure(playerID1, StructureType::VILLAGE, {1, 1},
                       Direction::NORTHWEST, {0, 0, 0, 0, 0}, false);
  EXPECT_THROW(
      {
        iGame.buildStructure(playerID1, StructureType::VILLAGE, {1, 1},
                             Direction::NORTHWEST, {0, 0, 0, 0, 0}, false);
      },
      Dogan::BuildStructureException);
  EXPECT_THROW(
      {
        iGame.buildStructure(playerID2, StructureType::VILLAGE, {1, 0},
                             Direction::SOUTH, {0, 0, 0, 0, 0}, false);
      },
      Dogan::BuildStructureException);

  // Roads
  iGame.buildStructure(playerID1, StructureType::ROAD, {1, 0},
                       Direction::SOUTHEAST, {0, 0, 0, 0, 0}, false);
  EXPECT_THROW(
      {
        iGame.buildStructure(playerID1, StructureType::ROAD, {1, 0},
                             Direction::SOUTHEAST, {0, 0, 0, 0, 0}, false);
      },
      Dogan::BuildStructureException);

  EXPECT_THROW(
      {
        iGame.buildStructure(playerID2, StructureType::ROAD, {1, 1},
                             Direction::NORTHWEST, {0, 0, 0, 0, 0}, false);
      },
      Dogan::BuildStructureException);
}

TEST_F(GameFixture, DistributeResourcesTest) {
  iGame.buildStructure(playerID1, StructureType::VILLAGE, {0, 0},
                       Direction::NORTH, {0, 0, 0, 0, 0}, false);
  int rolledDice = 2;
  iGame.distributeResources(rolledDice);
  std::array<int, 5> actual = iGame.getResourceCount(playerID1);
  std::array<int, 5> expected{0, 0, 0, 0, 1};
  EXPECT_EQ(actual, expected);
}

// Development Card Tests

TEST_F(GameFixture, CircularEconomyTest) {
  ASSERT_EQ(iGame.getResourceCount(-1),
            (std::array<int, 5>{19, 19, 19, 19, 19}));
  iGame.giveResources(playerID1, {4, 4, 4, 4, 4});
  iGame.buildStructure(playerID1, StructureType::VILLAGE, {1, 1},
                       Direction::NORTHWEST, {0, 1, 2, 3, 4}, false);

  std::array<int, 5> expected{19, 20, 21, 22, 23};
  EXPECT_EQ(iGame.getResourceCount(-1), expected);
}

// Functional Tests

TEST_F(GameFixture, StartPhaseTest) {
  iGame.buildStructure(playerID1, StructureType::VILLAGE, {1, 1},
                       Direction::NORTH, {0, 0, 0, 0, 0}, false);
  iGame.giveResources(playerID1, {1, 0, 0, 0, 0});
  iGame.buildStructure(playerID1, StructureType::ROAD, {1, 0},
                       Direction::NORTHEAST, {0, 0, 0, 0, 0}, false);
}

TEST_F(GameFixture, TradePhaseTest) {
  iGame.giveResources(playerID1, {4, 4, 4, 4, 4});
  iGame.giveResources(playerID2, {4, 4, 4, 4, 4});
  iGame.tradeResources(playerID1, {0, 1, 2, 3, 4}, playerID2, {0, 0, 0, 0, 0});
}

TEST_F(MidGameFixture, BuildAdjacentStructureSuccessTest) {
  game.buildStructure(playerID1, StructureType::ROAD, {0, 0}, Direction::WEST,
                      {0, 0, 0, 0, 0}, false);
  game.buildStructure(playerID1, StructureType::VILLAGE, {0, 0},
                      Direction::SOUTHWEST, {0, 0, 0, 0, 0}, false);
  EXPECT_EQ(
      game.hasStructure({-1, 1}, Direction::NORTH, StructureType::VILLAGE),
      true);

  game.buildStructure(playerID1, StructureType::ROAD, {-1, 1},
                      Direction::NORTHEAST, {0, 0, 0, 0, 0}, false);
  EXPECT_EQ(
      game.hasStructure({0, 0}, Direction::SOUTHWEST, StructureType::ROAD),
      true);

  game.buildStructure(playerID3, StructureType::ROAD, {-1, 3},
                      Direction::NORTHWEST, {0, 0, 0, 0, 0}, false);
  EXPECT_EQ(
      game.hasStructure({-1, 2}, Direction::SOUTHEAST, StructureType::ROAD),
      true);

  game.buildStructure(playerID3, StructureType::VILLAGE, {-2, 3},
                      Direction::NORTHEAST, {0, 0, 0, 0, 0}, false);
  EXPECT_EQ(
      game.hasStructure({-1, 2}, Direction::SOUTH, StructureType::VILLAGE),
      true);
}

TEST_F(MidGameFixture, BuildAdjacentStructureFailTest) {
  EXPECT_THROW(
      {
        game.buildStructure(playerID1, StructureType::VILLAGE, {2, 1},
                            Direction::SOUTHWEST, {0, 0, 0, 0, 0});
      },
      Dogan::BuildStructureException);
  EXPECT_EQ(
      game.hasStructure({2, 1}, Direction::SOUTHWEST, StructureType::VILLAGE),
      false);
  EXPECT_EQ(game.hasStructure({1, 2}, Direction::NORTH, StructureType::VILLAGE),
            false);
  EXPECT_EQ(
      game.hasStructure({1, 1}, Direction::SOUTHEAST, StructureType::VILLAGE),
      false);

  EXPECT_THROW(
      {
        game.buildStructure(playerID1, StructureType::ROAD, {-1, 4},
                            Direction::NORTHEAST, {0, 0, 0, 0, 0});
      },
      Dogan::BuildStructureException);
  EXPECT_EQ(
      game.hasStructure({-1, 4}, Direction::NORTHEAST, StructureType::ROAD),
      false);
  EXPECT_EQ(
      game.hasStructure({0, 3}, Direction::SOUTHWEST, StructureType::ROAD),
      false);
}

TEST_F(MidGameFixture, UseRobberNoStealTest) {
  game.useRobber(playerID1, {0, 0}, Direction::NONE);
  game.useRobber(playerID1, {-1, 4}, Direction::NONE);
  game.useRobber(playerID1, {0, 2}, Direction::NONE);
  EXPECT_EQ(game.getResourceCount(playerID1),
            (std::array<int, 5>{4, 4, 4, 4, 4}));
}

TEST_F(GameFixture, BuildWithoutStructuresTest) {
  iGame.buildStructure(playerID1, StructureType::VILLAGE, {0, 0},
                       Direction::NORTH, {0, 0, 0, 0, 0}, false);
  iGame.buildStructure(playerID1, StructureType::VILLAGE, {0, 1},
                       Direction::NORTH, {0, 0, 0, 0, 0}, false);
  iGame.buildStructure(playerID1, StructureType::VILLAGE, {0, 2},
                       Direction::NORTH, {0, 0, 0, 0, 0}, false);
  iGame.buildStructure(playerID1, StructureType::VILLAGE, {0, 3},
                       Direction::NORTH, {0, 0, 0, 0, 0}, false);
  iGame.buildStructure(playerID1, StructureType::VILLAGE, {0, 4},
                       Direction::NORTH, {0, 0, 0, 0, 0}, false);
  EXPECT_THROW(
      {
        iGame.buildStructure(playerID1, StructureType::VILLAGE, {1, 3},
                             Direction::NORTH, {0, 0, 0, 0, 0}, false);
      },
      Dogan::InsufficientStructuresException);
  iGame.buildStructure(playerID1, StructureType::CITY, {0, 4}, Direction::NORTH,
                       {0, 0, 0, 0, 0}, true);
  EXPECT_NO_THROW({
    iGame.buildStructure(playerID1, StructureType::VILLAGE, {1, 2},
                         Direction::NORTH, {0, 0, 0, 0, 0}, false);
  });
}

TEST_F(GameFixture, UpgradeSomeoneElsesVillageTest) {
  iGame.buildStructure(playerID2, StructureType::VILLAGE, {0, 0},
                       Direction::NORTH, {0, 0, 0, 0, 0}, false);
  EXPECT_THROW(
      {
        iGame.buildStructure(playerID1, StructureType::CITY, {0, 1},
                             Direction::NORTH, {0, 0, 0, 0, 0}, false);
      },
      Dogan::BuildStructureException);
}

class DevelopmentCardTestSuite : public ::testing::Test {
protected:
  void SetUp() override {
    playerID1 = 0;
    playerID2 = 1;
    playerID3 = 2;

    Dogan::Configuration generalConfig{Dogan::OrderConfiguration::EXACT,
                                       Dogan::ReplaceConfiguration::EXACT};
    Dogan::Config config = Dogan::ConfigBuilder()
                               .setDevelopmentConfig(generalConfig)
                               .setDevelopmentOrder({
                                   Dogan::DevelopmentType::TAKETWO,
                                   Dogan::DevelopmentType::TAKETWO,
                                   Dogan::DevelopmentType::BUILDROAD,
                                   Dogan::DevelopmentType::SOLDIER,
                                   Dogan::DevelopmentType::MONOPOLY,
                                   Dogan::DevelopmentType::VICPOINT,
                               })
                               .setDevelopmentCount({1, 1, 1, 1, 2})
                               .build();

    // initialGame = Dogan::Game(config);
    // initialGame.addPlayer(playerID1);

    game = Dogan::Game(config);
    game.addPlayer(playerID1);
    game.addPlayer(playerID2);
    game.addPlayer(playerID3);

    game.buildStructure(playerID1, StructureType::VILLAGE, {0, 0},
                        Dogan::Direction::NORTH, {0, 0, 0, 0, 0}, false);
    game.buildStructure(playerID2, StructureType::VILLAGE, {-1, 4},
                        Direction::SOUTH, {0, 0, 0, 0, 0}, false);
    game.buildStructure(playerID1, StructureType::ROAD, {0, 0},
                        Direction::NORTHWEST, {0, 0, 0, 0, 0}, false);
    game.buildStructure(playerID2, StructureType::ROAD, {0, 2},
                        Direction::SOUTHEAST, {0, 0, 0, 0, 0}, false);

    game.giveResources(playerID1, {4, 4, 4, 4, 4});
    game.giveResources(playerID2, {1, 2, 3, 4, 5});
    game.giveResources(playerID3, {1, 2, 3, 4, 5});
    for (int i = 0; i < 6; i++) {
      game.purchaseDevelopmentCard(playerID1, {0, 0, 0, 0, 0});
    }
  }
  int playerID1, playerID2, playerID3;
  Dogan::Game game;
  // Dogan::Game initialGame;
};

// TEST_F(DevelopmentCardTestSuite, PurchaseDevelopmentCardTest) {
//   std::array<int, 5> expected{0, 0, 0, 0, 0};
//   for (int i = 0; i < 5; i++) {
//     initialGame.purchaseDevelopmentCard(playerID1, {0, 0, 0, 0, 0});
//     expected[i] = 1;
//     std::array<int, 5> actual = initialGame.getDevelopmentCount(playerID1);
//     EXPECT_EQ(actual, expected);
//   }
// }

TEST_F(DevelopmentCardTestSuite, UseDevelopmentCardVictoryTest) {
  EXPECT_EQ(game.getVictoryPoints(playerID1), 2);
}

TEST_F(DevelopmentCardTestSuite, UseDevelopmentCardMonopolyTest) {
  game.useMonopolyDevelopmentCard(playerID1, ResourceType::WOOD);

  EXPECT_EQ(game.getResourceCount(playerID1),
            (std::array<int, 5>{6, 4, 4, 4, 4}));
  EXPECT_EQ(game.getResourceCount(playerID2),
            (std::array<int, 5>{0, 2, 3, 4, 5}));
  EXPECT_EQ(game.getResourceCount(playerID3),
            (std::array<int, 5>{0, 2, 3, 4, 5}));
}

TEST_F(DevelopmentCardTestSuite, useSoldierDevelopmentCardTest) {
  game.useSoldierDevelopmentCard(playerID1, {-1, 4}, Direction::SOUTH);

  int totalSum = 0;
  for (int i = 0; i < 5; i++) {
    totalSum += game.getResourceCount(playerID1)[i];
  }
  EXPECT_EQ(totalSum, 21);

  totalSum = 0;
  for (int i = 0; i < 5; i++) {
    totalSum += game.getResourceCount(playerID2)[i];
  }
  EXPECT_EQ(totalSum, 14);
}

TEST_F(DevelopmentCardTestSuite, useRoadDevelopmentCardTest) {
  std::array<Coordinate2D, 2> tileLocations{{{0, 0}, {-1, 1}}};
  std::array<Direction, 2> directions{Direction::WEST, Direction::NORTHEAST};

  game.useRoadDevelopmentCard(playerID1, tileLocations, directions);
  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(
        game.hasStructure(tileLocations[i], directions[i], StructureType::ROAD),
        true);
  }
  EXPECT_EQ(
      game.hasStructure({0, 0}, Direction::SOUTHWEST, StructureType::ROAD),
      true);
}

TEST_F(DevelopmentCardTestSuite, useTakeTwoDevelopmentCardTest) {
  std::array<ResourceType, 2> resources1{ResourceType::BRICK,
                                         ResourceType::SHEEP};

  game.useTakeTwoDevelopmentCard(playerID1, resources1);
  EXPECT_EQ(game.getResourceCount(playerID1),
            (std::array<int, 5>{4, 5, 4, 5, 4}));
  EXPECT_EQ(game.getResourceCount(-1),
            (std::array<int, 5>{19, 18, 19, 18, 19}));
}

TEST_F(DevelopmentCardTestSuite, DoubleUseSameDevelopmentCardsTest) {
  game.useTakeTwoDevelopmentCard(playerID1,
                                 {ResourceType::BRICK, ResourceType::SHEEP});
  EXPECT_THROW(
      {
        game.useTakeTwoDevelopmentCard(
            playerID1, {ResourceType::BRICK, ResourceType::SHEEP});
      },
      Dogan::UsedDevelopmentCardException);

  EXPECT_EQ(game.getResourceCount(playerID1),
            (std::array<int, 5>{4, 5, 4, 5, 4}));
  EXPECT_EQ(game.getResourceCount(playerID2),
            (std::array<int, 5>{1, 2, 3, 4, 5}));
}

TEST_F(DevelopmentCardTestSuite, DoubleUseDifferentDevelopmentCardsTest) {
  game.useTakeTwoDevelopmentCard(playerID1,
                                 {ResourceType::BRICK, ResourceType::SHEEP});
  EXPECT_THROW(
      { game.useMonopolyDevelopmentCard(playerID1, ResourceType::BRICK); },
      Dogan::UsedDevelopmentCardException);
  EXPECT_EQ(game.getResourceCount(playerID1),
            (std::array<int, 5>{4, 5, 4, 5, 4}));
  EXPECT_EQ(game.getResourceCount(playerID2),
            (std::array<int, 5>{1, 2, 3, 4, 5}));
}

TEST_F(DevelopmentCardTestSuite, DevelopmentCardResetTurnTest) {
  std::array<ResourceType, 2> resources1{ResourceType::BRICK,
                                         ResourceType::SHEEP};
  std::array<ResourceType, 2> resources2{ResourceType::WOOD,
                                         ResourceType::WOOD};

  game.useTakeTwoDevelopmentCard(playerID1, resources1);
  EXPECT_EQ(game.getResourceCount(playerID1),
            (std::array<int, 5>{4, 5, 4, 5, 4}));
  game.resetTurn();
  game.useTakeTwoDevelopmentCard(playerID1, resources2);

  EXPECT_EQ(game.getResourceCount(playerID1),
            (std::array<int, 5>{6, 5, 4, 5, 4}));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}