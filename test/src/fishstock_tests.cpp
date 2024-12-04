// Sample test file for the fishstock project
// (c) Fishstock 2024

#include "gtest/gtest.h"

class FishstockTest : public ::testing::Test {};

TEST_F(FishstockTest, Test1) {
  EXPECT_EQ(1, 1);
}