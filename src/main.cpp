// This is the main file for the fishstock project
// (c) Fishstock 2024

#include <iostream>
#include "board.h"
#include "util.h"

int main() {



    //testing getValidMoves stuff
    Board::Position pos;
    pos.row = 3;
    pos.col = 3;

    Board board = Board(true);
    Util::printBoard(&board);
    board.addPiece((Board::Position){pos.row,pos.col},Board::PieceType::WHITE_ROOK);
    Util::printBoard(&board);

    // making the pointer to the output vector, danger of memory leak
    std::vector<Board::Position>* getValidMovesOutput;
    Board::PieceType piece = board.getPiece(pos);
    std::cout << board.getPieceLetter(board.getPiece(pos)) << std::endl;
    Piece *pieceObj = Piece::pieceObjConstructor(piece);
    getValidMovesOutput = pieceObj->getValidMoves(&board,pos);

    std::cout << "list of posible moves for piece at " << (int)pos.row << ", " << (int)pos.col << std::endl;

    for (int i = 0; i < getValidMovesOutput->size(); ++i)
    {
        //std::cout << (int)getValidMovesOutput->at(i).row << ", " << (int)getValidMovesOutput->at(i).col << std::endl;
        if (board.getPiece((Board::Position){getValidMovesOutput->at(i).row,getValidMovesOutput->at(i).col}) == Board::PieceType::EMPTY)
        {
            board.addPiece((Board::Position){getValidMovesOutput->at(i).row,getValidMovesOutput->at(i).col},Board::PieceType::BLACK_PAWN);    
        }
        else
        {
            //std::cout << 
        }
    }
    Util::printBoard(&board);



    delete getValidMovesOutput;
    delete pieceObj;






    return 0;
}