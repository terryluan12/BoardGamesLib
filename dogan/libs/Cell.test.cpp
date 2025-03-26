#include "Cell.h"
#include "Board.h"
#include "Coordinate.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// class MockBoard : public Board {
//   public:
//     MOCK_METHOD(bool, hasTile, (Coordinate2D c), (override));
// };

using namespace Dogan;
// TODO: Upgrade once using Edge and Vertex Objects
// TEST(CellTest, UpgradeCityTest) {

//   MockBoard board;

//   EXPECT_CALL(board, hasTile(::testing::Eq(Coordinate2D{0,
//   0}))).WillOnce(::testing::Return(true));

//   Cell cell{&board, false, {0, 0}, 0, ResourceType::BRICK};
//   cell.buildStructure(0, Direction::NORTHWEST,
//                       std::make_shared<Building>(0, StructureType::VILLAGE),
//                       false);
//   cell.upgradeToCity(0, Direction::NORTHWEST);
// }