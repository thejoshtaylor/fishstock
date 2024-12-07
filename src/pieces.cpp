// Classes for each piece type and their respective moves
// (c) Fishstock 2024

#include "board.h"

//
// PAWN
//

// Check if a pawn can make this move
bool Pawn::isValidMove(Board *board, uint8_t fromRow, uint8_t fromCol, uint8_t toRow, uint8_t toCol)
{
    int8_t moveRows = 0;
    // White pieces move a certain direction
    if (this->color == Board::Color::WHITE)
    {
        moveRows = toRow - fromRow;
    }
    // Black piece
    else
    {
        moveRows = fromRow - toRow;
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
        if (fromCol != toCol)
        {
            return false;
        }
        // Check if there's a piece in the way
        if (this->color == Board::Color::WHITE)
        {
            if (board->getPieceColor(fromRow + 1, fromCol) != Board::Color::EMPTY)
            {
                return false;
            }
        }
        else
        {
            if (board->getPieceColor(fromRow - 1, fromCol) != Board::Color::EMPTY)
            {
                return false;
            }
        }

        // White side
        if (this->color == Board::Color::WHITE)
        {
            if (fromRow != 1)
            {
                return false;
            }
        }
        // Black side
        else
        {
            if (fromRow != 6)
            {
                return false;
            }
        }
    }

    Board::Color toColor = board->getPieceColor(toRow, toCol);

    // Check if we're moving straight
    if (fromCol == toCol)
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
        if (abs(fromCol - toCol) != 1)
        {
            return false;
        }
        
        // Check if we're moving to an empty space
        if (toColor == Board::Color::EMPTY)
        {
            // Check if we can en passant
            if (!board->checkEnPassant(toRow, toCol))
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
void Pawn::getValidMoves(Board *board, uint8_t fromRow, uint8_t fromCol)
{
    // Check if we can move forward
    if (this->color == Board::Color::WHITE)
    {
        if (board->getPieceColor(fromRow + 1, fromCol) == Board::Color::EMPTY)
        {
            // Move forward
            board->isValidMove(fromRow, fromCol, fromRow + 1, fromCol);
            // Move two forward
            if (fromRow == 1 && board->getPieceColor(fromRow + 2, fromCol) == Board::Color::EMPTY)
            {
                board->isValidMove(fromRow, fromCol, fromRow + 2, fromCol);
            }
        }
        // Check if we can take
        if (board->getPieceColor(fromRow + 1, fromCol + 1) == Board::Color::BLACK)
        {
            board->isValidMove(fromRow, fromCol, fromRow + 1, fromCol + 1);
        }
        if (board->getPieceColor(fromRow + 1, fromCol - 1) == Board::Color::BLACK)
        {
            board->isValidMove(fromRow, fromCol, fromRow + 1, fromCol - 1);
        }
    }
    else
    {
        if (board->getPieceColor(fromRow - 1, fromCol) == Board::Color::EMPTY)
        {
            // Move forward
            board->isValidMove(fromRow, fromCol, fromRow - 1, fromCol);
            // Move two forward
            if (fromRow == 6 && board->getPieceColor(fromRow - 2, fromCol) == Board::Color::EMPTY)
            {
                board->isValidMove(fromRow, fromCol, fromRow - 2, fromCol);
            }
        }
        // Check if we can take
        if (board->getPieceColor(fromRow - 1, fromCol + 1) == Board::Color::WHITE)
        {
            board->isValidMove(fromRow, fromCol, fromRow - 1, fromCol + 1);
        }
        if (board->getPieceColor(fromRow - 1, fromCol - 1) == Board::Color::WHITE)
        {
        }
    }
}

// Execute special moves for a pawn
void Pawn::doMove(Board *board, int fromRow, int fromCol, int toRow, int toCol)
{
    // Check if we are promoting
    if (toRow == 0 || toRow == 7)
    {
        // Promote the pawn
        board->promotePawn(toRow, toCol, Board::PieceType::QUEEN);
    }

    // Check if we're doing a double move
    if (abs((int)fromRow - (int)toRow) == 2)
    {
        // Set en passant
        board->setEnPassant(fromRow, toCol);
    }

    // Check if we are taking en passant
    if (fromCol != toCol && board->getPieceColor(toRow, toCol) == Board::Color::EMPTY)
    {
        // Remove the piece
        board->removePiece(fromRow, toCol);
    }
}
