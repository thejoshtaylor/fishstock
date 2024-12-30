// This is the main file for the fishstock project
// (c) Fishstock 2024

#include <iostream>
#include "board.h"
#include "util.h"

int main() {
    std::cout << "Hello, Fishstock!" << std::endl;


    std::vector<Board::pieceLocationInput> pieceVector;

    Board::pieceLocationInput tempPiece;

    tempPiece.PieceColor = Board::Color::WHITE;
    tempPiece.pieceKind = Board::PieceType::KNIGHT;
    tempPiece.piecePos.row = 4;
    tempPiece.piecePos.col = 6;

    pieceVector.push_back(tempPiece);





    Board board = Board(pieceVector,nullptr , nullptr, nullptr,Board::Color::WHITE);

    
    Util::printBoard(&board);

    return 0;
}