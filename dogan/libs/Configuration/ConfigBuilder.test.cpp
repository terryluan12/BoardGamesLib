#include "DoganConfigBuilder.h"
#include "config.enum.h"
#include <gtest/gtest.h>

using namespace Dogan;
TEST(BuildConfigReplaceExactTestSuite, NumberConfigSuccessTest) {
  ConfigBuilder builder{};
  Configuration c{OrderConfiguration::DEFAULT, ReplaceConfiguration::EXACT};
  std::vector<Coordinate2D> board{Coordinate2D{0, 0}, Coordinate2D{1, 1}};
  std::vector<int> numbers{1, 1};

  std::mt19937 rengine{std::random_device{}()};
  builder.setNumberConfig(c);
  builder.setTileLocations(board);
  builder.setNumberOrder(numbers);
  builder.setBoardResourceOrder(numbers);
  EXPECT_NO_THROW(builder.validate());
}

TEST(BuildConfigReplaceExactTestSuite, PortResourceOrderSuccessTest) {
  ConfigBuilder builder{};
  Configuration c{OrderConfiguration::DEFAULT, ReplaceConfiguration::EXACT};
  std::vector<std::set<VertexPrimitive>> ports{
      {{Coordinate2D{0, 0}, HexDirection::NORTH}},
      {{Coordinate2D{1, 1}, HexDirection::SOUTH}}};
  std::vector<int> pr{2, 3};
  // std::vector<ResourceType> pr{ResourceType::WHEAT, ResourceType::BRICK};

  std::mt19937 rengine{std::random_device{}()};

  builder.setPortResourceConfig(c);
  builder.setPortLocations(ports);
  builder.setPortResourceOrder(pr);
  EXPECT_NO_THROW(builder.validate());
}

TEST(BuildConfigReplaceExactTestSuite, ResourceSuccessTest) {
  ConfigBuilder builder{};
  Configuration c{OrderConfiguration::DEFAULT, ReplaceConfiguration::EXACT};
  std::vector<Coordinate2D> board{Coordinate2D{0, 0}, Coordinate2D{1, 1}};
  std::vector<int> numbers{2, 3};
  // std::vector<ResourceType> r{ResourceType::WHEAT, ResourceType::BRICK};

  std::mt19937 rengine{std::random_device{}()};

  builder.setBoardResourceConfig(c);
  builder.setTileLocations(board);
  builder.setNumberOrder(numbers);
  builder.setBoardResourceOrder(numbers);
  EXPECT_NO_THROW(builder.validate());
}

TEST(BuildConfigReplaceExactTestSuite, DevelopmentSuccessTest) {
  ConfigBuilder builder{};
  Configuration c{OrderConfiguration::DEFAULT, ReplaceConfiguration::EXACT};
  std::array<size_t, 5> developmentCount{1, 1, 0, 0, 0};
  std::vector<DevelopmentType> dl{DevelopmentType::VICPOINT,
                                  DevelopmentType::MONOPOLY};

  std::mt19937 rengine{std::random_device{}()};

  builder.setDevelopmentConfig(c);
  builder.setDevelopmentCount(developmentCount);
  builder.setDevelopmentOrder(dl);
  EXPECT_NO_THROW(builder.validate());
}

void testValidation(ConfigBuilder builder, std::string expectedString) {
  try {
    builder.validate();
  }
  catch( const std::invalid_argument& e) {
    EXPECT_STREQ(expectedString.c_str(), e.what());
    throw;
  }
}

TEST(BuildConfigReplaceExactTestSuite, NumberConfigFailTest) {
  ConfigBuilder builder{};
  Configuration c{OrderConfiguration::DEFAULT, ReplaceConfiguration::EXACT};
  std::vector<Coordinate2D> board{Coordinate2D{0, 0}, Coordinate2D{1, 1}};
  std::vector<int> numbers1{1}, numbers2{1, 1}, numbers3{1, 2, 3};

  std::mt19937 rengine{std::random_device{}()};

  builder.setNumberConfig(c);
  builder.setBoardResourceOrder(numbers2);
  builder.setTileLocations(board);

  builder.setNumberOrder(numbers1);
  EXPECT_THROW(testValidation(builder, "Error: ReplaceConfiguration::EXACT set. Therefore number location size: 1 must equal to board size: 2\n"), std::invalid_argument);

  builder.setNumberOrder(numbers3);
  EXPECT_THROW(testValidation(builder, "Error: ReplaceConfiguration::EXACT set. Therefore number location size: 3 must equal to board size: 2\n"), std::invalid_argument);
}

