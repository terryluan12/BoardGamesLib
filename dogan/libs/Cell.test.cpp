#include "Cell.h"
#include <gtest/gtest.h>

using namespace Dogan;
TEST(CellTest, UpgradeCityTest) {
    Cell cell{false, {0, 0}, 0, ResourceType::BRICK};
    cell.buildStructure(0, Direction::NORTHWEST, std::make_shared<Building>(0, StructureType::VILLAGE), false);
    cell.upgradeToCity(0, Direction::NORTHWEST);
}