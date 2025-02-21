// Header file for the board class
// (c) Fishstock 2024

#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <stdexcept>
#include <vector>
#include <iostream>
class Board
{
public:
    enum class PieceType : char
    {
        EMPTY = ' ',
        WHITE_PAWN = 'P',
        WHITE_ROOK = 'R',
        WHITE_KNIGHT = 'K',
        WHITE_BISHOP = 'B',
        WHITE_QUEEN = 'Q',
        WHITE_KING = 'K',
        BLACK_PAWN = 'p',
        BLACK_ROOK = 'r',
        BLACK_KNIGHT = 'k',
        BLACK_BISHOP = 'b',
        BLACK_QUEEN = 'q',
        BLACK_KING = 'k'
    };

    

    struct Position
    {
        uint8_t row;
        uint8_t col;
    };

    Board();

    char getPieceLetter(Position pos);
    PieceType getPiece(Position pos);
    bool isWhitePiece(Position pos);
    void setEnPassant(Position pos);
    bool checkEnPassant(Position pos);
    void promotePawn(Position pos, PieceType pieceType);
    void removePiece(Position pos);
    bool isValidMove(Position from, Position to);
    void move(Position from, Position to);

private:
    PieceType board[8][8];
    bool isWhiteTurn;
    bool canCastle[2][2];
    // records the column of the last move if double pawn move, cleared state is 8
    uint8_t EnPassantCol;
    uint8_t currentEnPassant;
};

// Base class for all pieces
class Piece
{
protected:
    bool isWhite;

public:
    Piece(bool inputColor) : isWhite(inputColor) {}

    virtual bool isValidMove(Board *board, Board::Position from, Board::Position to) = 0;
    virtual std::vector<Board::Position>* getValidMoves(Board *board, Board::Position from) = 0;
    virtual void doMove(Board *board, Board::Position from, Board::Position to) = 0;
};

// Pawn piece
class Pawn : public Piece
{
public:
    Pawn(bool inputColor) : Piece(inputColor) {}

    bool isValidMove(Board *board, Board::Position from, Board::Position to);
    std::vector<Board::Position>* getValidMoves(Board *board, Board::Position from);
    void doMove(Board *board, Board::Position from, Board::Position to);
};

// Rook piece
class Rook : public Piece
{
public:
    Rook(bool inputColor) : Piece(inputColor) {}

    bool isValidMove(Board *board, Board::Position from, Board::Position to);
    std::vector<Board::Position>* getValidMoves(Board *board, Board::Position from);
    void doMove(Board *board, Board::Position from, Board::Position to);
};

#endif