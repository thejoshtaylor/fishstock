// This is the main file for the fishstock project
// (c) Fishstock 2024

#include <iostream>
#include "board.h"
#include "util.h"

int main() {
    std::cout << "Hello, Fishstock!" << std::endl;

    Board board = Board(true);
    Util::printBoard(&board);
    board.addPiece((Board::Position){3,3},0);
    Util::printBoard(&board);
    return 0;
}