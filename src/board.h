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
        WHITE_KNIGHT = 'N',
        WHITE_BISHOP = 'B',
        WHITE_QUEEN = 'Q',
        WHITE_KING = 'K',
        BLACK_PAWN = 'p',
        BLACK_ROOK = 'r',
        BLACK_KNIGHT = 'n',
        BLACK_BISHOP = 'b',
        BLACK_QUEEN = 'q',
        BLACK_KING = 'k'
    };
    

    struct Position
    {
        uint8_t row;
        uint8_t col;
        bool operator==(const Position &other) const
        {
            return row == other.row && col == other.col;
        }
    };

    Board();
    Board(bool isWhiteTurnInput, uint8_t enPassantColInput = 8, bool canCastleInput[] = nullptr);

    
    // lets outside funciton access isWhiteTurn
    bool isWhiteTurnFunc() const;
    // checks if a position is is in bounds
    static bool isInBounds(Position pos);
    // returns a character, if the character is lowercase it makes it uppercase
    static char getPieceLetter(PieceType piece);
    // returns a PieceType val from the pos given, used in pieces.cpp
    PieceType getPiece(Position pos) const;
    // returns true if the piece at pos is white, false otherwise. throws an error if the tile is empty.
    static bool isWhitePiece(PieceType piece);
    // sets the EnPassant flag, 8 is the cleared value. Only cares about the col value, pos.row can be set to whatever.
    void setEnPassant(Position pos);
    bool checkEnPassant(Position pos) const;
    void promotePawn(Position pos, PieceType pieceType);
    // adds a piece to the board, used for making custom boards
    void addPiece(Position pos, PieceType inputPiece);
    void removePiece(Position pos);
    bool isValidMove(Position from, Position to) const;
    void move(Position from, Position to);

protected:
    bool canCastle[2][2];
    uint8_t EnPassantCol;

private:
    PieceType board[8][8];
    bool isWhiteTurn;
    
    // records the column of the last move if double pawn move, cleared state is 8
};

// Base class for all pieces
class Piece
{
protected:
    bool isWhite;

public:
    Piece(bool isWhite) : isWhite(isWhite) {}
    static Piece *pieceObjConstructor(Board::PieceType inputPiece);
    virtual bool isValidMove(const Board *board, Board::Position from, Board::Position to) = 0;
    virtual std::vector<Board::Position> *getValidMoves(const Board *board, Board::Position from) = 0;
    virtual void doMove(Board *board, Board::Position from, Board::Position to) = 0;
};

// Pawn piece
class Pawn : public Piece
{
public:
    Pawn(bool isWhite) : Piece(isWhite) {}
    bool isValidMove(const Board *board, Board::Position from, Board::Position to);
    std::vector<Board::Position> *getValidMoves(const Board *board, Board::Position from);
    void doMove(Board *board, Board::Position from, Board::Position to);
};

// Rook piece
class Rook : public Piece
{
public:
    Rook(bool isWhite) : Piece(isWhite) {}

    bool isValidMove(const Board *board, Board::Position from, Board::Position to);
    std::vector<Board::Position> *getValidMoves(const Board *board, Board::Position from);
    void doMove(Board *board, Board::Position from, Board::Position to);
};

#endif