#include "AxialHexDirection.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using Direction=AxialHexDirection::Direction;

TEST(GetSecondDegreeVertex, getNorthSecondDegreeVertexTest) {
  Direction d = Direction::NORTH;
  std::array<std::array<AxialHexDirection::Direction, 2>, 2> expected = {{
      {Direction::NORTHEAST, Direction::NORTHWEST},
      {Direction::NORTHWEST, Direction::NORTHEAST}}};
  auto representations = AxialHexDirection::getSecondDegreeVertex(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}


TEST(GetSecondDegreeVertex, getNorthEastSecondDegreeVertexTest) {
  Direction d = Direction::NORTHEAST;
  std::array<std::array<AxialHexDirection::Direction, 2>, 2> expected = {{
      {Direction::NORTHEAST, Direction::SOUTHEAST},
      {Direction::EAST, Direction::NORTH}}};
  auto representations = AxialHexDirection::getSecondDegreeVertex(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetSecondDegreeVertex, getSouthEastSecondDegreeVertexTest) {
  Direction d = Direction::SOUTHEAST;
  std::array<std::array<AxialHexDirection::Direction, 2>, 2> expected = {{
      {Direction::SOUTHEAST, Direction::NORTHEAST},
      {Direction::EAST, Direction::SOUTH}}};
  auto representations = AxialHexDirection::getSecondDegreeVertex(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetSecondDegreeVertex, getNorthEastDistantAdjacentEdgeToEdgeDirectionsTest) {
  Direction d = Direction::NORTHEAST;
  std::array<std::array<AxialHexDirection::Direction, 2>, 4> expected = {{
      {Direction::NORTHEAST, Direction::WEST},
      {Direction::NORTHWEST, Direction::EAST},
      {Direction::NORTHEAST, Direction::SOUTHEAST},
      {Direction::EAST, Direction::NORTHWEST}}};
  auto representations = AxialHexDirection::getDistantAdjacentEdgeToEdgeDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetSecondDegreeVertex, getEastDistantAdjacentEdgeToEdgeDirectionsTest) {
  Direction d = Direction::EAST;
  std::array<std::array<AxialHexDirection::Direction, 2>, 4> expected = {{
      {Direction::EAST, Direction::NORTHWEST},
      {Direction::NORTHEAST, Direction::SOUTHEAST},
      {Direction::EAST, Direction::SOUTHWEST},
      {Direction::SOUTHEAST, Direction::NORTHEAST}}};
  auto representations = AxialHexDirection::getDistantAdjacentEdgeToEdgeDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetSecondDegreeVertex, getSouthEastDistantAdjacentEdgeToEdgeDirectionsTest) {
  Direction d = Direction::SOUTHEAST;
  std::array<std::array<AxialHexDirection::Direction, 2>, 4> expected = {{
      {Direction::EAST, Direction::SOUTHWEST},
      {Direction::SOUTHEAST, Direction::NORTHEAST},
      {Direction::SOUTHEAST, Direction::WEST},
      {Direction::SOUTHWEST, Direction::EAST}}};
  auto representations = AxialHexDirection::getDistantAdjacentEdgeToEdgeDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetSecondDegreeVertex, getNorthEastLocalAdjacentEdgeToEdgeDirectionsTest) {
  Direction d = Direction::NORTHEAST;
  std::array<AxialHexDirection::Direction, 2> expected = {
      {Direction::NORTHWEST, Direction::EAST}};
  auto representations = AxialHexDirection::getLocalAdjacentEdgeToEdgeDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetSecondDegreeVertex, getEastLocalAdjacentEdgeToEdgeDirectionsTest) {
  Direction d = Direction::EAST;
  std::array<AxialHexDirection::Direction, 2> expected = {
      {Direction::NORTHEAST, Direction::SOUTHEAST}};
  auto representations = AxialHexDirection::getLocalAdjacentEdgeToEdgeDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetSecondDegreeVertex, getSouthEastLocalAdjacentEdgeToEdgeDirectionsTest) {
  Direction d = Direction::SOUTHEAST;
  std::array<AxialHexDirection::Direction, 2> expected = {
      {Direction::EAST, Direction::SOUTHWEST}};
  auto representations = AxialHexDirection::getLocalAdjacentEdgeToEdgeDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetSecondDegreeVertex, getNorthAdjacentEdgeToVertexDirectionsTest) {
  Direction d = Direction::NORTH;
  std::array<Direction, 2>  expected = {
      {Direction::NORTHWEST, Direction::NORTHEAST}};
  auto representations = AxialHexDirection::getAdjacentEdgeToVertexDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetSecondDegreeVertex, getNorthEastAdjacentEdgeToVertexDirectionsTest) {
  Direction d = Direction::NORTHEAST;
  std::array<Direction, 2>  expected = {
      {Direction::NORTHEAST, Direction::EAST}};
  auto representations = AxialHexDirection::getAdjacentEdgeToVertexDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetSecondDegreeVertex, getSouthEastAdjacentEdgeToVertexDirectionsTest) {
  Direction d = Direction::SOUTHEAST;
  std::array<Direction, 2>  expected = {
      {Direction::SOUTHEAST, Direction::EAST}};
  auto representations = AxialHexDirection::getAdjacentEdgeToVertexDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetSecondDegreeVertex, getNorthAdjacentVertexToVertexDirectionsTest) {
  Direction d = Direction::NORTH;
  std::array<Direction, 2>  expected = {
      {Direction::NORTHWEST, Direction::NORTHEAST}};
  auto representations = AxialHexDirection::getAdjacentVertexToVertexDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetSecondDegreeVertex, getNorthEastAdjacentVertexToVertexDirectionsTest) {
  Direction d = Direction::NORTHEAST;
  std::array<Direction, 2>  expected = {
      {Direction::NORTH, Direction::SOUTHEAST}};
  auto representations = AxialHexDirection::getAdjacentVertexToVertexDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetSecondDegreeVertex, getSouthEastAdjacentVertexToVertexDirectionsTest) {
  Direction d = Direction::SOUTHEAST;
  std::array<Direction, 2>  expected = {
      {Direction::SOUTH, Direction::NORTHEAST}};
  auto representations = AxialHexDirection::getAdjacentVertexToVertexDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}