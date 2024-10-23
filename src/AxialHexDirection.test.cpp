#include "AxialHexDirection.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using Direction = AxialHexDirection::Direction;

TEST(GetSecondDegreeVertexTestSuite, getNorthSecondDegreeVertexTest) {
  Direction d = Direction::NORTH;
  std::array<std::array<AxialHexDirection::Direction, 2>, 2> expected = {
      {{Direction::NORTHEAST, Direction::NORTHWEST},
       {Direction::NORTHWEST, Direction::NORTHEAST}}};
  auto representations = AxialHexDirection::getSecondDegreeVertex(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetSecondDegreeVertexTestSuite, getNorthEastSecondDegreeVertexTest) {
  Direction d = Direction::NORTHEAST;
  std::array<std::array<AxialHexDirection::Direction, 2>, 2> expected = {
      {{Direction::NORTHEAST, Direction::SOUTHEAST},
       {Direction::EAST, Direction::NORTH}}};
  auto representations = AxialHexDirection::getSecondDegreeVertex(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetSecondDegreeVertexTestSuite, getSouthEastSecondDegreeVertexTest) {
  Direction d = Direction::SOUTHEAST;
  std::array<std::array<AxialHexDirection::Direction, 2>, 2> expected = {
      {{Direction::SOUTHEAST, Direction::NORTHEAST},
       {Direction::EAST, Direction::SOUTH}}};
  auto representations = AxialHexDirection::getSecondDegreeVertex(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetDistantAdjacentEdgeToEdgeDirectionsTestSuite,
     getNorthEastDistantAdjacentEdgeToEdgeDirectionsTest) {
  Direction d = Direction::NORTHEAST;
  std::array<std::array<AxialHexDirection::Direction, 2>, 4> expected = {
      {{Direction::NORTHEAST, Direction::WEST},
       {Direction::NORTHWEST, Direction::EAST},
       {Direction::NORTHEAST, Direction::SOUTHEAST},
       {Direction::EAST, Direction::NORTHWEST}}};
  auto representations =
      AxialHexDirection::getDistantAdjacentEdgeToEdgeDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetDistantAdjacentEdgeToEdgeDirectionsTestSuite,
     getEastDistantAdjacentEdgeToEdgeDirectionsTest) {
  Direction d = Direction::EAST;
  std::array<std::array<AxialHexDirection::Direction, 2>, 4> expected = {
      {{Direction::EAST, Direction::NORTHWEST},
       {Direction::NORTHEAST, Direction::SOUTHEAST},
       {Direction::EAST, Direction::SOUTHWEST},
       {Direction::SOUTHEAST, Direction::NORTHEAST}}};
  auto representations =
      AxialHexDirection::getDistantAdjacentEdgeToEdgeDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetDistantAdjacentEdgeToEdgeDirectionsTestSuite,
     getSouthEastDistantAdjacentEdgeToEdgeDirectionsTest) {
  Direction d = Direction::SOUTHEAST;
  std::array<std::array<AxialHexDirection::Direction, 2>, 4> expected = {
      {{Direction::EAST, Direction::SOUTHWEST},
       {Direction::SOUTHEAST, Direction::NORTHEAST},
       {Direction::SOUTHEAST, Direction::WEST},
       {Direction::SOUTHWEST, Direction::EAST}}};
  auto representations =
      AxialHexDirection::getDistantAdjacentEdgeToEdgeDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetLocalAdjacentEdgeToEdgeDirectionsTestSuite,
     getNorthEastLocalAdjacentEdgeToEdgeDirectionsTest) {
  Direction d = Direction::NORTHEAST;
  std::array<AxialHexDirection::Direction, 2> expected = {
      {Direction::NORTHWEST, Direction::EAST}};
  auto representations =
      AxialHexDirection::getLocalAdjacentEdgeToEdgeDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetLocalAdjacentEdgeToEdgeDirectionsTestSuite,
     getEastLocalAdjacentEdgeToEdgeDirectionsTest) {
  Direction d = Direction::EAST;
  std::array<AxialHexDirection::Direction, 2> expected = {
      {Direction::NORTHEAST, Direction::SOUTHEAST}};
  auto representations =
      AxialHexDirection::getLocalAdjacentEdgeToEdgeDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetLocalAdjacentEdgeToEdgeDirectionsTestSuite,
     getSouthEastLocalAdjacentEdgeToEdgeDirectionsTest) {
  Direction d = Direction::SOUTHEAST;
  std::array<AxialHexDirection::Direction, 2> expected = {
      {Direction::EAST, Direction::SOUTHWEST}};
  auto representations =
      AxialHexDirection::getLocalAdjacentEdgeToEdgeDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetAdjacentEdgeToVertexDirectionsTestSuite,
     getNorthAdjacentEdgeToVertexDirectionsTest) {
  Direction d = Direction::NORTH;
  edgeRepresentation expected = {
      {Direction::NORTHWEST, Direction::NORTHEAST}};
  auto representations =
      AxialHexDirection::getAdjacentEdgeToVertexDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetAdjacentEdgeToVertexDirectionsTestSuite,
     getNorthEastAdjacentEdgeToVertexDirectionsTest) {
  Direction d = Direction::NORTHEAST;
  edgeRepresentation expected = {{Direction::NORTHEAST, Direction::EAST}};
  auto representations =
      AxialHexDirection::getAdjacentEdgeToVertexDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetAdjacentEdgeToVertexDirectionsTestSuite,
     getSouthEastAdjacentEdgeToVertexDirectionsTest) {
  Direction d = Direction::SOUTHEAST;
  edgeRepresentation expected = {{Direction::SOUTHEAST, Direction::EAST}};
  auto representations =
      AxialHexDirection::getAdjacentEdgeToVertexDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetAdjacentVertexToVertexDirectionsTestSuite,
     getNorthAdjacentVertexToVertexDirectionsTest) {
  Direction d = Direction::NORTH;
  vertexRepresentation expected = {
      {Direction::NORTHWEST, Direction::NORTHEAST}};
  auto representations =
      AxialHexDirection::getAdjacentVertexToVertexDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetAdjacentVertexToVertexDirectionsTestSuite,
     getNorthEastAdjacentVertexToVertexDirectionsTest) {
  Direction d = Direction::NORTHEAST;
  vertexRepresentation expected = {
      {Direction::NORTH, Direction::SOUTHEAST}};
  auto representations =
      AxialHexDirection::getAdjacentVertexToVertexDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(GetAdjacentVertexToVertexDirectionsTestSuite,
     getSouthEastAdjacentVertexToVertexDirectionsTest) {
  Direction d = Direction::SOUTHEAST;
  vertexRepresentation expected = {
      {Direction::SOUTH, Direction::NORTHEAST}};
  auto representations =
      AxialHexDirection::getAdjacentVertexToVertexDirections(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

TEST(getVertexRepresentationsTestSuite, getNorthVertexRepresentationsTest) {
  Direction d = Direction::NORTH;
  std::array<vertexRepresentation, 3> expected = {
      {{Direction::NONE, Direction::NORTH},
       {Direction::NORTHWEST, Direction::SOUTHEAST},
       {Direction::NORTHEAST, Direction::SOUTHWEST}}};
  auto representations = AxialHexDirection::getAllVertexRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(getVertexRepresentationsTestSuite, getNorthEastVertexRepresentationsTest) {
  Direction d = Direction::NORTHEAST;
  std::array<vertexRepresentation, 3> expected = {
      {{Direction::NONE, Direction::NORTHEAST},
       {Direction::NORTHEAST, Direction::SOUTH},
       {Direction::EAST, Direction::NORTHWEST}}};
  auto representations = AxialHexDirection::getAllVertexRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(getVertexRepresentationsTestSuite, getSouthEastVertexRepresentationsTest) {
  Direction d = Direction::SOUTHEAST;
  std::array<vertexRepresentation, 3> expected = {
      {{Direction::NONE, Direction::SOUTHEAST},
       {Direction::SOUTHEAST, Direction::NORTH},
       {Direction::EAST, Direction::SOUTHWEST}}};
  auto representations = AxialHexDirection::getAllVertexRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(getVertexRepresentationsTestSuite, getSouthVertexRepresentationsTest) {
  Direction d = Direction::SOUTH;
  std::array<vertexRepresentation, 3> expected = {
      {{Direction::NONE, Direction::SOUTH},
       {Direction::SOUTHEAST, Direction::NORTHWEST},
       {Direction::SOUTHWEST, Direction::NORTHEAST}}};
  auto representations = AxialHexDirection::getAllVertexRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(getVertexRepresentationsTestSuite, getSouthWestVertexRepresentationsTest) {
  Direction d = Direction::SOUTHWEST;
  std::array<vertexRepresentation, 3> expected = {
      {{Direction::NONE, Direction::SOUTHWEST},
       {Direction::SOUTHWEST, Direction::NORTH},
       {Direction::WEST, Direction::SOUTHEAST}}};
  auto representations = AxialHexDirection::getAllVertexRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(getVertexRepresentationsTestSuite, getNorthWestVertexRepresentationsTest) {
  Direction d = Direction::NORTHWEST;
  std::array<vertexRepresentation, 3> expected = {
      {{Direction::NONE, Direction::NORTHWEST},
       {Direction::NORTHWEST, Direction::SOUTH},
       {Direction::WEST, Direction::NORTHEAST}}};
  auto representations = AxialHexDirection::getAllVertexRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}