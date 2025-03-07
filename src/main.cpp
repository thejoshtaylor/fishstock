// This is the main file for the fishstock project
// (c) Fishstock 2024

#include <iostream>
#include "board.h"
#include "util.h"

int main() {
    std::cout << "Hello, Fishstock!" << std::endl;

    Board board = Board();
    Util::printBoard(&board);
    board.move((Board::Position){1, 1}, (Board::Position){3, 1});
    Util::printBoard(&board);
    board.move((Board::Position){6, 2}, (Board::Position){4, 2});
    Util::printBoard(&board);
    board.move((Board::Position){3, 1}, (Board::Position){4, 2});
    Util::printBoard(&board);
    board.move((Board::Position){6, 3}, (Board::Position){4, 3});
    Util::printBoard(&board);

    /*
    // Take en passant
    board.move((Board::Position){4, 2}, (Board::Position){5, 3});
    Util::printBoard(&board);

    // Try non en passantable
    board.move((Board::Position){6, 7}, (Board::Position){5, 7});
    Util::printBoard(&board);
    board.move((Board::Position){1, 5}, (Board::Position){3, 5});
    Util::printBoard(&board);
    board.move((Board::Position){5, 7}, (Board::Position){4, 7});
    Util::printBoard(&board);
    board.move((Board::Position){3, 5}, (Board::Position){4, 5});
    Util::printBoard(&board);
    board.move((Board::Position){6, 6}, (Board::Position){4, 6});
    Util::printBoard(&board);
    board.move((Board::Position){1, 0}, (Board::Position){2, 0});
    Util::printBoard(&board);
    board.move((Board::Position){6, 0}, (Board::Position){5, 0});
    Util::printBoard(&board);

    // Try en passantable that shouldn't work
    try {
        board.move((Board::Position){4, 5}, (Board::Position){5, 6});
    } catch (std::invalid_argument &e) {
        std::cout << "CORRECTLY Caught exception: " << e.what() << std::endl;
    }

    */



    //testing getValidMoves stuff
    Board::Position pos;
    pos.row = 1;
    pos.col = 0;

    // making the pointer to the output vector, danger of memory leak
    std::vector<Board::Position>* getValidMovesOutput;
    Board::PieceType piece = board.getPiece(pos);
    std::cout << board.getPieceLetter(board.getPiece(pos)) << std::endl;
    Piece *pieceObj = Piece::pieceObjConstructor(piece);
    getValidMovesOutput = pieceObj->getValidMoves(&board,pos);

    std::cout << "list of posible moves for piece at " << (int)pos.row << ", " << (int)pos.col << std::endl;

    for (int i = 0; i < getValidMovesOutput->size(); ++i)
    {
        std::cout << (int)getValidMovesOutput->at(i).row << ", " << (int)getValidMovesOutput->at(i).col << std::endl;
    }


    delete getValidMovesOutput;
    delete pieceObj;

    return 0;
}