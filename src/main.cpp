// This is the main file for the fishstock project
// (c) Fishstock 2024

#include <iostream>
#include "board.h"
#include "util.h"

int main() {
    std::cout << "Hello, Fishstock!" << std::endl;

    Board board = Board();
    Util::printBoard(&board);
    board.move(Util::pos("b2"), Util::pos("b4"));
    Util::printBoard(&board);
    board.move(Util::pos("c7"), Util::pos("c5"));
    Util::printBoard(&board);
    board.move(Util::pos("b4"), Util::pos("c5"));
    Util::printBoard(&board);

    return 0;
}