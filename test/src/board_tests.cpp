// Test file for the board class of the fishstock project
// (c) Fishstock 2024

#include "board.h"
#include "gtest/gtest.h"

class BoardTest : public ::testing::Test, public Board::Board
{
protected:
    BoardTest() {}
};

TEST_F(BoardTest, ColorTest)
{
    EXPECT_EQ(isWhitePiece(getPiece((Board::Position){0, 0})), true);
    EXPECT_EQ(isWhitePiece(getPiece((Board::Position){7, 0})), false);
    EXPECT_EQ(getPiece((Board::Position){3, 3}), Board::PieceType::EMPTY);
    EXPECT_ANY_THROW(isWhitePiece(getPiece((Board::Position){3, 3})));
}

TEST_F(BoardTest, InvalidMoveTest)
{
    // Move to current position
    EXPECT_FALSE(isValidMove((Board::Position){0, 0}, (Board::Position){0, 0}));

    // Move off the board
    EXPECT_FALSE(isValidMove((Board::Position){0, 0}, (Board::Position){8, 0}));
    EXPECT_FALSE(isValidMove((Board::Position){0, 0}, (Board::Position){0, 8}));
    EXPECT_FALSE(isValidMove((Board::Position){0, 0}, (Board::Position){8, 8}));

    // Move from empty space
    EXPECT_FALSE(isValidMove((Board::Position){2, 2}, (Board::Position){3, 3}));

    // Move to same color
    EXPECT_FALSE(isValidMove((Board::Position){0, 0}, (Board::Position){1, 0}));

    // Move wrong team
    EXPECT_FALSE(isValidMove((Board::Position){6, 0}, (Board::Position){5, 0}));

    // Try the actual move
    EXPECT_ANY_THROW(move((Board::Position){0, 0}, (Board::Position){0, 0}));
    EXPECT_ANY_THROW(move((Board::Position){0, 0}, (Board::Position){8, 0}));
    EXPECT_ANY_THROW(move((Board::Position){2, 2}, (Board::Position){3, 3}));
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
    EXPECT_TRUE(isValidMove((Board::Position){1, 0}, (Board::Position){2, 0}));
    EXPECT_TRUE(isValidMove((Board::Position){1, 0}, (Board::Position){3, 0}));

    // Move pawn diagonal: invalid because not taking
    EXPECT_FALSE(isValidMove((Board::Position){1, 1}, (Board::Position){2, 0}));
    EXPECT_FALSE(isValidMove((Board::Position){1, 1}, (Board::Position){2, 2}));

    // Develop board for diagonal move
    ASSERT_NO_THROW(move((Board::Position){1, 2}, (Board::Position){3, 2}));
    ASSERT_NO_THROW(move((Board::Position){6, 1}, (Board::Position){4, 1}));

    // Move pawn diagonal and take
    EXPECT_TRUE(isValidMove((Board::Position){3, 2}, (Board::Position){4, 1}));
    // Can't move pawn diagonal other way
    EXPECT_FALSE(isValidMove((Board::Position){3, 2}, (Board::Position){4, 3}));
    // Move one forward
    EXPECT_TRUE(isValidMove((Board::Position){3, 2}, (Board::Position){4, 2}));
    // Move two forward
    EXPECT_FALSE(isValidMove((Board::Position){3, 2}, (Board::Position){5, 2}));

    // Develop board for en passant
    ASSERT_NO_THROW(move((Board::Position){1, 5}, (Board::Position){3, 5}));
    ASSERT_NO_THROW(move((Board::Position){6, 2}, (Board::Position){5, 2}));
    ASSERT_NO_THROW(move((Board::Position){3, 5}, (Board::Position){4, 5}));
    ASSERT_NO_THROW(move((Board::Position){6, 4}, (Board::Position){4, 4}));

    // En passant
    EXPECT_TRUE(isValidMove((Board::Position){4, 5}, (Board::Position){5, 4}));
    // Check valid take
    ASSERT_NO_THROW(move((Board::Position){4, 5}, (Board::Position){5, 4}));
    EXPECT_EQ(getPiece((Board::Position){4, 4}), Board::PieceType::EMPTY);

    // Develop board to test pawn can't move forward two
    ASSERT_NO_THROW(move((Board::Position){4, 1}, (Board::Position){3, 1}));
    ASSERT_NO_THROW(move((Board::Position){1, 6}, (Board::Position){3, 6}));
    ASSERT_NO_THROW(move((Board::Position){6, 7}, (Board::Position){4, 7}));
    ASSERT_NO_THROW(move((Board::Position){3, 6}, (Board::Position){4, 6}));

    // Can't move forward two
    EXPECT_FALSE(isValidMove((Board::Position){6, 6}, (Board::Position){4, 6}));
    // Can move forward one
    EXPECT_TRUE(isValidMove((Board::Position){6, 6}, (Board::Position){5, 6}));

    // Develop board to test pawn can't move forward one
    ASSERT_NO_THROW(move((Board::Position){4, 7}, (Board::Position){3, 7}));
    ASSERT_NO_THROW(move((Board::Position){4, 6}, (Board::Position){5, 6}));
    ASSERT_NO_THROW(move((Board::Position){3, 7}, (Board::Position){2, 7}));

    // Can't move forward one
    EXPECT_FALSE(isValidMove((Board::Position){1, 7}, (Board::Position){2, 7}));
    // Can't move forward two
    EXPECT_FALSE(isValidMove((Board::Position){1, 7}, (Board::Position){3, 7}));
}

