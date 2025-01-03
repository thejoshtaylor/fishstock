// This is the main file for the fishstock project
// (c) Fishstock 2024

#include <iostream>
#include "board.h"
#include "util.h"

int main() {
    std::cout << "Hello, Fishstock!" << std::endl;


    std::vector<Board::pieceLocationInput> pieceVector;

    //Board::pieceLocationInput tempPiece = {Board::Position{6,4},Board::PieceType::ROOK,Board::Color::BLACK};

    

    pieceVector.push_back({Board::Position{6,4},Board::PieceType::ROOK,Board::Color::BLACK});
    pieceVector.push_back({Board::Position{5,4},Board::PieceType::ROOK,Board::Color::BLACK});
    pieceVector.push_back({Board::Position{3,4},Board::PieceType::KING,Board::Color::BLACK});
    pieceVector.push_back({Board::Position{3,2},Board::PieceType::KING,Board::Color::WHITE});





    Board board = Board(pieceVector,nullptr , nullptr, nullptr,Board::Color::WHITE);

    
    Util::printBoard(&board);

    return 0;
}