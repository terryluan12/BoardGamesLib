#include <gtest/gtest.h>
#include "DoganGame.h"
#include "DoganConfigBuilder.h"
#include "DoganExceptions.h"

class GameFixture : public ::testing::Test {
    protected:
    void SetUp() override {
        DoganConfig config1 = DoganConfigBuilder().build();
        DoganConfig config2 = DoganConfigBuilder().build();
        nGame = DoganGame(config1);
        iGame = DoganGame(config2);
        iGame.addPlayer("Dogan1", 0);
        iGame.addPlayer("Dogan2", 1);
        iGame.addPlayer("Dogan3", 2);
    }

    DoganGame nGame;
    DoganGame iGame;
};

TEST_F(GameFixture, AddExistingPlayersTest) {
    nGame.addPlayer("DoganPlayer", 0);
    EXPECT_THROW({
        nGame.addPlayer("", 0);
    }, SamePlayerException);
}
TEST_F(GameFixture, BuildSameStructureTwice) {
    iGame.buildStructure(0, 0, {1, 1}, "NW", {0, 0, 0, 0, 0});
    EXPECT_THROW({
        iGame.buildStructure(0, 0, {1, 1}, "NW", {0, 0, 0, 0, 0});
    }, SameStructureException);
    EXPECT_THROW({
        iGame.buildStructure(0, 0, {1, 0}, "SE", {0, 0, 0, 0, 0});
    }, SameStructureException);
    
}

TEST_F(GameFixture, StartPhaseTest) {
    iGame.buildStructure(0, 0, {1, 1}, "N", {0, 0, 0, 0, 0});
    iGame.giveResources(0, {1, 0, 0, 0, 0});
    iGame.buildStructure(0, 2, {1, 0}, "NE", {0, 0, 0, 0, 0});
}