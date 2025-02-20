// Chess board and rules implementation
// (c) Fishstock 2024

#include "board.h"


using namespace std;

Board::Board()
{
    isWhiteTurn = true;

    canCastle[0][0] = true;
    canCastle[0][1] = true;
    canCastle[1][0] = true;
    canCastle[1][1] = true;
    EnPassantCol = 8;

    // Board layout is from a1 to h8 and the value is the piece index
    // NEEDS TO BE REDONE
    for (int i = 0; i < 8; ++i)
    {

        for (int j = 0; j < 8; ++j)
         {
            board[i][j] = PieceType::EMPTY;
         }
    }

    for (int i = 0; i < 8; ++i)
    {
        board[1][i] = PieceType::WHITE_PAWN;
    }



}

char Board::getPieceLetter(Position pos)
{
    // Validate the pos.row and column
    if (pos.row < 0 || pos.row > 7 || pos.col < 0 || pos.col > 7)
    {
        throw invalid_argument("Invalid pos.row or column");
    }

    return (char(board[pos.row][pos.col]) < 'a' ? char(board[pos.row][pos.col]) : char( uint8_t(board[pos.row][pos.col]) - 32));

   
}

Board::PieceType Board::getPiece(Position pos)
{
    if (pos.row < 0 || pos.row > 7 || pos.col < 0 || pos.col > 7)
    {
        throw invalid_argument("Invalid pos.row or column");
    }
    return board[pos.row][pos.col];

}


// Set the en passant position
void Board::setEnPassant(Position pos)
{
    // Validate the pos.row and column
    if ((pos.row != 1 && pos.row != 6) || pos.col < 0 || pos.col > 7)
    {
        throw invalid_argument("Invalid pos.row or column");
    }

    EnPassantCol = pos.col;
}
// Private exposure of the en passant check
bool Board::checkEnPassant(Position pos)
{
    // Validate the pos.row and column
    if (pos.col < 0 || pos.col > 7)
    {
        throw invalid_argument("Invalid column");
    }

    // Check if this is a valid en passant pos.row
    if (pos.row != 2 && pos.row != 5)
    {
        return false;
    }

    // Check if the en passant is valid
    return (pos.col == EnPassantCol);


}

void Board::promotePawn(Position pos, PieceType pieceType)
{
    // Validate the pos.row and column
    if (pos.row < 0 || pos.row > 7 || pos.col < 0 || pos.col > 7)
    {
        throw invalid_argument("Invalid pos.row or column");
    }

    if (pieceType == PieceType::BLACK_PAWN || pieceType == PieceType::WHITE_PAWN || pieceType == PieceType::EMPTY)
    {
        throw invalid_argument("invalid promotion type");
    }

    board[pos.row][pos.col] = pieceType;


}

// Remove a piece from the board
void Board::removePiece(Position pos)
{
    // Validate the pos.row and column
    if (pos.row < 0 || pos.row > 7 || pos.col < 0 || pos.col > 7)
    {
        throw invalid_argument("Invalid pos.row or column");
    }

    // Remove the piece
    board[pos.row][pos.col] = PieceType::EMPTY;
}


// Check if a proposed move is valid
bool Board::isValidMove(Position from, Position to)
{
    // Check if the move is within the board
    if (from.row < 0 || from.row > 7 || from.col < 0 || from.col > 7 || to.row < 0 || to.row > 7 || to.col < 0 || to.col > 7)
    {
        return false;
    }

    // Check if the piece actually exists
    if (board[from.row][from.col] == PieceType::EMPTY)
    {
        return false;
    }

    // Check if the piece is moving to the same position
    if (from.row == to.row && from.col == to.col)
    {
        return false;
    }


    // Check if the piece is moving to the same color
    bool fromPosIsWhite = (char(board[from.row][from.col]) < 'a');
    bool ToPosIsWhite = (char(board[to.row][to.col]) < 'a');


    if (fromPosIsWhite == ToPosIsWhite)
    {
        return false;
    }

    // Check if it's this pieces turn
    if (fromPosIsWhite != isWhiteTurn)
    {
        return false;
    }

    // Piece-specific move validation
    PieceType pieceType = board[from.row][from.col];
    if (!fromPosIsWhite)
    {
        pieceType = PieceType(char(pieceType) - 32);
    }

    Piece *pieceObj;
    switch (pieceType)
    {
    case PieceType::WHITE_PAWN:
        pieceObj = new Pawn(fromPosIsWhite);
        break;

    default:
        throw invalid_argument("Invalid piece type");
        break;
    }

    if (!pieceObj->isValidMove(this, from, to))
    {
        return false;
    }

    return true;
}

// Execute a move on the board
void Board::move(Position from, Position to)
{
    // setting EnPassant to an invalid column, will get reset by the piece specific do move function if it is the right pawn move
    EnPassantCol = 8;

    // Check if the move is valid
    if (!isValidMove(from, to))
    {
        throw invalid_argument("Invalid move");
    }
    std::cout << "meep" << std::endl;

    // Move the piece
    PieceType piece = board[from.row][from.col];
    board[from.row][from.col] = PieceType::EMPTY;

    // Tell the piece that we're moving
    Piece *pieceObj;
    //converting black to white for piece kind
    PieceType upperCase = (char(piece) >= 'a' ? PieceType(char(piece) - 32) : piece);
    //geting piece color
    std::cout << char(upperCase) << std::endl;
    bool isWhite = (char(piece) < 'a');
    switch (upperCase)
    {
    case PieceType::WHITE_PAWN:
        pieceObj = new Pawn(isWhite);
        break;
    
    default:
        throw invalid_argument("Invalid piece type");
        break;
    }

    pieceObj->doMove(this,from,to);

    // Finish the move
    board[to.row][to.col] = piece;

    // Update the turn
    isWhiteTurn = !isWhiteTurn;
}
