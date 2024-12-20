// Sample test file for the fishstock project
// (c) Fishstock 2024

#include "board.h"
#include "util.h"
#include "gtest/gtest.h"


class FishstockTest : public ::testing::Test {};

TEST_F(FishstockTest, Test1) {
  EXPECT_EQ(1, 1);
}

TEST_F(FishstockTest, UtilTest) {
  // Test the Util class
  
  // Test the pos() method
  Board::Position p = Util::pos("a1");
  EXPECT_EQ(p.row, 0);
  EXPECT_EQ(p.col, 0);

  p = Util::pos("h8");
  EXPECT_EQ(p.row, 7);
  EXPECT_EQ(p.col, 7);

  // Test the str() method
  std::string s = Util::str((Board::Position){0, 0});
  EXPECT_EQ(s, "a1");

  s = Util::str((Board::Position){7, 7});
  EXPECT_EQ(s, "h8");
}