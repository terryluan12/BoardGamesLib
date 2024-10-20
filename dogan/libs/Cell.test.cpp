#include "Cell.h"
#include <gtest/gtest.h>

using namespace Dogan;
class CellFixture : public ::testing::Test {
protected:
  void SetUp() override {}
  Cell nCell{false, (0, 0), 5, ResourceType::BRICK};
  Cell rCell{true, (100, 100), 2, ResourceType::OTHER};
};