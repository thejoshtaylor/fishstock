// Header file for the board class
// (c) Fishstock 2024

#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <stdexcept>
#include <vector>

class Board
{
public:
    enum class PieceType : char
    {
        EMPTY = ' ',
        WHITE_PAWN = 'p',
        WHITE_ROOK = 'r',
        WHITE_KNIGHT = 'k',
        WHITE_BISHOP = 'b',
        WHITE_QUEEN = 'q',
        WHITE_KING = 'k',
        BLACK_PAWN = 'P',
        BLACK_ROOK = 'R',
        BLACK_KNIGHT = 'K',
        BLACK_BISHOP = 'B',
        BLACK_QUEEN = 'Q',
        BLACK_KING = 'K'
    };

    

    struct Position
    {
        uint8_t row;
        uint8_t col;
    };

    Board();

    char getPieceLetter(Position pos);
    void setEnPassant(Position pos);
    bool checkEnPassant(Position pos);
    void promotePawn(Position pos, PieceType pieceType);
    void removePiece(Position pos);
    bool isValidMove(Position from, Position to);
    void move(Position from, Position to);

private:
    char board[8][8];
    bool isWhiteTurn;
    bool canCastle[2][2];
    uint8_t canEnPassant;
};

// Base class for all pieces
class Piece
{
protected:
    Board::PieceType PieceType;

public:
    Piece(Board::PieceType pieceType) : PieceType(pieceType) {}

    virtual bool isValidMove(Board *board, Board::Position from, Board::Position to) = 0;
    virtual std::vector<Board::Position>* getValidMoves(Board *board, Board::Position from) = 0;
    virtual void doMove(Board *board, Board::Position from, Board::Position to) = 0;
};

// Pawn piece
class Pawn : public Piece
{
public:
    Pawn(Board::PieceType pieceType) : Piece(pieceType) {}

    bool isValidMove(Board *board, Board::Position from, Board::Position to);
    std::vector<Board::Position>* getValidMoves(Board *board, Board::Position from);
    void doMove(Board *board, Board::Position from, Board::Position to);
};

// Rook piece
class Rook : public Piece
{
public:
    Rook(Board::PieceType pieceType) : Piece(pieceType) {}

    bool isValidMove(Board *board, Board::Position from, Board::Position to);
    std::vector<Board::Position>* getValidMoves(Board *board, Board::Position from);
    void doMove(Board *board, Board::Position from, Board::Position to);
};

#endif