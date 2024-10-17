#include "DoganCell.h"
#include <gtest/gtest.h>

class CellFixture : public ::testing::Test {
protected:
  void SetUp() override {}
  DoganCell nCell{false, (0, 0), 5, ResourceType::BRICK};
  DoganCell rCell{true, (100, 100), 2, ResourceType::OTHER};
};