// Classes for each piece type and their respective moves
// (c) Fishstock 2024

#include "board.h"

// Piece class util
Piece *Piece::pieceObjConstructor(Board::PieceType inputPiece)
{
    switch (inputPiece)
    {
    case Board::PieceType::WHITE_PAWN:
    case Board::PieceType::BLACK_PAWN:
        return new Pawn(Board::isWhitePiece(inputPiece));
        break;
    case Board::PieceType::WHITE_ROOK:
    case Board::PieceType::BLACK_ROOK:
        return new Rook(Board::isWhitePiece(inputPiece));
        break;
    case Board::PieceType::WHITE_KNIGHT:
    case Board::PieceType::BLACK_KNIGHT:
        return new Knight(Board::isWhitePiece(inputPiece));
        break;
    case Board::PieceType::WHITE_BISHOP:
    case Board::PieceType::BLACK_BISHOP:
        return new Bishop(Board::isWhitePiece(inputPiece));
        break;
    case Board::PieceType::WHITE_QUEEN:
    case Board::PieceType::BLACK_QUEEN:
        return new Queen(Board::isWhitePiece(inputPiece));
        break;
    default:
        throw std::invalid_argument("Invalid piece type");
        break;
    }
}


//
// PRIVATE PIECE FUNC DEFINITIONS
//

