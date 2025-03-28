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
    for (int i = 2; i < 6; ++i)
    {

        for (int j = 0; j < 8; ++j)
        {
            board[i][j] = PieceType::EMPTY;
        }
    }

    for (int i = 0; i < 8; ++i)
    {
        board[1][i] = PieceType::WHITE_PAWN;
        board[6][i] = PieceType::BLACK_PAWN;
    }

    board[0][0] = PieceType::WHITE_ROOK;
    board[0][7] = PieceType::WHITE_ROOK;
    board[7][0] = PieceType::BLACK_ROOK;
    board[7][7] = PieceType::BLACK_ROOK;

    board[0][1] = PieceType::WHITE_KNIGHT;
    board[0][6] = PieceType::WHITE_KNIGHT;
    board[7][1] = PieceType::BLACK_KNIGHT;
    board[7][6] = PieceType::BLACK_KNIGHT;

    board[0][2] = PieceType::WHITE_BISHOP;
    board[0][5] = PieceType::WHITE_BISHOP;
    board[7][2] = PieceType::BLACK_BISHOP;
    board[7][5] = PieceType::BLACK_BISHOP;

    board[0][4] = PieceType::WHITE_KING;
    board[0][3] = PieceType::WHITE_QUEEN;
    board[7][3] = PieceType::BLACK_QUEEN;
    board[7][4] = PieceType::BLACK_KING;
}

bool Board::isWhiteTurnFunc() const
{
    return isWhiteTurn;
}

bool Board::isInBounds(Position pos)
{
    return !(pos.row < 0 || pos.row > 7 || pos.col < 0 || pos.col > 7);
}

char Board::getPieceLetter(PieceType piece)
{
    // changes a PieceType into a char, alwas the uppercase version which is why we subtract 32 from lowercase PieceTypes. Used in util for the print function
    return ((char)piece < 'a' ? (char)piece : (char)((int)piece - 32));
}

Board::PieceType Board::getPiece(Position pos) const
{
    if (pos.row < 0 || pos.row > 7 || pos.col < 0 || pos.col > 7)
    {
        throw invalid_argument("Invalid pos.row or column");
    }
    return board[pos.row][pos.col];
}

bool Board::isWhitePiece(PieceType piece)
{
    if ((char)piece < 'A' || (char)piece > 'z')
        throw invalid_argument("invalid symbol at pos given");
    return (char)piece < 'a';
}

// Set the en passant position
void Board::setEnPassant(Position pos)
{
    EnPassantCol = pos.col;
}

void Board::setCanCastleToFalse(uint8_t row, uint8_t col)
{
    canCastle[row][col] = false;
}

// Private exposure of the en passant check
bool Board::checkEnPassant(Position pos) const
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
bool Board::isValidMove(Position from, Position to) const
{
    PieceType fromPiece = getPiece(from);

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
    if (board[to.row][to.col] != PieceType::EMPTY)
    {
        if (isWhitePiece(fromPiece) == isWhitePiece(getPiece(to)))
        {
            return false;
        }
    }

    // Check if it's this pieces turn
    if (isWhitePiece(fromPiece) != isWhiteTurn)
    {
        return false;
    }

    // Piece-specific move validation
    Piece *pieceObj = Piece::pieceObjConstructor(fromPiece);

    std::vector<Position> *allValidMoves = pieceObj->getValidMoves(this, from);

    bool isValid = false;
    for (int i = 0; i < allValidMoves->size(); ++i)
    {
        if (allValidMoves->at(i) == to)
        {
            isValid = true;
            break;
        }
    }
    delete pieceObj;
    return isValid;
}

// Execute a move on the board
void Board::move(Position from, Position to)
{
    if (board[from.row][from.col] != PieceType::WHITE_PAWN && board[from.row][from.col] != PieceType::BLACK_PAWN)
    {
        EnPassantCol = 8;
    }
    // Check if the move is valid
    if (!isValidMove(from, to))
    {
        throw invalid_argument("Invalid move");
    }

    // Move the piece
    PieceType piece = getPiece(from);
    board[from.row][from.col] = PieceType::EMPTY;

    // Tell the piece that we're moving
    Piece *pieceObj = Piece::pieceObjConstructor(piece);
    pieceObj->doMove(this, from, to);

    // Finish the move
    board[to.row][to.col] = piece;

    // Update the turn
    isWhiteTurn = !isWhiteTurn;
    delete pieceObj;
}
