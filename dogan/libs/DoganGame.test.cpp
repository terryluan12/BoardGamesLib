#include "DoganGame.h"
#include "DoganConfigBuilder.h"
#include "DoganStructureType.h"
#include "DoganExceptions.h"
#include <gtest/gtest.h>
#include "config.enum.h"

class GameFixture : public ::testing::Test {
protected:
  void SetUp() override {
    villageInt = DoganStructureType::toInt(StructureType::VILLAGE);
    roadInt = DoganStructureType::toInt(StructureType::ROAD);
    playerID1 = 0;
    playerID2 = 1;
    playerID3 = 2;


    DoganConfig config1 = DoganConfigBuilder().build();
    std::array<int, 2> generalConfig{2, 2};
    std::vector<int> numberLocations{2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12};
    DoganConfig config2 = DoganConfigBuilder()
                          .setNumberConfig(generalConfig)
                          .setNumberLocations(numberLocations)
                          .setResourceConfig(generalConfig)
                          .setResources({4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4})
                          .setDevelopmentConfig(generalConfig)
                          .setDevelopmentLocations(
                            {DevelopmentType::TAKETWO, DevelopmentType::BUILDROAD, DevelopmentType::SOLDIER, DevelopmentType::MONOPOLY, DevelopmentType::VICPOINT}
                          )
                          .setDevelopmentCount({1, 1, 1, 1, 1})
                          .build();
    nGame = DoganGame(config1);
    iGame = DoganGame(config2);
    iGame.addPlayer("Dogan1", playerID1);
    iGame.addPlayer("Dogan2", playerID2);
    iGame.addPlayer("Dogan3", playerID3);
  }

  DoganGame nGame;
  DoganGame iGame;
  
  int villageInt;
  int roadInt;
  int playerID1;
  int playerID2;
  int playerID3;
};

TEST_F(GameFixture, AddExistingPlayersTest) {
  nGame.addPlayer("DoganPlayer", 0);
  EXPECT_THROW({ nGame.addPlayer("", 0); }, SamePlayerException);
}

TEST_F(GameFixture, BuildStructuresTest) {
    // Buildings
  iGame.buildStructure(playerID1, villageInt, {1, 1}, "NW", {0, 0, 0, 0, 0});
  EXPECT_EQ((iGame.hasStructure({1, 1}, "NW", villageInt)), true);
  EXPECT_EQ((iGame.hasStructure({1, 0}, "S", villageInt)), true);
  EXPECT_EQ((iGame.hasStructure({0, 1}, "NE", villageInt)), true);

  // Roads
  iGame.buildStructure(playerID1, roadInt, {1, 0}, "SE", {0, 0, 0, 0, 0});
  EXPECT_EQ((iGame.hasStructure({1, 0}, "SE", roadInt)), true);
  EXPECT_EQ((iGame.hasStructure({1, 1}, "NW", roadInt)), true);

  // Edge Building
  iGame.buildStructure(playerID1, villageInt, {0, 0}, "NW", {0, 0, 0, 0, 0});
  EXPECT_EQ((iGame.hasStructure({0, 0}, "NW", villageInt)), true);
  EXPECT_EQ((iGame.hasStructure({-1, 0}, "S", villageInt)), false);

  // Edge Road
  iGame.buildStructure(playerID1, roadInt, {0, 0}, "NW", {0, 0, 0, 0, 0});
  EXPECT_EQ((iGame.hasStructure({0, 0}, "NW", roadInt)), true);
  EXPECT_EQ((iGame.hasStructure({-1, 0}, "SE", roadInt)), false);
}

TEST_F(GameFixture, EmptyStructureTest) {

    // Buildings
  EXPECT_EQ((iGame.hasStructure({1, 1}, "NW", villageInt)), false);
  EXPECT_EQ((iGame.hasStructure({1, 0}, "SE", villageInt)), false);
  EXPECT_EQ((iGame.hasStructure({0, 1}, "NE", villageInt)), false);

  // Roads
  EXPECT_EQ((iGame.hasStructure({1, 0}, "SE", roadInt)), false);
  EXPECT_EQ((iGame.hasStructure({1, 1}, "NW", roadInt)), false);
}

TEST_F(GameFixture, TradeTest) {
  iGame.giveResources(0, {4, 4, 4, 4, 4});
  iGame.giveResources(1, {4, 4, 4, 4, 4});
  iGame.tradeResources(0, {0, 1, 2, 3, 4}, 1, {0, 0, 0 , 0, 0});

  std::array<int, 5> expected1 = {4, 3, 2, 1, 0};
  std::array<int, 5> expected2 = {4, 5, 6, 7, 8};

  EXPECT_EQ((iGame.getResourceCount(0)), expected1);
  EXPECT_EQ((iGame.getResourceCount(1)), expected2);
}

