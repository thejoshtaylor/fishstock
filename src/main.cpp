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

    return 0;
}