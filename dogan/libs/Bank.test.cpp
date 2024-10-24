#include "Bank.h"
#include "DoganExceptions.h"
#include <gtest/gtest.h>

using namespace Dogan;
class BankFixture : public ::testing::Test {
protected:
  void SetUp() override {}
  Bank dBank{};
  Bank pBank{{10, 11, 12, 13, 14},
             {DevelopmentType::BUILDROAD, DevelopmentType::MONOPOLY,
              DevelopmentType::SOLDIER, DevelopmentType::TAKETWO,
              DevelopmentType::VICPOINT}};
};

TEST_F(BankFixture, DefaultConstructorTest) {
  std::array<int, 5> expected = {0, 0, 0, 0, 0};
  EXPECT_EQ(dBank.getResourceCount(), expected)
      << "Default resources should be 0";
  EXPECT_EQ(dBank.getDevelopmentCount(), expected)
      << "Default developments should be 0";
}

TEST_F(BankFixture, AddResourceTest) {
  std::array<int, 5> expected = {5, 5, 5, 5, 5};
  dBank.addResources({5, 5, 5, 5, 5});
  EXPECT_EQ(dBank.getResourceCount(), expected)
      << "Resources should be added correctly";

  expected = {10, 10, 10, 10, 10};
  dBank.addResource(ResourceType::WOOD, 5);
  dBank.addResource(ResourceType::SHEEP, 5);
  dBank.addResource(ResourceType::WHEAT, 5);
  dBank.addResource(ResourceType::BRICK, 5);
  dBank.addResource(ResourceType::STONE, 5);
  EXPECT_EQ(dBank.getResourceCount(), expected)
      << "Resources should be added correctly";
}

TEST_F(BankFixture, RemoveResourceTest) {
  std::array<int, 5> expected = {5, 6, 7, 8, 9};
  pBank.addResources({-5, -5, -5, -5, -5});
  EXPECT_EQ(pBank.getResourceCount(), expected)
      << "Resources should be removed correctly";

  expected = {0, 1, 2, 3, 4};
  pBank.addResource(ResourceType::WOOD, -5);
  pBank.addResource(ResourceType::SHEEP, -5);
  pBank.addResource(ResourceType::WHEAT, -5);
  pBank.addResource(ResourceType::BRICK, -5);
  pBank.addResource(ResourceType::STONE, -5);
  EXPECT_EQ(pBank.getResourceCount(), expected)
      << "Resources should be removed correctly";
}

TEST_F(BankFixture, RemoveResourceEmptyTest) {
  EXPECT_THROW({ pBank.addResource(ResourceType::WOOD, -11); },
               InsufficientResourcesException);
  EXPECT_THROW({ dBank.addResource(ResourceType::WOOD, -1); },
               InsufficientResourcesException);
}

TEST_F(BankFixture, CanAffordTest) {
  EXPECT_TRUE(pBank.canAfford({10, 11, 12, 13, 14}))
      << "Should be able to afford";
  EXPECT_TRUE(pBank.canAfford({2, 2, 2, 2, 2})) << "Should be able to afford";
  EXPECT_TRUE(pBank.canAfford({0, 0, 0, 0, 0})) << "Should be able to afford";
  pBank.addResources({-5, -5, -5, -5, -5});
  EXPECT_FALSE(pBank.canAfford({6, 1, 2, 3, 4}))
      << "Should not be able to afford";
}

TEST_F(BankFixture, PopDevelopmentTest) {
  DevelopmentType expected = DevelopmentType::VICPOINT;
  EXPECT_EQ(pBank.popDevelopment(), expected)
      << "Should pop the last development";
  expected = DevelopmentType::TAKETWO;
  EXPECT_EQ(pBank.popDevelopment(), expected)
      << "Should pop the last development";
  expected = DevelopmentType::SOLDIER;
  EXPECT_EQ(pBank.popDevelopment(), expected)
      << "Should pop the last development";
  expected = DevelopmentType::MONOPOLY;
  EXPECT_EQ(pBank.popDevelopment(), expected)
      << "Should pop the last development";
  expected = DevelopmentType::BUILDROAD;
  EXPECT_EQ(pBank.popDevelopment(), expected)
      << "Should pop the last development";

  std::array<int, 5> newExpected{0, 0, 0, 0, 0};
  EXPECT_EQ(pBank.getDevelopmentCount(), newExpected)
      << "Should have no developments left";

  EXPECT_THROW({ pBank.popDevelopment(); }, InsufficientDevelopmentsException)
      << "Should throw an error when popping from an empty bank";
}