TEST(BuildConfigReplaceExactTestSuite, PortResourceFailTest) {
  ConfigBuilder builder{};
  Configuration c{OrderConfiguration::DEFAULT, ReplaceConfiguration::EXACT};
  std::vector<std::set<VertexPrimitive>> ports{
      {{Coordinate2D{0, 0}, HexDirection::NORTH}},
      {{Coordinate2D{1, 1}, HexDirection::SOUTH}}};
  std::vector<int> numbers1{2}, numbers3{2, 3, 1};
  // std::vector<ResourceType> pr1{ResourceType::WHEAT, ResourceType::BRICK,
  // ResourceType::SHEEP}, pr2{ResourceType::WHEAT};

  std::mt19937 rengine{std::random_device{}()};

  builder.setPortResourceConfig(c);
  builder.setPortLocations(ports);
  builder.setPortResourceOrder(numbers1);
  EXPECT_THROW(testValidation(builder, "Error: ReplaceConfiguration::EXACT set. Therefore Port Resources size: 1 must equal to Port locations size: 2\n"), std::invalid_argument);

  builder.setPortResourceOrder(numbers3);
  EXPECT_THROW(testValidation(builder, "Error: ReplaceConfiguration::EXACT set. Therefore Port Resources size: 3 must equal to Port locations size: 2\n"), std::invalid_argument);
}

TEST(BuildConfigReplaceExactTestSuite, ResourceFailTest) {
  ConfigBuilder builder{};
  Configuration c{OrderConfiguration::DEFAULT, ReplaceConfiguration::EXACT};
  std::vector<Coordinate2D> board{Coordinate2D{0, 0}, Coordinate2D{1, 1}};
  std::vector<int> numbers1{2}, numbers2{1, 1}, numbers3{2, 3, 1};
  // std::vector<ResourceType> r1{ResourceType::WHEAT, ResourceType::BRICK,
  // ResourceType::SHEEP}, r2{ResourceType::WHEAT};

  std::mt19937 rengine{std::random_device{}()};

  builder.setBoardResourceConfig(c);
  builder.setNumberOrder(numbers2);
  builder.setTileLocations(board);
  builder.setBoardResourceOrder(numbers1);
  EXPECT_THROW(testValidation(builder, "Error: ReplaceConfiguration::EXACT set. Therefore Resources size: 1 must equal to board size: 2\n"), std::invalid_argument);

  builder.setBoardResourceOrder(numbers3);
  EXPECT_THROW(testValidation(builder, "Error: ReplaceConfiguration::EXACT set. Therefore Resources size: 3 must equal to board size: 2\n"), std::invalid_argument);
}

TEST(BuildConfigReplaceExactTestSuite, DevelopmentFailTest) {
  ConfigBuilder builder{};
  Configuration c{OrderConfiguration::DEFAULT, ReplaceConfiguration::EXACT};
  std::array<size_t, 5> developmentCount{1, 1, 0, 0, 0};
  std::vector<DevelopmentType> dl1{DevelopmentType::SOLDIER,
                                   DevelopmentType::SOLDIER,
                                   DevelopmentType::SOLDIER},
      dl2{DevelopmentType::VICPOINT},
      dl3{DevelopmentType::VICPOINT, DevelopmentType::MONOPOLY,
          DevelopmentType::BUILDROAD},
      dl4{DevelopmentType::BUILDROAD, DevelopmentType::TAKETWO};

  std::mt19937 rengine{std::random_device{}()};

  builder.setDevelopmentConfig(c);
  builder.setDevelopmentCount(developmentCount);
  builder.setDevelopmentOrder(dl1);
  EXPECT_THROW(testValidation(builder, "Error: ReplaceConfiguration::EXACT set. Therefore Amount of DevelopmentCard type: Victory Point must equal to 1\nError: ReplaceConfiguration::EXACT set. Therefore Amount of DevelopmentCard type: Monopoly must equal to 1\nError: ReplaceConfiguration::EXACT set. Therefore Amount of DevelopmentCard type: Soldier must equal to 0\n"), std::invalid_argument);

  builder.setDevelopmentOrder(dl2);
  EXPECT_THROW(testValidation(builder, "Error: ReplaceConfiguration::EXACT set. Therefore Amount of DevelopmentCard type: Monopoly must equal to 1\n"), std::invalid_argument);

  builder.setDevelopmentOrder(dl3);
  EXPECT_THROW(testValidation(builder, "Error: ReplaceConfiguration::EXACT set. Therefore Amount of DevelopmentCard type: Build Road must equal to 0\n"), std::invalid_argument);

  builder.setDevelopmentOrder(dl4);
  EXPECT_THROW(testValidation(builder, "Error: ReplaceConfiguration::EXACT set. Therefore Amount of DevelopmentCard type: Victory Point must equal to 1\nError: ReplaceConfiguration::EXACT set. Therefore Amount of DevelopmentCard type: Monopoly must equal to 1\nError: ReplaceConfiguration::EXACT set. Therefore Amount of DevelopmentCard type: Build Road must equal to 0\nError: ReplaceConfiguration::EXACT set. Therefore Amount of DevelopmentCard type: Take Two must equal to 0\n"), std::invalid_argument);
}