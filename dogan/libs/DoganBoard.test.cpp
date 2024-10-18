#include "DoganBoard.h"
#include "DoganConfig.h"
#include "DoganConfigBuilder.h"
#include "DoganExceptions.h"
#include <gtest/gtest.h>

class BoardFixture : public ::testing::Test {
protected:
  void SetUp() override {
    DoganConfig config = DoganConfig();
    board = DoganBoard(config);
  }
  DoganBoard board;
};

TEST(BoardTest, AddDuplicateCellTest) {
  DoganConfigBuilder config = DoganConfigBuilder();
  config.setTileLocations({{0, 0}, {0, 0}});
  EXPECT_THROW({ DoganBoard board = DoganBoard(config.build()); },
               std::invalid_argument);
}
