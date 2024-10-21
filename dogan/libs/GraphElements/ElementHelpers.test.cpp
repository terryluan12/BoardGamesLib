#include "ElementHelpers.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>

using namespace Dogan;

TEST(ElementHelpersTest, getNorthVertexRepresentationsTest) {
  // Test NORTH
  std::pair<Coordinate2D, Direction> dvp = {{1, 1}, Direction::NORTH};
  std::vector<std::pair<Coordinate2D, Direction>> expected = {
      {{1, 1}, Direction::NORTH}, {{1, 0}, Direction::SOUTHEAST},
      {{2, 0}, Direction::SOUTHWEST}};
  auto representations = getAllVertexRepresentations(dvp);
  EXPECT_THAT(expected, ::testing::UnorderedElementsAreArray(representations));
}
TEST(ElementHelpersTest, getNorthEastVertexRepresentationsTest) {
  // Test NORTH
  std::pair<Coordinate2D, Direction> dvp = {{1, 1}, Direction::NORTHEAST};
  std::vector<std::pair<Coordinate2D, Direction>> expected = {
      {{1, 1}, Direction::NORTHEAST}, {{2, 0}, Direction::SOUTH},
      {{2, 1}, Direction::NORTHWEST}};
  auto representations = getAllVertexRepresentations(dvp);
  EXPECT_THAT(expected, ::testing::UnorderedElementsAreArray(representations));
}
TEST(ElementHelpersTest, getSouthEastVertexRepresentationsTest) {
  std::pair<Coordinate2D, Direction> dvp = {{1, 1}, Direction::SOUTHEAST};
  std::vector<std::pair<Coordinate2D, Direction>> expected = {
      {{2, 1}, Direction::SOUTHWEST}, {{1, 1}, Direction::SOUTHEAST},
      {{1, 2}, Direction::NORTH}};
  auto representations = getAllVertexRepresentations(dvp);
  EXPECT_THAT(expected, ::testing::UnorderedElementsAreArray(representations));
}
TEST(ElementHelpersTest, getSouthVertexRepresentationsTest) {
  std::pair<Coordinate2D, Direction> dvp = {{1, 1}, Direction::SOUTH};
  std::vector<std::pair<Coordinate2D, Direction>> expected = {
      {{0, 2}, Direction::NORTHEAST}, {{1, 1}, Direction::SOUTH},
      {{1, 2}, Direction::NORTHWEST}};
  auto representations = getAllVertexRepresentations(dvp);
  EXPECT_THAT(expected, ::testing::UnorderedElementsAreArray(representations));
}
TEST(ElementHelpersTest, getSouthWestVertexRepresentationsTest) {
  std::pair<Coordinate2D, Direction> dvp = {{1, 1}, Direction::SOUTHWEST};
  std::vector<std::pair<Coordinate2D, Direction>> expected = {
      {{0, 2}, Direction::NORTH}, {{1, 1}, Direction::SOUTHWEST},
      {{0, 1}, Direction::SOUTHEAST}};
  auto representations = getAllVertexRepresentations(dvp);
  EXPECT_THAT(expected, ::testing::UnorderedElementsAreArray(representations));
}
TEST(ElementHelpersTest, getNorthWestVertexRepresentationsTest) {
  std::pair<Coordinate2D, Direction> dvp = {{1, 1}, Direction::NORTHWEST};
  std::vector<std::pair<Coordinate2D, Direction>> expected = {
      {{1, 0}, Direction::SOUTH}, {{1, 1}, Direction::NORTHWEST},
      {{0, 1}, Direction::NORTHEAST}};
  auto representations = getAllVertexRepresentations(dvp);
  EXPECT_THAT(expected, ::testing::UnorderedElementsAreArray(representations));
}