// This is the main file for the fishstock project
// (c) Fishstock 2024

#include <iostream>
#include "board.h"
#include "util.h"

int main() {
    std::cout << "Hello, Fishstock!" << std::endl;


    std::vector<Board::pieceLocationInput> pieceVector;
    

    for (int loopCount = 0; loopCount < 8; ++loopCount)
    {
        pieceVector.push_back({Board::Position{(uint8_t)loopCount,0},Board::PieceType::PAWN,Board::Color::BLACK});
    }

    Board board = Board(pieceVector,nullptr , nullptr, nullptr,Board::Color::WHITE);

    
    Util::printBoard(&board);

    return 0;
}