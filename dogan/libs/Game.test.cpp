#include "DoganConfigBuilder.h"
#include "DoganExceptions.h"
#include "DoganGame.h"
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
    std::vector<int> numberLocations{2, 3, 3, 4, 4,  5,  5,  6,  6, 7,
                                     8, 8, 9, 9, 10, 10, 11, 11, 12};
    Dogan::Config config2 =
        Dogan::ConfigBuilder()
            .setNumberConfig(generalConfig)
            .setNumberLocations(numberLocations)
            .setResourceConfig(generalConfig)
            .setResources(
                {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4})
            .setDevelopmentConfig(generalConfig)
            .setDevelopmentLocations({Dogan::DevelopmentType::TAKETWO,
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
    playerID1 = 0;
    playerID2 = 1;
    playerID3 = 2;

    Dogan::Configuration generalConfig{Dogan::OrderConfiguration::EXACT,
                                       Dogan::ReplaceConfiguration::EXACT};
    std::vector<int> numberLocations{2, 3, 3, 4, 4,  5,  5,  6,  6, 7,
                                     8, 8, 9, 9, 10, 10, 11, 11, 12};
    Dogan::Config config =
        Dogan::ConfigBuilder()
            .setNumberConfig(generalConfig)
            .setNumberLocations(numberLocations)
            .setResourceConfig(generalConfig)
            .setResources(
                {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4})
            .setDevelopmentConfig(generalConfig)
            .setDevelopmentLocations({Dogan::DevelopmentType::TAKETWO,
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
                        Dogan::Direction::NORTH, {0, 0, 0, 0, 0});
    game.buildStructure(playerID2, StructureType::VILLAGE, {-1, 4},
                        Direction::SOUTH, {0, 0, 0, 0, 0});
    game.buildStructure(playerID3, StructureType::VILLAGE, {0, 2},
                        Direction::SOUTH, {0, 0, 0, 0, 0});
    game.buildStructure(playerID1, StructureType::ROAD, {0, 0},
                        Direction::NORTHWEST, {0, 0, 0, 0, 0});
    game.buildStructure(playerID2, StructureType::ROAD, {0, 2},
                        Direction::SOUTHEAST, {0, 0, 0, 0, 0});
    game.buildStructure(playerID3, StructureType::ROAD, {0, 2},
                        Direction::SOUTHWEST, {0, 0, 0, 0, 0});

    game.giveResources(playerID1, {4, 4, 4, 4, 4});
    game.giveResources(playerID2, {1, 2, 3, 4, 5});
    game.giveResources(playerID3, {0, 0, 0, 0, 0});
  }
  int playerID1, playerID2, playerID3;
  Dogan::Game game;
};

TEST_F(GameFixture, AddExistingPlayersTest) {
  nGame.addPlayer(0);
  EXPECT_THROW({ nGame.addPlayer(0); }, Dogan::SamePlayerException);
}

TEST_F(GameFixture, BuildStructuresTest) {
  // Buildings
  iGame.buildStructure(playerID1, StructureType::VILLAGE, {1, 1},
                       Direction::NORTHWEST, {0, 0, 0, 0, 0});
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
                       Direction::SOUTHEAST, {0, 0, 0, 0, 0});
  EXPECT_EQ(
      (iGame.hasStructure({1, 0}, Direction::SOUTHEAST, StructureType::ROAD)),
      true);
  EXPECT_EQ(
      (iGame.hasStructure({1, 1}, Direction::NORTHWEST, StructureType::ROAD)),
      true);

  // Edge Building
  iGame.buildStructure(playerID1, StructureType::VILLAGE, {0, 0},
                       Direction::NORTHWEST, {0, 0, 0, 0, 0});
  EXPECT_EQ((iGame.hasStructure({0, 0}, Direction::NORTHWEST,
                                StructureType::VILLAGE)),
            true);
  EXPECT_EQ(
      (iGame.hasStructure({-1, 0}, Direction::SOUTH, StructureType::VILLAGE)),
      false);

  // Edge Road
  iGame.buildStructure(playerID1, StructureType::ROAD, {0, 0},
                       Direction::NORTHWEST, {0, 0, 0, 0, 0});
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
      Dogan::InsufficientFundsException);
}

