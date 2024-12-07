// This is the main file for the fishstock project
// (c) Fishstock 2024

#include <iostream>
#include "board.h"
#include "util.h"

int main() {
    std::cout << "Hello, Fishstock!" << std::endl;

    Board board = Board();
    Util::printBoard(&board);
    board.move(1, 1, 3, 1);
    Util::printBoard(&board);
    board.move(6, 2, 4, 2);
    Util::printBoard(&board);
    board.move(3, 1, 4, 2);
    Util::printBoard(&board);

    return 0;
}