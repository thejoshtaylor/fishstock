// Header file for the board class
// (c) Fishstock 2024

#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <stdexcept>
#include <vector>
#include <algorithm>



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
        EMPTY,
        WHITE,
        BLACK
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

    
/// @brief makes a blank board and adds a list of pieces described in a vector to it. It also sets all the different castling and passant flags. If you provide nullpointers to 
///        all three array inputs it will set all the castle and passant stuff to false. dependent on addPiece, which is dependent on reversePieceLookup. throws errors if you give
///        a bad Color to playerTurn, or if your picePosistions vector is bad (bad color for a piece, or trying to add a piece on top of another piece)
/// @param piecePosistions vector of a struct that takes in a pos struct, a piece type, and a piece color.
/// @param canCastleMapping 2 by 2 array of bools
/// @param canEnPassantMapping 2 by 8 array of bools
/// @param pawnPromoteMapping 2 by 8 array of piece types, from the mind of josh, hate it.
/// @param playerTurn Color enum
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


    /// @brief makes use of reversePieceLookup, goes through the whole board looking for id's that have already been taken, and finds an id that is not reserved yet if one exists.
    ///        throws an error if none exists. also throws an error if you try to add a piece on top of an existing piece.
    /// @param inputPiece const reference to a pieceLocationInput struct, to make one you need a Color, Pos, and PieceType.
    void addPiece(const pieceLocationInput& inputPiece);


    /// @brief does the opposite of getPieceType, given a PieceType and color it fills a given array with possible id's. output size ranges from 1 to 8, given array has to be size 9
    /// @param PieceInput type of the piece
    /// @param PieceColor color of the piece
    /// @param outputArray has to be a size 9 array of -1's
    /// @return size of the list of numbers it adds to outputArray
    int reversePieceLookup(PieceType PieceInput, Color PieceColor, uint8_t outputArray[]); // does the opposite of getPieceType, takes a piece kind and gives possible id's  
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