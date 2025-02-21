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
    if (this->isWhite)
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
        if (this->isWhite)
        {
            if (board->getPiece((Board::Position){from.row + 1, from.col}) != Board::PieceType::EMPTY)
            {
                return false;
            }
        }
        else
        {
            if (board->getPiece((Board::Position){from.row - 1, from.col}) != Board::PieceType::EMPTY)
            {
                return false;
            }
        }

        // White side
        if (this->isWhite)
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

    bool isToColorWhite = (char(board->getPiece(to)) < 'a');
    // Check if we're moving straight
    if (from.col == to.col)
    {
        // Check if there's a piece in the way
        if (board->getPiece(to) != Board::PieceType::EMPTY)
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
        if (board->getPiece(to) == Board::PieceType::EMPTY)
        {
            // Check if we can en passant
            if (!board->checkEnPassant(to))
            {
                std::cout << "bad EnPassant" << int(to.col) << std::endl;
                return false;
            }
        }


        // Check if we're trying to take our own piece
        if (this->isWhite == isToColorWhite)
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
    if (this->isWhite)
    {
        if (board->getPiece((Board::Position){from.row + 1, from.col}) == Board::PieceType::EMPTY)
        {
            // Move forward
            board->isValidMove(from, (Board::Position){from.row + 1, from.col});
            // Move two forward
            if (from.row == 1 && board->getPiece((Board::Position){from.row + 2, from.col}) == Board::PieceType::EMPTY)
            {
                board->isValidMove(from, (Board::Position){from.row + 2, from.col});
            }
        }
        // Check if we can take, checking if it is black
        if (char(board->getPiece((Board::Position){from.row + 1, from.col + 1})) >= 'a')
        {
            board->isValidMove(from, (Board::Position){from.row + 1, from.col + 1});
        }
        if (char(board->getPiece((Board::Position){from.row + 1, from.col - 1})) >= 'a')
        {
            board->isValidMove(from, (Board::Position){from.row + 1, from.col - 1});
        }
    }
    else
    {
        if (board->getPiece((Board::Position){from.row - 1, from.col}) == Board::PieceType::EMPTY)
        {
            // Move forward
            board->isValidMove(from, (Board::Position){from.row - 1, from.col});
            // Move two forward
            if (from.row == 6 && board->getPiece((Board::Position){from.row - 2, from.col}) == Board::PieceType::EMPTY)
            {
                board->isValidMove(from, (Board::Position){from.row - 2, from.col});
            }
        }
        // Check if we can take, we can take if it is white
        if (char(board->getPiece((Board::Position){from.row - 1, from.col + 1})) < 'a')
        {
            board->isValidMove(from, (Board::Position){from.row - 1, from.col + 1});
        }
        if (char(board->getPiece((Board::Position){from.row - 1, from.col - 1})) < 'a')
        {
            board->isValidMove(from, (Board::Position){from.row - 1, from.col - 1});
        }
    }
}

// Execute special moves for a pawn
void Pawn::doMove(Board *board, Board::Position from, Board::Position to)
{

    //BAD CODE: assumes pawn is alway white from what I can tell
    // Check if we are promoting
    if (to.row == 7)
    {
        // Promote the pawn
        if (isWhite)
        {
            board->promotePawn(to, Board::PieceType::WHITE_QUEEN);
        }
        else
        {
            board->promotePawn(to, Board::PieceType::BLACK_QUEEN);
        }
            
    } 

    // Check if we're doing a double move
    if (abs((int)from.row - (int)to.row) == 2)
    {
        std::cout << "setting Passant col to " <<  int(to.col) << std::endl;
        // Set en passant
        board->setEnPassant((Board::Position){from.row, to.col});
    }

    //BAD CODE: if it is an enpassant but the space we need to move to is full it throws no errors and sielently fails (shut up)
    // Check if we are taking en passant
    if (from.col != to.col && board->getPiece(to) == Board::PieceType::EMPTY)
    {
        // Remove the piece
        board->removePiece((Board::Position){from.row, to.col});
    }

    board->setEnPassant((Board::Position){0,8});

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
            if (board->getPiece((Board::Position){from.row, i}) != Board::PieceType::EMPTY)
            {
                return false;
            }
        }
        for (int i = from.col - 1; i > to.col; i--)
        {
            if (board->getPiece((Board::Position){from.row, i}) != Board::PieceType::EMPTY)
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
            if (board->getPiece((Board::Position){i, from.col}) != Board::PieceType::EMPTY)
            {
                return false;
            }
        }
        for (int i = from.row - 1; i > to.row; i--)
        {
            if (board->getPiece((Board::Position){i, from.col}) != Board::PieceType::EMPTY)
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