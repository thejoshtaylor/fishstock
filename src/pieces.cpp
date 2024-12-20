// Classes for each piece type and their respective moves
// (c) Fishstock 2024

#include "board.h"

//
// PAWN
//

// Check if a pawn can make this move
bool Pawn::isValidMove(Board *board, Board::Position from, Board::Position to)
{
    int8_t moveRows = 0;
    // White pieces move a certain direction
    if (this->color == Board::Color::WHITE)
    {
        moveRows = to.row - from.row;
    }
    // Black piece
    else
    {
        moveRows = from.row - to.row;
    }

    // Check if we're moving in a mildly correct direction
    if (moveRows <= 0 || moveRows > 2)
    {
        return false;
    }

    // Check if we can move two spaces
    if (moveRows == 2)
    {
        // If we're moving two we can only move forward
        if (from.col != to.col)
        {
            return false;
        }
        // Check if there's a piece in the way
        if (this->color == Board::Color::WHITE)
        {
            if (board->getPieceColor((Board::Position){from.row + 1, from.col}) != Board::Color::EMPTY)
            {
                return false;
            }
        }
        else
        {
            if (board->getPieceColor((Board::Position){from.row - 1, from.col}) != Board::Color::EMPTY)
            {
                return false;
            }
        }

        // White side
        if (this->color == Board::Color::WHITE)
        {
            if (from.row != 1)
            {
                return false;
            }
        }
        // Black side
        else
        {
            if (from.row != 6)
            {
                return false;
            }
        }
    }

    Board::Color toColor = board->getPieceColor(to);

    // Check if we're moving straight
    if (from.col == to.col)
    {
        // Check if there's a piece in the way
        if (toColor != Board::Color::EMPTY)
        {
            return false;
        }
    }
    // We're moving diagonally
    else
    {
        // Make sure it's only one space diagonally
        if (abs(from.col - to.col) != 1)
        {
            return false;
        }
        
        // Check if we're moving to an empty space
        if (toColor == Board::Color::EMPTY)
        {
            // Check if we can en passant
            if (!board->checkEnPassant(to))
            {
                return false;
            }
        }
        // Check if we're trying to take our own piece
        if (this->color == toColor)
        {
            return false;
        }
    }

    // Passed all checks
    return true;
}

// Get all valid moves for a pawn
std::vector<Board::Position>* Pawn::getValidMoves(Board *board, Board::Position from)
{
    // Check if we can move forward
    if (this->color == Board::Color::WHITE)
    {
        if (board->getPieceColor((Board::Position){from.row + 1, from.col}) == Board::Color::EMPTY)
        {
            // Move forward
            board->isValidMove(from, (Board::Position){from.row + 1, from.col});
            // Move two forward
            if (from.row == 1 && board->getPieceColor((Board::Position){from.row + 2, from.col}) == Board::Color::EMPTY)
            {
                board->isValidMove(from, (Board::Position){from.row + 2, from.col});
            }
        }
        // Check if we can take
        if (board->getPieceColor((Board::Position){from.row + 1, from.col + 1}) == Board::Color::BLACK)
        {
            board->isValidMove(from, (Board::Position){from.row + 1, from.col + 1});
        }
        if (board->getPieceColor((Board::Position){from.row + 1, from.col - 1}) == Board::Color::BLACK)
        {
            board->isValidMove(from, (Board::Position){from.row + 1, from.col - 1});
        }
    }
    else
    {
        if (board->getPieceColor((Board::Position){from.row - 1, from.col}) == Board::Color::EMPTY)
        {
            // Move forward
            board->isValidMove(from, (Board::Position){from.row - 1, from.col});
            // Move two forward
            if (from.row == 6 && board->getPieceColor((Board::Position){from.row - 2, from.col}) == Board::Color::EMPTY)
            {
                board->isValidMove(from, (Board::Position){from.row - 2, from.col});
            }
        }
        // Check if we can take
        if (board->getPieceColor((Board::Position){from.row - 1, from.col + 1}) == Board::Color::WHITE)
        {
            board->isValidMove(from, (Board::Position){from.row - 1, from.col + 1});
        }
        if (board->getPieceColor((Board::Position){from.row - 1, from.col - 1}) == Board::Color::WHITE)
        {
        }
    }
}

// Execute special moves for a pawn
void Pawn::doMove(Board *board, Board::Position from, Board::Position to)
{
    // Check if we are promoting
    if (to.row == 7)
    {
        // Promote the pawn
        board->promotePawn(to, Board::PieceType::QUEEN);
    }

    // Check if we're doing a double move
    if (abs((int)from.row - (int)to.row) == 2)
    {
        // Set en passant
        board->setEnPassant((Board::Position){from.row, to.col});
    }

    // Check if we are taking en passant
    if (from.col != to.col && board->getPieceColor(to) == Board::Color::EMPTY)
    {
        // Remove the piece
        board->removePiece((Board::Position){from.row, to.col});
    }
}

//
// ROOK
//
bool Rook::isValidMove(Board *board, Board::Position from, Board::Position to)
{
    // Check if we're moving in a straight line
    if (from.row != to.row && from.col != to.col)
    {
        return false;
    }

    // Check if there's a piece in the way
    if (from.row == to.row)
    {
        // Moving horizontally
        for (int i = from.col + 1; i < to.col; i++)
        {
            if (board->getPieceColor((Board::Position){from.row, i}) != Board::Color::EMPTY)
            {
                return false;
            }
        }
        for (int i = from.col - 1; i > to.col; i--)
        {
            if (board->getPieceColor((Board::Position){from.row, i}) != Board::Color::EMPTY)
            {
                return false;
            }
        }
    }
    else
    {
        // Moving vertically
        for (int i = from.row + 1; i < to.row; i++)
        {
            if (board->getPieceColor((Board::Position){i, from.col}) != Board::Color::EMPTY)
            {
                return false;
            }
        }
        for (int i = from.row - 1; i > to.row; i--)
        {
            if (board->getPieceColor((Board::Position){i, from.col}) != Board::Color::EMPTY)
            {
                return false;
            }
        }
    }

    return true;
}

std::vector<Board::Position>* Rook::getValidMoves(Board *board, Board::Position from)
{
}

void Rook::doMove(Board *board, Board::Position from, Board::Position to)
{
}