void Piece::rookGetValidMovesPattern(const Board *board, Board::Position from, std::vector<Board::Position>* returnVector)
{
    int varyingIndex = 1;

    // moving right
    while (from.col + varyingIndex < 8 && board->getPiece((Board::Position){from.row, from.col + varyingIndex}) == Board::PieceType::EMPTY)
    {
        returnVector->push_back((Board::Position){from.row, from.col + varyingIndex});
        varyingIndex++;
    }

    if (from.col + varyingIndex < 8)
    {
        if (board->getPiece((Board::Position){from.row, from.col + varyingIndex}) != Board::PieceType::EMPTY)
        {
            if (Board::isWhitePiece(board->getPiece((Board::Position){from.row, from.col + varyingIndex})) != isWhite)
            {
                returnVector->push_back((Board::Position){from.row, from.col + varyingIndex});
            }
        }
    }

    // moving left
    varyingIndex = -1;

    while (from.col + varyingIndex >= 0 && board->getPiece((Board::Position){from.row, from.col + varyingIndex}) == Board::PieceType::EMPTY)
    {
        returnVector->push_back((Board::Position){from.row, from.col + varyingIndex});
        varyingIndex--;
    }

    if (from.col + varyingIndex >= 0)
    {
        if (board->getPiece((Board::Position){from.row, from.col + varyingIndex}) != Board::PieceType::EMPTY)
        {
            if (Board::isWhitePiece(board->getPiece((Board::Position){from.row, from.col + varyingIndex})) != isWhite)
            {
                returnVector->push_back((Board::Position){from.row, from.col + varyingIndex});
            }
        }
    }

    // moving up
    varyingIndex = 1;
    while (from.row + varyingIndex < 8 && board->getPiece((Board::Position){from.row + varyingIndex, from.col}) == Board::PieceType::EMPTY)
    {
        returnVector->push_back((Board::Position){from.row + varyingIndex, from.col});
        varyingIndex++;
    }

    if (from.row + varyingIndex < 8)
    {
        if (board->getPiece((Board::Position){from.row + varyingIndex, from.col}) != Board::PieceType::EMPTY)
        {
            if (Board::isWhitePiece(board->getPiece((Board::Position){from.row + varyingIndex, from.col})) != isWhite)
            {
                returnVector->push_back((Board::Position){from.row + varyingIndex, from.col});
            }
        }
    }

    // moving down
    varyingIndex = -1;
    while (from.row + varyingIndex >= 0 && board->getPiece((Board::Position){from.row + varyingIndex, from.col}) == Board::PieceType::EMPTY)
    {
        returnVector->push_back((Board::Position){from.row + varyingIndex, from.col});
        varyingIndex--;
    }

    if (from.row + varyingIndex >= 0)
    {
        if (board->getPiece((Board::Position){from.row + varyingIndex, from.col}) != Board::PieceType::EMPTY)
        {
            if (Board::isWhitePiece(board->getPiece((Board::Position){from.row + varyingIndex, from.col})) != isWhite)
            {
                returnVector->push_back((Board::Position){from.row + varyingIndex, from.col});
            }
        }
    }


}
void Piece::bishopGetValidMovesPattern(const Board *board, Board::Position from, std::vector<Board::Position>* returnVector)
{
    int varyingIndex = 1;

    // moving NE
    while (Board::isInBounds((Board::Position){from.row + varyingIndex, from.col + varyingIndex}) && board->getPiece((Board::Position){from.row + varyingIndex, from.col + varyingIndex}) == Board::PieceType::EMPTY)
    {
        returnVector->push_back((Board::Position){from.row + varyingIndex, from.col + varyingIndex});
        varyingIndex++;
    }

    if (Board::isInBounds((Board::Position){from.row + varyingIndex, from.col + varyingIndex}))
    {
        if (board->getPiece((Board::Position){from.row + varyingIndex, from.col + varyingIndex}) != Board::PieceType::EMPTY)
        {
            if (Board::isWhitePiece(board->getPiece((Board::Position){from.row + varyingIndex, from.col + varyingIndex})) != isWhite)
            {
                returnVector->push_back((Board::Position){from.row + varyingIndex, from.col + varyingIndex});
            }
        }
    }
    varyingIndex = 1;

    // moving NW
    while (Board::isInBounds((Board::Position){from.row + varyingIndex, from.col - varyingIndex}) && board->getPiece((Board::Position){from.row + varyingIndex, from.col - varyingIndex}) == Board::PieceType::EMPTY)
    {
        returnVector->push_back((Board::Position){from.row + varyingIndex, from.col - varyingIndex});
        varyingIndex++;
    }

    if (Board::isInBounds((Board::Position){from.row + varyingIndex, from.col - varyingIndex}))
    {
        if (board->getPiece((Board::Position){from.row + varyingIndex, from.col - varyingIndex}) != Board::PieceType::EMPTY)
        {
            if (Board::isWhitePiece(board->getPiece((Board::Position){from.row + varyingIndex, from.col - varyingIndex})) != isWhite)
            {
                returnVector->push_back((Board::Position){from.row + varyingIndex, from.col - varyingIndex});
            }
        }
    }
    varyingIndex = 1;

    // moving SE
    while (Board::isInBounds((Board::Position){from.row - varyingIndex, from.col + varyingIndex}) && board->getPiece((Board::Position){from.row - varyingIndex, from.col + varyingIndex}) == Board::PieceType::EMPTY)
    {
        returnVector->push_back((Board::Position){from.row - varyingIndex, from.col + varyingIndex});
        varyingIndex++;
    }

    if (Board::isInBounds((Board::Position){from.row - varyingIndex, from.col + varyingIndex}))
    {
        if (board->getPiece((Board::Position){from.row - varyingIndex, from.col + varyingIndex}) != Board::PieceType::EMPTY)
        {
            if (Board::isWhitePiece(board->getPiece((Board::Position){from.row - varyingIndex, from.col + varyingIndex})) != isWhite)
            {
                returnVector->push_back((Board::Position){from.row - varyingIndex, from.col + varyingIndex});
            }
        }
    }
    varyingIndex = 1;

    // moving SW
    while (Board::isInBounds((Board::Position){from.row - varyingIndex, from.col - varyingIndex}) && board->getPiece((Board::Position){from.row - varyingIndex, from.col - varyingIndex}) == Board::PieceType::EMPTY)
    {
        returnVector->push_back((Board::Position){from.row - varyingIndex, from.col - varyingIndex});
        varyingIndex++;
    }

    if (Board::isInBounds((Board::Position){from.row - varyingIndex, from.col - varyingIndex}))
    {
        if (board->getPiece((Board::Position){from.row - varyingIndex, from.col - varyingIndex}) != Board::PieceType::EMPTY)
        {
            if (Board::isWhitePiece(board->getPiece((Board::Position){from.row - varyingIndex, from.col - varyingIndex})) != isWhite)
            {
                returnVector->push_back((Board::Position){from.row - varyingIndex, from.col - varyingIndex});
            }
        }
    }
}





//
// PAWN
//

// possibly garbage now
// Check if a pawn can make this move

