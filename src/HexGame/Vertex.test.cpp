#include "Vertex.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

// ------------------------- VertexGetLAVTestSuite ------------------------- //

TEST(VertexGetLAVTestSuite, GetNorthLAVerticesTest) {
  HexDirection d = HexDirection::NORTH;
  std::array<HexPath, 2> expected = {
      {{HexDirection::NONE, HexDirection::NORTHWEST},
       {HexDirection::NONE, HexDirection::NORTHEAST}}};
  auto representations = Vertex::getLocalAdjacentVertices(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(VertexGetLAVTestSuite, GetNorthEastLAVerticesTest) {
  HexDirection d = HexDirection::NORTHEAST;
  std::array<HexPath, 2> expected = {
      {{HexDirection::NONE, HexDirection::NORTH},
       {HexDirection::NONE, HexDirection::SOUTHEAST}}};
  auto representations = Vertex::getLocalAdjacentVertices(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(VertexGetLAVTestSuite, GetSouthEastLAVerticesTest) {
  HexDirection d = HexDirection::SOUTHEAST;
  std::array<HexPath, 2> expected = {
      {{HexDirection::NONE, HexDirection::SOUTH},
       {HexDirection::NONE, HexDirection::NORTHEAST}}};
  auto representations = Vertex::getLocalAdjacentVertices(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

// ------------------------- VertexGetDAVTestSuite ------------------------- //

TEST(VertexGetDAVTestSuite, GetNorthDAVertexTest) {
  HexDirection d = HexDirection::NORTH;
  std::array<HexPath, 2> expected = {
      {{HexDirection::NORTHEAST, HexDirection::NORTHWEST},
       {HexDirection::NORTHWEST, HexDirection::NORTHEAST}}};
  auto representations = Vertex::getDistantAdjacentVertex(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(VertexGetDAVTestSuite, GetNorthEastDAVertexTest) {
  HexDirection d = HexDirection::NORTHEAST;
  std::array<HexPath, 2> expected = {
      {{HexDirection::NORTHEAST, HexDirection::SOUTHEAST},
       {HexDirection::EAST, HexDirection::NORTH}}};
  auto representations = Vertex::getDistantAdjacentVertex(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(VertexGetDAVTestSuite, GetSouthEastDAVertexTest) {
  HexDirection d = HexDirection::SOUTHEAST;
  std::array<HexPath, 2> expected = {
      {{HexDirection::SOUTHEAST, HexDirection::NORTHEAST},
       {HexDirection::EAST, HexDirection::SOUTH}}};
  auto representations = Vertex::getDistantAdjacentVertex(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

// ------------------------- VertexGetLAETestSuite ------------------------- //

TEST(VertexGetLAETestSuite, GetNorthLAEdgesTest) {
  HexDirection d = HexDirection::NORTH;
  std::array<HexPath, 2> expected = {
      {{HexDirection::NONE, HexDirection::NORTHWEST},
       {HexDirection::NONE, HexDirection::NORTHEAST}}};
  auto representations = Vertex::getLocalAdjacentEdges(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(VertexGetLAETestSuite, GetNorthEastLAEdgesTest) {
  HexDirection d = HexDirection::NORTHEAST;
  std::array<HexPath, 2> expected = {
      {{HexDirection::NONE, HexDirection::NORTHEAST},
       {HexDirection::NONE, HexDirection::EAST}}};
  auto representations = Vertex::getLocalAdjacentEdges(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(VertexGetLAETestSuite, GetSouthEastLAEdgesTest) {
  HexDirection d = HexDirection::SOUTHEAST;
  std::array<HexPath, 2> expected = {
      {{HexDirection::NONE, HexDirection::SOUTHEAST},
       {HexDirection::NONE, HexDirection::EAST}}};
  auto representations = Vertex::getLocalAdjacentEdges(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

// ------------------------- VertexGetDAETestSuite ------------------------- //

TEST(VertexGetDAETestSuite, GetNorthDAEdgeTest) {
  HexDirection d = HexDirection::NORTH;
  std::array<HexPath, 2> expected = {
      {{HexDirection::NORTHWEST, HexDirection::EAST},
       {HexDirection::NORTHEAST, HexDirection::WEST}}};
  auto representations = Vertex::getDistantAdjacentEdge(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(VertexGetDAETestSuite, GetNorthEastDAEdgeTest) {
  HexDirection d = HexDirection::NORTHEAST;
  std::array<HexPath, 2> expected = {
      {{HexDirection::NORTHEAST, HexDirection::SOUTHEAST},
       {HexDirection::EAST, HexDirection::NORTHWEST}}};
  auto representations = Vertex::getDistantAdjacentEdge(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(VertexGetDAETestSuite, GetSouthEastDAEdgeTest) {
  HexDirection d = HexDirection::SOUTHEAST;
  std::array<HexPath, 2> expected = {
      {{HexDirection::EAST, HexDirection::SOUTHWEST},
       {HexDirection::SOUTHEAST, HexDirection::NORTHEAST}}};
  auto representations = Vertex::getDistantAdjacentEdge(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

// ------------------------- GetAllVertexRepsTestSuite -------------------------
// //

TEST(GetAllVertexRepsTestSuite, GetAllNorthVertexRepsTest) {
  HexDirection d = HexDirection::NORTH;
  std::array<HexPath, 3> expected = {
      {{HexDirection::NONE, HexDirection::NORTH},
       {HexDirection::NORTHWEST, HexDirection::SOUTHEAST},
       {HexDirection::NORTHEAST, HexDirection::SOUTHWEST}}};
  auto representations = Vertex::getAllVertexRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(GetAllVertexRepsTestSuite, GetAllNorthEastVertexRepsTest) {
  HexDirection d = HexDirection::NORTHEAST;
  std::array<HexPath, 3> expected = {
      {{HexDirection::NONE, HexDirection::NORTHEAST},
       {HexDirection::NORTHEAST, HexDirection::SOUTH},
       {HexDirection::EAST, HexDirection::NORTHWEST}}};
  auto representations = Vertex::getAllVertexRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(GetAllVertexRepsTestSuite, GetAllSouthEastVertexRepsTest) {
  HexDirection d = HexDirection::SOUTHEAST;
  std::array<HexPath, 3> expected = {
      {{HexDirection::NONE, HexDirection::SOUTHEAST},
       {HexDirection::SOUTHEAST, HexDirection::NORTH},
       {HexDirection::EAST, HexDirection::SOUTHWEST}}};
  auto representations = Vertex::getAllVertexRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(GetAllVertexRepsTestSuite, GetAllSouthVertexRepsTest) {
  HexDirection d = HexDirection::SOUTH;
  std::array<HexPath, 3> expected = {
      {{HexDirection::NONE, HexDirection::SOUTH},
       {HexDirection::SOUTHEAST, HexDirection::NORTHWEST},
       {HexDirection::SOUTHWEST, HexDirection::NORTHEAST}}};
  auto representations = Vertex::getAllVertexRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(GetAllVertexRepsTestSuite, GetAllSouthWestVertexRepsTest) {
  HexDirection d = HexDirection::SOUTHWEST;
  std::array<HexPath, 3> expected = {
      {{HexDirection::NONE, HexDirection::SOUTHWEST},
       {HexDirection::SOUTHWEST, HexDirection::NORTH},
       {HexDirection::WEST, HexDirection::SOUTHEAST}}};
  auto representations = Vertex::getAllVertexRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(GetAllVertexRepsTestSuite, GetAllNorthWestVertexRepsTest) {
  HexDirection d = HexDirection::NORTHWEST;
  std::array<HexPath, 3> expected = {
      {{HexDirection::NONE, HexDirection::NORTHWEST},
       {HexDirection::NORTHWEST, HexDirection::SOUTH},
       {HexDirection::WEST, HexDirection::NORTHEAST}}};
  auto representations = Vertex::getAllVertexRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}