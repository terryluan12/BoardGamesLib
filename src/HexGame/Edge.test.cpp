#include "Edge.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

// ------------------------------ EdgeGetDAETestSuite ------------------------------ //

TEST(EdgeGetDAETestSuite, getNorthEastDAEdgeTest) {
  HexDirection d = HexDirection::NORTHEAST;
  std::array<HexPath, 4> expected = {{
    {HexDirection::NORTHEAST, HexDirection::WEST},
    {HexDirection::NORTHWEST, HexDirection::EAST},
    {HexDirection::NORTHEAST, HexDirection::SOUTHEAST},
    {HexDirection::EAST, HexDirection::NORTHWEST}
  }};
  auto representations = Edge::getDistantAdjacentEdges(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(EdgeGetDAETestSuite, getEastDAEdgeTest) {
  HexDirection d = HexDirection::EAST;
  std::array<HexPath, 4> expected = {{
    {HexDirection::EAST, HexDirection::NORTHWEST},
    {HexDirection::NORTHEAST, HexDirection::SOUTHEAST},
    {HexDirection::EAST, HexDirection::SOUTHWEST},
    {HexDirection::SOUTHEAST, HexDirection::NORTHEAST}
  }};
  auto representations = Edge::getDistantAdjacentEdges(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(EdgeGetDAETestSuite, getSouthEastDAEdgeTest) {
  HexDirection d = HexDirection::SOUTHEAST;
  std::array<HexPath, 4> expected = {{
    {HexDirection::EAST, HexDirection::SOUTHWEST},
    {HexDirection::SOUTHEAST, HexDirection::NORTHEAST},
    {HexDirection::SOUTHEAST, HexDirection::WEST},
    {HexDirection::SOUTHWEST, HexDirection::EAST}
  }};
 auto representations = Edge::getDistantAdjacentEdges(d);
 EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

// ------------------------------ EdgeGetLAETestSuite ------------------------------ //

TEST(EdgeGetLAETestSuite, GetNorthLAEdgesTest) {
  HexDirection d = HexDirection::NORTHEAST;
  std::array<HexPath, 2> expected = {{
    {HexDirection::NONE, HexDirection::NORTHWEST},
    {HexDirection::NONE, HexDirection::EAST}
  }};
  auto representations = Edge::getLocalAdjacentEdges(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(EdgeGetLAETestSuite, GetEastLAEdgesTest) {
  HexDirection d = HexDirection::EAST;
  std::array<HexPath, 2> expected = {{
    {HexDirection::NONE, HexDirection::NORTHEAST}, 
    {HexDirection::NONE, HexDirection::SOUTHEAST}
  }};
  auto representations = Edge::getLocalAdjacentEdges(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(EdgeGetLAETestSuite, GetSouthEastLAEdgesTest) {
  HexDirection d = HexDirection::SOUTHEAST;
  std::array<HexPath, 2> expected = {{
    {HexDirection::NONE, HexDirection::EAST},
    {HexDirection::NONE, HexDirection::SOUTHWEST}
  }};
  auto representations = Edge::getLocalAdjacentEdges(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}

// ------------------------------ GetAllEdgeRepsTestSuite ------------------------------ //

TEST(GetAllEdgeRepsTestSuite, GetAllNorthWestEdgeRepsTest) {
  HexDirection d = HexDirection::NORTHWEST;
  std::array<HexPath, 2> expected = {{
    {HexDirection::NONE, HexDirection::NORTHWEST},
    {HexDirection::NORTHWEST, HexDirection::SOUTHEAST}
  }};
  auto representations = Edge::getAllEdgeRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(GetAllEdgeRepsTestSuite, GetAllNorthEastEdgeRepsTest) {
  HexDirection d = HexDirection::NORTHEAST;
  std::array<HexPath, 2> expected = {{
    {HexDirection::NONE, HexDirection::NORTHEAST},
    {HexDirection::NORTHEAST, HexDirection::SOUTHWEST},
  }};
  auto representations = Edge::getAllEdgeRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(GetAllEdgeRepsTestSuite, GetAllEastEdgeRepsTest) {
  HexDirection d = HexDirection::EAST;
  std::array<HexPath, 2> expected = {{
    {HexDirection::NONE, HexDirection::EAST},
    {HexDirection::EAST, HexDirection::WEST},
  }};
  auto representations = Edge::getAllEdgeRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(GetAllEdgeRepsTestSuite, GetAllSouthEastEdgeRepsTest) {
  HexDirection d = HexDirection::SOUTHEAST;
  std::array<HexPath, 2> expected = {{
    {HexDirection::NONE, HexDirection::SOUTHEAST},
    {HexDirection::SOUTHEAST, HexDirection::NORTHWEST},
  }};
  auto representations = Edge::getAllEdgeRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(GetAllEdgeRepsTestSuite, GetAllSouthWestEdgeRepsTest) {
  HexDirection d = HexDirection::SOUTHWEST;
  std::array<HexPath, 2> expected = {{
    {HexDirection::NONE, HexDirection::SOUTHWEST},
    {HexDirection::SOUTHWEST, HexDirection::NORTHEAST},
  }};
  auto representations = Edge::getAllEdgeRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
TEST(GetAllEdgeRepsTestSuite, GetAllWestEdgeRepsTest) {
  HexDirection d = HexDirection::WEST;
  std::array<HexPath, 2> expected = {{
    {HexDirection::NONE, HexDirection::WEST},
    {HexDirection::WEST, HexDirection::EAST},
  }};
  auto representations = Edge::getAllEdgeRepresentations(d);
  EXPECT_THAT(representations, ::testing::UnorderedElementsAreArray(expected));
}
