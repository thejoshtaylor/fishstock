// Header file for the board class
// (c) Fishstock 2024

#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <stdexcept>
#include <vector>
#include <iostream> // REMOVE IN FINAL PUSH!!!!


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

    struct Position
    {
        uint8_t row;
        uint8_t col;
    };


    struct pieceLocationInput
    {
        Position piecePos;
        PieceType pieceKind;
        Color PieceColor;
    };


    Board();
    Board(const std::vector<pieceLocationInput>& piecePosistions, bool canCastleMapping[],bool canEnPassantMapping[], PieceType pawnPromoteMapping[], Color playerTurn);

    char getPieceLetter(Position pos);
    Color getPieceColor(Position pos);
    void setEnPassant(Position pos);
    bool checkEnPassant(Position pos);
    void promotePawn(Position pos, PieceType pieceType);
    void removePiece(Position pos);
    bool isValidMove(Position from, Position to);
    void move(Position from, Position to);

private:
    uint8_t board[8][8];
    Color turn;
    bool canCastle[2][2];
    bool canEnPassant[2][8];
    PieceType pawnPromote[2][8];

    void addPiece(const pieceLocationInput& inputPiece);
    std::vector<uint8_t> reversePieceLookup(PieceType PieceInput, Color PieceColor); // does the opposite of getPieceType, takes a piece kind and gives possible id's  
    PieceType getPieceType(uint8_t piece);
};

// Base class for all pieces
class Piece
{
protected:
    Board::Color color;

public:
    Piece(Board::Color color) : color(color) {}

    virtual bool isValidMove(Board *board, Board::Position from, Board::Position to) = 0;
    virtual std::vector<Board::Position>* getValidMoves(Board *board, Board::Position from) = 0;
    virtual void doMove(Board *board, Board::Position from, Board::Position to) = 0;
};

// Pawn piece
class Pawn : public Piece
{
public:
    Pawn(Board::Color color) : Piece(color) {}

    bool isValidMove(Board *board, Board::Position from, Board::Position to);
    std::vector<Board::Position>* getValidMoves(Board *board, Board::Position from);
    void doMove(Board *board, Board::Position from, Board::Position to);
};

// Rook piece
class Rook : public Piece
{
public:
    Rook(Board::Color color) : Piece(color) {}

    bool isValidMove(Board *board, Board::Position from, Board::Position to);
    std::vector<Board::Position>* getValidMoves(Board *board, Board::Position from);
    void doMove(Board *board, Board::Position from, Board::Position to);
};

#endif