// Structures
TEST_F(GameFixture, BuildExistingStructuresTest) {

  // Buildings
  iGame.buildStructure(playerID1, StructureType::VILLAGE, {1, 1},
                       Direction::NORTHWEST, {0, 0, 0, 0, 0});
  EXPECT_THROW(
      {
        iGame.buildStructure(playerID1, StructureType::VILLAGE, {1, 1},
                             Direction::NORTHWEST, {0, 0, 0, 0, 0});
      },
      Dogan::SameStructureException);
  EXPECT_THROW(
      {
        iGame.buildStructure(playerID2, StructureType::VILLAGE, {1, 0},
                             Direction::SOUTH, {0, 0, 0, 0, 0});
      },
      Dogan::SameStructureException);

  // Roads
  iGame.buildStructure(playerID1, StructureType::ROAD, {1, 0},
                       Direction::SOUTHEAST, {0, 0, 0, 0, 0});
  EXPECT_THROW(
      {
        iGame.buildStructure(playerID1, StructureType::ROAD, {1, 0},
                             Direction::SOUTHEAST, {0, 0, 0, 0, 0});
      },
      Dogan::SameStructureException);

  EXPECT_THROW(
      {
        iGame.buildStructure(playerID2, StructureType::ROAD, {1, 1},
                             Direction::NORTHWEST, {0, 0, 0, 0, 0});
      },
      Dogan::SameStructureException);
}

TEST_F(GameFixture, DistributeResourcesTest) {
  iGame.buildStructure(playerID1, StructureType::VILLAGE, {0, 0},
                       Direction::NORTH, {0, 0, 0, 0, 0});
  int rolledDice = 2;
  iGame.distributeResources(rolledDice);
  std::array<int, 5> actual = iGame.getResourceCount(playerID1);
  std::array<int, 5> expected{0, 0, 0, 0, 1};
  EXPECT_EQ(actual, expected);
}

// Development Card Tests

TEST_F(GameFixture, PurchaseDevelopmentCardTest) {
  std::array<int, 5> expected{0, 0, 0, 0, 0};
  for (int i = 0; i < 5; i++) {
    iGame.purchaseDevelopmentCard(playerID1, {0, 0, 0, 0, 0});
    expected[i] = 1;
    std::array<int, 5> actual = iGame.getDevelopmentCount(playerID1);
    EXPECT_EQ(actual, expected);
  }
}

TEST_F(GameFixture, UseDevelopmentCardVictoryTest) {
  for (int i = 0; i < 5; i++) {
    iGame.purchaseDevelopmentCard(playerID1, {0, 0, 0, 0, 0});
  }
  EXPECT_EQ(iGame.getVictoryPoints(playerID1), 1);
}

TEST_F(GameFixture, UseDevelopmentCardMonopolyTest) {
  for (int i = 0; i < 5; i++) {
    iGame.purchaseDevelopmentCard(playerID1, {0, 0, 0, 0, 0});
  }
  iGame.giveResources(playerID2, {5, 4, 3, 2, 1});
  iGame.giveResources(playerID3, {5, 4, 3, 2, 1});
  ASSERT_EQ(iGame.getResourceCount(playerID1),
            (std::array<int, 5>{0, 0, 0, 0, 0}));
  ASSERT_EQ(iGame.getResourceCount(playerID2),
            (std::array<int, 5>{5, 4, 3, 2, 1}));
  ASSERT_EQ(iGame.getResourceCount(playerID3),
            (std::array<int, 5>{5, 4, 3, 2, 1}));
  iGame.useMonopolyDevelopmentCard(playerID1, ResourceType::WOOD);

  EXPECT_EQ(iGame.getResourceCount(playerID1),
            (std::array<int, 5>{10, 0, 0, 0, 0}));
  EXPECT_EQ(iGame.getResourceCount(playerID2),
            (std::array<int, 5>{0, 4, 3, 2, 1}));
  EXPECT_EQ(iGame.getResourceCount(playerID3),
            (std::array<int, 5>{0, 4, 3, 2, 1}));
}