// Get all valid moves for a pawn
std::vector<Board::Position> *Pawn::getValidMoves(const Board *board, Board::Position from)
{
    std::vector<Board::Position> *returnList = new std::vector<Board::Position>();
    // direction will be negative if black, reduces if statments becauses you just add direction to the from row if it is white or black
    int direction = (board->isWhitePiece(board->getPiece(from)) ? 1 : -1);

    bool toPosIsWhite = false;
    if (Board::isInBounds((Board::Position){from.row + direction, from.col + 1}))
    {
        // doesnt matter if the tile is empty, but isWhitePiece cant be called on an empty tile
        try
        {
            toPosIsWhite = Board::isWhitePiece(board->getPiece((Board::Position){from.row + direction, from.col + 1}));
        }
        catch (std::invalid_argument &e)
        {
        }
        // check if we can make a capture
        // if diagonal is not empty and it is an enemy piece, or if we can enpassant that way
        if ((board->getPiece((Board::Position){from.row + direction, from.col + 1}) != Board::PieceType::EMPTY && isWhite != toPosIsWhite) ||
            board->checkEnPassant((Board::Position){from.row + direction, from.col + 1}))
        {
            returnList->push_back((Board::Position){from.row + direction, from.col + 1});
        }
    }
    if (Board::isInBounds((Board::Position){from.row + direction, from.col - 1}))
    {
        // doesnt matter if the tile is empty, but isWhitePiece cant be called on an empty tile
        try
        {
            toPosIsWhite = Board::isWhitePiece(board->getPiece((Board::Position){from.row + direction, from.col - 1}));
        }
        catch (std::invalid_argument &e)
        {
        }

        // if diagonal is not empty and it is an enemy piece, or if we can enpassant that way
        if ((board->getPiece((Board::Position){from.row + direction, from.col - 1}) != Board::PieceType::EMPTY && isWhite != toPosIsWhite) ||
            board->checkEnPassant((Board::Position){from.row + direction, from.col - 1}))
        {
            returnList->push_back((Board::Position){from.row + direction, from.col - 1});
        }
    }

    // if one forwards is out of bounds than two forwards is also out of bounds and we are done
    if (!Board::isInBounds((Board::Position){from.row + direction, from.col}))
    {
        return returnList;
    }

    // check if we can move one forward
    if (board->getPiece((Board::Position){from.row + direction, from.col}) == Board::PieceType::EMPTY)
        returnList->push_back((Board::Position){from.row + direction, from.col});

    // if we cant move one forwards we cant move two forwards
    else
        return returnList;

    // check for double moves, uses 2 * direction which can either be 2 or -2
    if ((from.row == 6 || from.row == 1) && (board->getPiece((Board::Position){from.row + 2 * direction, from.col}) == Board::PieceType::EMPTY))
    {
        returnList->push_back((Board::Position){from.row + 2 * direction, from.col});
    }

    return returnList;
}

// Execute special moves for a pawn
void Pawn::doMove(Board *board, Board::Position from, Board::Position to)
{

    // Check if we are promoting
    if (to.row == 7 || to.row == 0)
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

    // Check if we are taking en passant
    if (from.col != to.col && board->getPiece(to) == Board::PieceType::EMPTY)
    {
        // Remove the piece
        board->removePiece((Board::Position){from.row, to.col});
    }
    // clearing the enpassant column now, gets uncleared in the next segment if needed
    board->setEnPassant((Board::Position){0, 8});

    // Check if we're doing a double move
    if (abs((int)from.row - (int)to.row) == 2)
    {
        // Set en passant
        board->setEnPassant((Board::Position){from.row, to.col});
    }
}

//
// ROOK
//

std::vector<Board::Position> *Rook::getValidMoves(const Board *board, Board::Position from)
{
    std::vector<Board::Position> *returnVector = new std::vector<Board::Position>();
    rookGetValidMovesPattern(board,from,returnVector);
    return returnVector;
}

void Rook::doMove(Board *board, Board::Position from, Board::Position to)
{
    // checking if we are on one of the corners
    if (!(from.row % 7 + from.col % 7))
    {
        // setting castle flag for that corner to false, it is possible that it is already false but that does not matter
        board->setCanCastleToFalse(from.row / 7, from.col / 7);
    }
}


//
// KNIGHT
//

