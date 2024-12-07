// Chess board and rules implementation
// (c) Fishstock 2024

#include "board.h"

using namespace std;

Board::Board()
{
    turn = Color::WHITE;

    canCastle[0][0] = true;
    canCastle[0][1] = true;
    canCastle[1][0] = true;
    canCastle[1][1] = true;
    for (int i = 0; i < 8; i++)
    {
        canEnPassant[0][i] = false;
        canEnPassant[1][i] = false;
    }
    for (int i = 0; i < 8; i++)
    {
        pawnPromote[0][i] = PieceType::PAWN;
        pawnPromote[1][i] = PieceType::PAWN;
    }

    // Board layout is from a1 to h8 and the value is the piece index
    for (int i = 0; i < 8; i++)
    {
        // White pieces
        board[0][i] = i;
        board[1][i] = i + 8;

        // Black pieces
        board[7][i] = i + 16;
        board[6][i] = i + 24;

        // Empty spaces
        for (int j = 2; j < 6; j++)
        {
            board[j][i] = 32;
        }
    }
}

char Board::getPieceLetter(int row, int col)
{
    // Validate the row and column
    if (row < 0 || row > 7 || col < 0 || col > 7)
    {
        throw invalid_argument("Invalid row or column");
    }

    // Validate that it's not empty
    if (board[row][col] == 32)
    {
        return ' ';
    }

    // Get the piece type
    PieceType pt = getPieceType(board[row][col]);

    // Get the piece letter
    switch (pt)
    {
    case PieceType::PAWN:
        return 'P';
    case PieceType::ROOK:
        return 'R';
    case PieceType::KNIGHT:
        return 'N';
    case PieceType::BISHOP:
        return 'B';
    case PieceType::QUEEN:
        return 'Q';
    case PieceType::KING:
        return 'K';
    default:
        throw invalid_argument("Invalid piece type");
    }
}

// Get the type of a piece from its location
Board::Color Board::getPieceColor(int row, int col)
{
    // Validate the row and column
    if (row < 0 || row > 7 || col < 0 || col > 7)
    {
        throw invalid_argument("Invalid row or column");
    }

    // Get the color of the piece
    if (board[row][col] >= 32)
    {
        return Color::EMPTY;
    }
    else if (board[row][col] < 16)
    {
        return Color::WHITE;
    }
    else
    {
        return Color::BLACK;
    }
}

// Set the en passant position
void Board::setEnPassant(int row, int col)
{
    // Validate the row and column
    if ((row != 1 && row != 6) || col < 0 || col > 7)
    {
        throw invalid_argument("Invalid row or column");
    }

    // Set the en passant position
    if (row == 1)
    {
        canEnPassant[0][col] = true;
    }
    else
    {
        canEnPassant[1][col] = true;
    }
}

// Private exposure of the en passant check
bool Board::checkEnPassant(int row, int col)
{
    // Validate the row and column
    if (col < 0 || col > 7)
    {
        throw invalid_argument("Invalid column");
    }
    
    // Check if this is a valid en passant row
    if (row != 2 && row != 5)
    {
        return false;
    }

    // Check if the en passant is valid
    if (row == 2)
    {

        return canEnPassant[0][col];
    }
    else
    {
        return canEnPassant[1][col];
    }
}

void Board::promotePawn(int row, int col, PieceType pieceType)
{
    // Validate the row and column
    if (row < 0 || row > 7 || col < 0 || col > 7)
    {
        throw invalid_argument("Invalid row or column");
    }

    // Get pawn id
    uint8_t piece = board[row][col];
    if (piece < 8 || piece > 15)
    {
        throw invalid_argument("Invalid piece ID");
    }

    // Promote the pawn
    pawnPromote[piece < 16][piece % 8] = pieceType;
}

// Remove a piece from the board
void Board::removePiece(int row, int col)
{
    // Validate the row and column
    if (row < 0 || row > 7 || col < 0 || col > 7)
    {
        throw invalid_argument("Invalid row or column");
    }

    // Remove the piece
    board[row][col] = 32;
}

// Get the type of a piece from its ID
Board::PieceType Board::getPieceType(uint8_t pieceId)
{
    // Validate the piece ID
    if (pieceId > 31)
    {
        throw invalid_argument("Invalid piece ID");
    }

    switch (pieceId % 16)
    {
    case 0:
    case 7:
        return PieceType::ROOK;
    case 1:
    case 6:
        return PieceType::KNIGHT;
    case 2:
    case 5:
        return PieceType::BISHOP;
    case 3:
        return PieceType::QUEEN;
    case 4:
        return PieceType::KING;
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        // Check if we've promoted a pawn
        return pawnPromote[pieceId < 16][pieceId % 16 - 8];
    default:
        throw invalid_argument("Invalid piece ID");
    }
}

// Check if a proposed move is valid
bool Board::isValidMove(int fromRow, int fromCol, int toRow, int toCol)
{
    // Check if the move is within the board
    if (fromRow < 0 || fromRow > 7 || fromCol < 0 || fromCol > 7 || toRow < 0 || toRow > 7 || toCol < 0 || toCol > 7)
    {
        return false;
    }

    // Check if the piece actually exists
    if (board[fromRow][fromCol] == 32)
    {
        return false;
    }

    // Check if the piece is moving to the same position
    if (fromRow == toRow && fromCol == toCol)
    {
        return false;
    }

    // Check if the piece is moving to the same color
    Color fromColor = getPieceColor(fromRow, fromCol);
    Color toColor = getPieceColor(toRow, toCol);
    if (fromColor == toColor)
    {
        return false;
    }

    // Check if it's this pieces turn
    if (fromColor != turn)
    {
        return false;
    }

    // Piece-specific move validation
    uint8_t piece = board[fromRow][fromCol];
    PieceType pieceType = getPieceType(piece);

    Piece *pieceObj;
    pieceObj = new Pawn(fromColor);
    if (!pieceObj->isValidMove(this, fromRow, fromCol, toRow, toCol))
    {
        return false;
    }

    return true;
}

// Execute a move on the board
void Board::move(int fromRow, int fromCol, int toRow, int toCol)
{
    // Check if the move is valid
    if (!isValidMove(fromRow, fromCol, toRow, toCol))
    {
        throw invalid_argument("Invalid move");
    }

    // Move the piece
    uint8_t piece = board[fromRow][fromCol];
    board[fromRow][fromCol] = 32;

    // Tell the piece that we're moving
    PieceType pieceType = getPieceType(piece);
    Piece *pieceObj;
    pieceObj = new Pawn(getPieceColor(fromRow, fromCol));
    pieceObj->doMove(this, fromRow, fromCol, toRow, toCol);
    
    // Finish the move
    board[toRow][toCol] = piece;

    // Update the turn
    if (turn == Color::WHITE)
    {
        turn = Color::BLACK;
    }
    else
    {
        turn = Color::WHITE;
    }
}
