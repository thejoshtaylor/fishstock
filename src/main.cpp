// This is the main file for the fishstock project
// (c) Fishstock 2024

#include <iostream>
#include "board.h"
#include "util.h"

int main() {
    std::cout << "Hello, Fishstock!" << std::endl;


    std::vector<Board::pieceLocationInput> listOfPiecesTemp;

    Board::pieceLocationInput tempPiece;
    tempPiece.piecePos = (Board::Position){3, 4};
    tempPiece.pieceKind = Board::PieceType::KNIGHT;
    tempPiece.PieceColor = Board::Color::BLACK;

    listOfPiecesTemp.push_back(tempPiece);

    Board board = Board(listOfPiecesTemp, nullptr, nullptr, nullptr, Board::Color::WHITE);

    /*
    
    Util::printBoard(&board);
    board.move((Board::Position){1, 1}, (Board::Position){3, 1});
    Util::printBoard(&board);
    board.move((Board::Position){6, 2}, (Board::Position){4, 2});
    Util::printBoard(&board);
    board.move((Board::Position){3, 1}, (Board::Position){4, 2});
    Util::printBoard(&board);

    */
    return 0;
}