std::vector<Board::Position> *Knight::getValidMoves(const Board *board, Board::Position from)
{
    std::vector<Board::Position> *returnList = new std::vector<Board::Position>();

    // going through each coordinate that a knight could move through, I think it is technically effecient, but it is very ugly
    Board::Position newPos = (Board::Position){from.row + 2,from.col + 1};
    if (Board::isInBounds(newPos))
    {
        if (board->getPiece(newPos) == Board::PieceType::EMPTY)
        {
            returnList->push_back(newPos);
        }
        else if (Board::isWhitePiece(board->getPiece(newPos)) != isWhite)
        {
            returnList->push_back(newPos);
        }
    }
    newPos.col = newPos.col + 1;
    newPos.row = newPos.row - 1;
    if (Board::isInBounds(newPos))
    {
        if (board->getPiece(newPos) == Board::PieceType::EMPTY)
        {
            returnList->push_back(newPos);
        }
        else if (Board::isWhitePiece(board->getPiece(newPos)) != isWhite)
        {
            returnList->push_back(newPos);
        }
    }
    newPos.row = newPos.row - 2;
    if (Board::isInBounds(newPos))
    {
        if (board->getPiece(newPos) == Board::PieceType::EMPTY)
        {
            returnList->push_back(newPos);
        }
        else if (Board::isWhitePiece(board->getPiece(newPos)) != isWhite)
        {
            returnList->push_back(newPos);
        }
    }
    newPos.col = newPos.col - 1;
    newPos.row = newPos.row - 1;
    if (Board::isInBounds(newPos))
    {
        if (board->getPiece(newPos) == Board::PieceType::EMPTY)
        {
            returnList->push_back(newPos);
        }
        else if (Board::isWhitePiece(board->getPiece(newPos)) != isWhite)
        {
            returnList->push_back(newPos);
        }
    }
    newPos.col = newPos.col - 2;
    if (Board::isInBounds(newPos))
    {
        if (board->getPiece(newPos) == Board::PieceType::EMPTY)
        {
            returnList->push_back(newPos);
        }
        else if (Board::isWhitePiece(board->getPiece(newPos)) != isWhite)
        {
            returnList->push_back(newPos);
        }
    }
    newPos.col = newPos.col - 1;
    newPos.row = newPos.row + 1;
    if (Board::isInBounds(newPos))
    {
        if (board->getPiece(newPos) == Board::PieceType::EMPTY)
        {
            returnList->push_back(newPos);
        }
        else if (Board::isWhitePiece(board->getPiece(newPos)) != isWhite)
        {
            returnList->push_back(newPos);
        }
    }
    newPos.row = newPos.row + 2;
    if (Board::isInBounds(newPos))
    {
        if (board->getPiece(newPos) == Board::PieceType::EMPTY)
        {
            returnList->push_back(newPos);
        }
        else if (Board::isWhitePiece(board->getPiece(newPos)) != isWhite)
        {
            returnList->push_back(newPos);
        }
    } 
    newPos.col = newPos.col + 1;
    newPos.row = newPos.row + 1;
    if (Board::isInBounds(newPos))
    {
        if (board->getPiece(newPos) == Board::PieceType::EMPTY)
        {
            returnList->push_back(newPos);
        }
        else if (Board::isWhitePiece(board->getPiece(newPos)) != isWhite)
        {
            returnList->push_back(newPos);
        }
    } 
    return returnList;

}
void Knight::doMove(Board *board, Board::Position from, Board::Position to)
{
}



//
// BISHOP
//
std::vector<Board::Position> *Bishop::getValidMoves(const Board *board, Board::Position from)
{
    std::vector<Board::Position>* returnVector = new std::vector<Board::Position>();
    bishopGetValidMovesPattern(board,from,returnVector);
    return returnVector;
}

void Bishop::doMove(Board *board, Board::Position from, Board::Position to)
{

}

std::vector<Board::Position> *Queen::getValidMoves(const Board *board, Board::Position from)
{
    std::vector<Board::Position>* returnVector = new std::vector<Board::Position>();
    bishopGetValidMovesPattern(board,from,returnVector);
    rookGetValidMovesPattern(board,from,returnVector);
    return returnVector;
}

void Queen::doMove(Board *board, Board::Position from, Board::Position to)
{

}