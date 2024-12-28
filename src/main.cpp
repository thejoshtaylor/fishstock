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

    return 0;
}