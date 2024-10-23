#include "ElementHelpers.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>

using namespace Dogan;

TEST(ElementHelpersTest, getNorthVertexRepresentationsTest) {
  Direction d = Direction::NORTH;
  std::array<std::pair<Direction, Direction>, 3> expected = {{
      {Direction::NONE, Direction::NORTH}, 
      {Direction::NORTHWEST, Direction::SOUTHEAST},
      {Direction::NORTHEAST, Direction::SOUTHWEST}}};
  auto representations = getAllVertexRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(ElementHelpersTest, getNorthEastVertexRepresentationsTest) {
  Direction d = Direction::NORTHEAST;
  std::array<std::pair<Direction, Direction>, 3> expected = {{
      {Direction::NONE, Direction::NORTHEAST}, 
      {Direction::NORTHEAST, Direction::SOUTH},
      {Direction::EAST, Direction::NORTHWEST}}};
  auto representations = getAllVertexRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(ElementHelpersTest, getSouthEastVertexRepresentationsTest) {
  Direction d = Direction::SOUTHEAST;
  std::array<std::pair<Direction, Direction>, 3> expected = {{
      {Direction::NONE, Direction::SOUTHEAST}, 
      {Direction::SOUTHEAST, Direction::NORTH},
      {Direction::EAST, Direction::SOUTHWEST}
      }};
  auto representations = getAllVertexRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(ElementHelpersTest, getSouthVertexRepresentationsTest) {
  Direction d = Direction::SOUTH;
  std::array<std::pair<Direction, Direction>, 3> expected = {{
      {Direction::NONE, Direction::SOUTH}, 
      {Direction::SOUTHEAST, Direction::NORTHWEST}, 
      {Direction::SOUTHWEST, Direction::NORTHEAST}}};
  auto representations = getAllVertexRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(ElementHelpersTest, getSouthWestVertexRepresentationsTest) {
  Direction d = Direction::SOUTHWEST;
  std::array<std::pair<Direction, Direction>, 3> expected = {{
      {Direction::NONE, Direction::SOUTHWEST},
      {Direction::SOUTHWEST, Direction::NORTH},
      {Direction::WEST, Direction::SOUTHEAST}}};
  auto representations = getAllVertexRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(ElementHelpersTest, getNorthWestVertexRepresentationsTest) {
  Direction d = Direction::NORTHWEST;
  std::array<std::pair<Direction, Direction>, 3> expected = {{
      {Direction::NONE, Direction::NORTHWEST},
      {Direction::NORTHWEST, Direction::SOUTH}, 
      {Direction::WEST, Direction::NORTHEAST}}};
  auto representations = getAllVertexRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}