//
// ROOK
//
TEST_F(BoardTest, RookMoveTest)
{
    // Move forward
    // Move backward
    // Move left
    // Move right

    // Can't move diagonal
    // Can't move over pieces
    // Can't take own piece

    // Can take
}

//
// KNIGHT
//
TEST_F(BoardTest, KnightMoveTest)
{
    // Move up 2 left 1
    // Move up 2 right 1
    // Move down 2 left 1
    // Move down 2 right 1
    // Move left 2 up 1
    // Move left 2 down 1
    // Move right 2 up 1
    // Move right 2 down 1

    // Can't move in straight line
    // Can move over pieces
    // Can't take own piece
    // Can take
}

//
// BISHOP
//
TEST_F(BoardTest, BishopMoveTest)
{
    // Move NE
    // Move NW
    // Move SE
    // Move SW

    // Can't move straight
    // Can't move over pieces
    // Can't take own piece
    // Can take
}

//
// QUEEN
//
TEST_F(BoardTest, QueenMoveTest)
{
    // Move forward
    // Move backward
    // Move left
    // Move right
    // Move NE
    // Move NW
    // Move SE
    // Move SW

    // Can't move over pieces
    // Can't take own piece
    // Can take
}

//
// KING
//
TEST_F(BoardTest, KingMoveTest)
{
    // Move forward
    // Move backward
    // Move left
    // Move right
    // Move NE
    // Move NW
    // Move SE
    // Move SW

    // Can't move more than 1 space
    // Can't take own piece
    // Can take
}

//
// CASTLING
//
TEST_F(BoardTest, CastlingTest)
{
    // Can't castle if king has moved
    // Can't castle left if left rook has moved
    // Can't castle right if right rook has moved
    // Can't castle if pieces in the way
    // Can't castle if in check
    // Can't castle if through check

    // Can castle right or left if conditions are met
}

//
// PROMOTION
//
TEST_F(BoardTest, PromotionTest)
{
    // Pawn reaches end of board
    // Pawn can't promote if not at end of board
    // Pawn can't promote to king
    // Pawn can't promote to pawn

    // Pawn can promote to queen, rook, knight, bishop
}

//
// CHECK
//
TEST_F(BoardTest, CheckTest)
{
    // Can't move any piece except to get out of check

    // Can't move king into check
    // Can't move piece into reveal check
}