TEST_F(GameFixture, BuildExistingStructuresTest) {

    // Buildings
  iGame.buildStructure(playerID1, villageInt, {1, 1}, "NW", {0, 0, 0, 0, 0});
  EXPECT_THROW(
      {
        iGame.buildStructure(playerID1, villageInt, {1, 1}, "NW", {0, 0, 0, 0, 0});
      },
      SameStructureException);
  EXPECT_THROW(
      {
        iGame.buildStructure(playerID2, villageInt, {1, 0}, "S", {0, 0, 0, 0, 0});
      },
      SameStructureException);

    // Roads
    iGame.buildStructure(playerID1, roadInt, {1, 0}, "SE", {0, 0, 0, 0, 0});
    EXPECT_THROW(
        {
          iGame.buildStructure(playerID1, roadInt, {1, 0}, "SE", {0, 0, 0, 0, 0});
        },
        SameStructureException);
    
    EXPECT_THROW(
        {
          iGame.buildStructure(playerID2, roadInt, {1, 1}, "NW", {0, 0, 0, 0, 0});
        },
        SameStructureException);
}

TEST_F(GameFixture, DistributeResourcesTest) {
  iGame.buildStructure(playerID1, villageInt, {0, 0}, "N", {0, 0, 0, 0, 0});
  int rolledDice = 2;
  iGame.distributeResources(rolledDice);
  std::array<int, 5> actual = iGame.getResourceCount(playerID1);
  std::array<int, 5> expected{0, 0, 0, 0, 1};
  EXPECT_EQ(actual, expected);
}


TEST_F(GameFixture, StartPhaseTest) {
  iGame.buildStructure(playerID1, villageInt, {1, 1}, "N", {0, 0, 0, 0, 0});
  iGame.giveResources(playerID1, {1, 0, 0, 0, 0});
  iGame.buildStructure(playerID1, roadInt, {1, 0}, "NE", {0, 0, 0, 0, 0});
}

TEST_F(GameFixture, PurchaseDevelopmentCardTest) {
  std::array<int, 5> expected{0, 0, 0, 0, 0};
  for(int i = 0; i < 5; i++) {
    iGame.purchaseDevelopmentCard(playerID1, {0, 0, 0, 0, 0});
    expected[i] = 1;
    std::array<int, 5> actual = iGame.getDevelopmentCount(playerID1);
    EXPECT_EQ(actual, expected);
  }
}

TEST_F(GameFixture, UseDevelopmentCardVictoryTest) {
  for(int i = 0; i < 5; i++) {
    iGame.purchaseDevelopmentCard(playerID1, {0, 0, 0, 0, 0});
  }
  EXPECT_EQ(iGame.getVictoryPoints(playerID1), 1);
  
}
TEST_F(GameFixture, UseDevelopmentCardMonopolyTest) {
  for(int i = 0; i < 5; i++) {
    iGame.purchaseDevelopmentCard(playerID1, {0, 0, 0, 0, 0});
  }
  iGame.giveResources(playerID2, {5, 4, 3, 2, 1});
  iGame.giveResources(playerID3, {5, 4, 3, 2, 1});
  ASSERT_EQ(iGame.getResourceCount(playerID1), (std::array<int, 5>{0, 0, 0, 0, 0}));
  ASSERT_EQ(iGame.getResourceCount(playerID2), (std::array<int, 5>{5, 4, 3, 2, 1}));
  ASSERT_EQ(iGame.getResourceCount(playerID3), (std::array<int, 5>{5, 4, 3, 2, 1}));
  iGame.useMonopolyDevelopmentCard(playerID1, ResourceType::WOOD);
  
  EXPECT_EQ(iGame.getResourceCount(playerID1), (std::array<int, 5>{10, 0, 0, 0, 0}));
  EXPECT_EQ(iGame.getResourceCount(playerID2), (std::array<int, 5>{0, 4, 3, 2, 1}));
  EXPECT_EQ(iGame.getResourceCount(playerID3), (std::array<int, 5>{0, 4, 3, 2, 1}));

}



TEST_F(GameFixture, CircularEconomyTest) {
  ASSERT_EQ(iGame.getResourceCount(-1), (std::array<int, 5>{19, 19, 19, 19, 19}));
  iGame.giveResources(playerID1, {4, 4, 4, 4, 4});
  iGame.buildStructure(playerID1, villageInt, {1, 1}, "NW", {0, 1, 2, 3, 4});
  
  std::array<int, 5> expected{19, 20, 21, 22, 23};
  EXPECT_EQ(iGame.getResourceCount(-1), expected);
}
