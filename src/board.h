// Header file for the board class
// (c) Fishstock 2024

#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <stdexcept>

class Board
{
public:
    enum class PieceType : uint8_t
    {
        PAWN,
        ROOK,
        KNIGHT,
        BISHOP,
        QUEEN,
        KING
    };

    enum class Color
    {
        WHITE,
        BLACK,
        EMPTY
    };

    Board();

    char getPieceLetter(int row, int col);
    Color getPieceColor(int row, int col);
    void setEnPassant(int row, int col);
    bool checkEnPassant(int row, int col);
    void promotePawn(int row, int col, PieceType pieceType);
    void removePiece(int row, int col);
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol);
    void move(int fromRow, int fromCol, int toRow, int toCol);

private:
    uint8_t board[8][8];
    Color turn;
    bool canCastle[2][2];
    bool canEnPassant[2][8];
    PieceType pawnPromote[2][8];

    PieceType getPieceType(uint8_t piece);
};

// Base class for all pieces
class Piece
{
protected:
    Board::Color color;

public:
    Piece(Board::Color color) : color(color) {}

    virtual bool isValidMove(Board *board, uint8_t fromRow, uint8_t fromCol, uint8_t toRow, uint8_t toCol) = 0;
    virtual void getValidMoves(Board *board, uint8_t fromRow, uint8_t fromCol) = 0;
    virtual void doMove(Board *board, int fromRow, int fromCol, int toRow, int toCol) = 0;
};

// Pawn piece
class Pawn : public Piece
{
public:
    Pawn(Board::Color color) : Piece(color) {}

    bool isValidMove(Board *board, uint8_t fromRow, uint8_t fromCol, uint8_t toRow, uint8_t toCol);
    void getValidMoves(Board *board, uint8_t fromRow, uint8_t fromCol);
    void doMove(Board *board, int fromRow, int fromCol, int toRow, int toCol);
};

#endif