TEST_F(GameFixture, useSoldierDevelopmentCardTest) {
  for (int i = 0; i < 5; i++) {
    iGame.purchaseDevelopmentCard(playerID1, {0, 0, 0, 0, 0});
  }
  iGame.buildStructure(playerID2, StructureType::VILLAGE, {1, 1},
                       Direction::NORTHWEST, {0, 0, 0, 0, 0});
  iGame.giveResources(playerID2, {0, 1, 2, 3, 4});
  EXPECT_EQ(iGame.getResourceCount(playerID1),
            (std::array<int, 5>{0, 0, 0, 0, 0}));
  EXPECT_EQ(iGame.getResourceCount(playerID2),
            (std::array<int, 5>{0, 1, 2, 3, 4}));

  iGame.useSoldierDevelopmentCard(playerID1, {1, 1}, Direction::NORTHWEST);

  int totalSum = 0;
  for (int i = 0; i < 5; i++) {
    totalSum += iGame.getResourceCount(playerID1)[i];
  }
  EXPECT_EQ(totalSum, 1);

  totalSum = 0;
  for (int i = 0; i < 5; i++) {
    totalSum += i - iGame.getResourceCount(playerID2)[i];
  }
  EXPECT_EQ(totalSum, 1);
}

TEST_F(GameFixture, useRoadDevelopmentCardTest) {
  for (int i = 0; i < 5; i++) {
    iGame.purchaseDevelopmentCard(playerID1, {0, 0, 0, 0, 0});
  }

  std::array<Coordinate2D, 2> tileLocations{{{1, 1}, {1, 0}}};
  std::array<Direction, 2> directions{Direction::NORTHWEST,
                                      Direction::NORTHWEST};
  iGame.buildStructure(playerID2, StructureType::VILLAGE, {1, 1},
                       Direction::NORTHWEST, {0, 0, 0, 0, 0});

  iGame.useRoadDevelopmentCard(playerID1, tileLocations, directions);
  EXPECT_EQ(
      iGame.hasStructure({1, 1}, Direction::NORTHWEST, StructureType::ROAD),
      true);
  EXPECT_EQ(
      iGame.hasStructure({1, 0}, Direction::SOUTHEAST, StructureType::ROAD),
      true);
  EXPECT_EQ(
      iGame.hasStructure({1, 0}, Direction::NORTHWEST, StructureType::ROAD),
      true);
}

TEST_F(GameFixture, useTakeTwoDevelopmentCardTest) {
  for (int i = 0; i < 5; i++) {
    iGame.purchaseDevelopmentCard(playerID1, {0, 0, 0, 0, 0});
  }
  std::array<ResourceType, 2> resources1{ResourceType::BRICK,
                                         ResourceType::SHEEP};
  std::array<ResourceType, 2> resources2{ResourceType::WOOD,
                                         ResourceType::WOOD};

  EXPECT_EQ(iGame.getResourceCount(playerID1),
            (std::array<int, 5>{0, 0, 0, 0, 0}));

  iGame.useTakeTwoDevelopmentCard(playerID1, resources1);
  EXPECT_EQ(iGame.getResourceCount(playerID1),
            (std::array<int, 5>{0, 1, 0, 1, 0}));
  iGame.useTakeTwoDevelopmentCard(playerID1, resources2);

  EXPECT_EQ(iGame.getResourceCount(playerID1),
            (std::array<int, 5>{2, 1, 0, 1, 0}));
}

