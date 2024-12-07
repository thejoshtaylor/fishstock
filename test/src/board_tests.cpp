// Test file for the board class of the fishstock project
// (c) Fishstock 2024

#include "board.h"
#include "gtest/gtest.h"

class BoardTest : public ::testing::Test
{
protected:
    BoardTest()
    {
        board = Board();
    }

public:
    Board board;
};

TEST_F(BoardTest, ColorTest)
{
    EXPECT_EQ(board.getPieceColor(0, 0), Board::Color::WHITE);
    EXPECT_EQ(board.getPieceColor(7, 0), Board::Color::BLACK);
    EXPECT_EQ(board.getPieceColor(3, 3), Board::Color::EMPTY);
}

TEST_F(BoardTest, InvalidMoveTest)
{
    // Move to current position
    EXPECT_FALSE(board.isValidMove(0, 0, 0, 0));

    // Move off the board
    EXPECT_FALSE(board.isValidMove(0, 0, 8, 0));
    EXPECT_FALSE(board.isValidMove(0, 0, 0, 8));
    EXPECT_FALSE(board.isValidMove(0, 0, 8, 8));

    // Move from empty space
    EXPECT_FALSE(board.isValidMove(2, 2, 3, 3));

    // Move to same color
    EXPECT_FALSE(board.isValidMove(0, 0, 1, 0));

    // Move wrong team
    EXPECT_FALSE(board.isValidMove(6, 0, 5, 0));

    // Try the actual move
    EXPECT_ANY_THROW(board.move(0, 0, 0, 0));
    EXPECT_ANY_THROW(board.move(0, 0, 8, 0));
    EXPECT_ANY_THROW(board.move(2, 2, 3, 3));
}

//
// SPECIFIC PIECES
//

//
// PAWN
//
TEST_F(BoardTest, PawnMoveTest)
{
    // Move pawn forward
    EXPECT_TRUE(board.isValidMove(1, 0, 2, 0));
    EXPECT_TRUE(board.isValidMove(1, 0, 3, 0));

    // Move pawn diagonal: invalid because not taking
    EXPECT_FALSE(board.isValidMove(1, 1, 2, 0));
    EXPECT_FALSE(board.isValidMove(1, 1, 2, 2));

    // Develop board for diagonal move
    ASSERT_NO_THROW(board.move(1, 2, 3, 2));
    ASSERT_NO_THROW(board.move(6, 1, 4, 1));

    // Move pawn diagonal and take
    EXPECT_TRUE(board.isValidMove(3, 2, 4, 1));
    // Can't move pawn diagonal other way
    EXPECT_FALSE(board.isValidMove(3, 2, 4, 3));
    // Move one forward
    EXPECT_TRUE(board.isValidMove(3, 2, 4, 2));
    // Move two forward
    EXPECT_FALSE(board.isValidMove(3, 2, 5, 2));

    // Develop board for en passant
    ASSERT_NO_THROW(board.move(1, 5, 3, 5));
    ASSERT_NO_THROW(board.move(6, 2, 5, 2));
    ASSERT_NO_THROW(board.move(3, 5, 4, 5));
    ASSERT_NO_THROW(board.move(6, 4, 4, 4));

    // En passant
    EXPECT_TRUE(board.isValidMove(4, 5, 5, 4));
    // Check valid take
    ASSERT_NO_THROW(board.move(4, 5, 5, 4));
    EXPECT_EQ(board.getPieceColor(4, 4), Board::Color::EMPTY);

    // Develop board to test pawn can't move forward two
    ASSERT_NO_THROW(board.move(4, 1, 3, 1));
    ASSERT_NO_THROW(board.move(1, 6, 3, 6));
    ASSERT_NO_THROW(board.move(6, 7, 4, 7));
    ASSERT_NO_THROW(board.move(3, 6, 4, 6));

    // Can't move forward two
    EXPECT_FALSE(board.isValidMove(6, 6, 4, 6));
    // Can move forward one
    EXPECT_TRUE(board.isValidMove(6, 6, 5, 6));

    // Develop board to test pawn can't move forward one
    ASSERT_NO_THROW(board.move(4, 7, 3, 7));
    ASSERT_NO_THROW(board.move(4, 6, 5, 6));
    ASSERT_NO_THROW(board.move(3, 7, 2, 7));

    // Can't move forward one
    EXPECT_FALSE(board.isValidMove(1, 7, 2, 7));
    // Can't move forward two
    EXPECT_FALSE(board.isValidMove(1, 7, 3, 7));
}