TEST_F(GameFixture, CircularEconomyTest) {
  ASSERT_EQ(iGame.getResourceCount(-1),
            (std::array<int, 5>{19, 19, 19, 19, 19}));
  iGame.giveResources(playerID1, {4, 4, 4, 4, 4});
  iGame.buildStructure(playerID1, StructureType::VILLAGE, {1, 1},
                       Direction::NORTHWEST, {0, 1, 2, 3, 4});

  std::array<int, 5> expected{19, 20, 21, 22, 23};
  EXPECT_EQ(iGame.getResourceCount(-1), expected);
}

// Functional Tests

TEST_F(GameFixture, StartPhaseTest) {
  iGame.buildStructure(playerID1, StructureType::VILLAGE, {1, 1},
                       Direction::NORTH, {0, 0, 0, 0, 0});
  iGame.giveResources(playerID1, {1, 0, 0, 0, 0});
  iGame.buildStructure(playerID1, StructureType::ROAD, {1, 0},
                       Direction::NORTHEAST, {0, 0, 0, 0, 0});
}

TEST_F(GameFixture, TradePhaseTest) {
  iGame.giveResources(playerID1, {4, 4, 4, 4, 4});
  iGame.giveResources(playerID2, {4, 4, 4, 4, 4});
  iGame.tradeResources(playerID1, {0, 1, 2, 3, 4}, playerID2, {0, 0, 0, 0, 0});
}


TEST_F(MidGameFixture, BuildAdjacentStructureSuccessTest) {
    game.buildStructure(playerID1, StructureType::ROAD, {0, 0},
                        Direction::WEST, {0, 0, 0, 0, 0});
    game.buildAdjacentStructure(playerID1, StructureType::VILLAGE, {0, 0},
                                Direction::SOUTHWEST, {0, 0, 0, 0, 0});
    EXPECT_EQ(game.hasStructure({-1, 1}, Direction::NORTH, StructureType::VILLAGE),
              true);
                                
    game.buildAdjacentStructure(playerID1, StructureType::ROAD, {-1, 1},
                                Direction::NORTHEAST, {0, 0, 0, 0, 0});
    EXPECT_EQ(game.hasStructure({0, 0}, Direction::SOUTHWEST, StructureType::ROAD),
              true);

    game.buildAdjacentStructure(playerID3, StructureType::ROAD, {-1, 3},
                                Direction::NORTHWEST, {0, 0, 0, 0, 0});
    EXPECT_EQ(game.hasStructure({-1, 2}, Direction::SOUTHEAST, StructureType::ROAD),
              true);
    
    game.buildAdjacentStructure(playerID3, StructureType::VILLAGE, {-2, 3},
                                Direction::NORTHEAST, {0, 0, 0, 0, 0});
    EXPECT_EQ(game.hasStructure({-1, 2}, Direction::SOUTH, StructureType::VILLAGE),
              true);
}

TEST_F(MidGameFixture, BuildAdjacentStructureFailTest) {
    EXPECT_THROW({
    game.buildAdjacentStructure(playerID1, StructureType::VILLAGE, {2, 1},
                                Direction::SOUTHWEST, {0, 0, 0, 0, 0});
    }, Dogan::NoAdjacentRoadException);
    EXPECT_EQ(game.hasStructure({2, 1}, Direction::SOUTHWEST, StructureType::VILLAGE),
              false);
    EXPECT_EQ(game.hasStructure({1, 2}, Direction::NORTH, StructureType::VILLAGE),
              false);
    EXPECT_EQ(game.hasStructure({1, 1}, Direction::SOUTHEAST, StructureType::VILLAGE),
              false);

    EXPECT_THROW({
    game.buildAdjacentStructure(playerID1, StructureType::ROAD, {-1, 4},
                                Direction::NORTHEAST, {0, 0, 0, 0, 0});
    }, Dogan::NoAdjacentRoadException);
    EXPECT_EQ(game.hasStructure({-1, 4}, Direction::NORTHEAST, StructureType::ROAD),
              false);
    EXPECT_EQ(game.hasStructure({0, 3}, Direction::SOUTHWEST, StructureType::ROAD),
              false);
}