// Utilities for the operating the chess game
// (c) Fishstock 2024

#include "board.h"
#include "util.h"

void Util::printBoard(Board *board)
{
    fmt::print(fg(fmt::color::turquoise) | fmt::emphasis::bold,
               "   a  b  c  d  e  f  g  h\n");
    for (int i = 7; i >= 0; i--)
    {
        fmt::print(fg(fmt::color::turquoise) | fmt::emphasis::bold,
                   "{} ", i + 1);
        for (int j = 0; j < 8; j++)
        {
            char c = board->getPieceLetter(board->getPiece((Board::Position){i, j}));

            // doesnt matter what the white var is on a blank tile, but I can only call isWhitePiece on an occupied tile
            bool white = false;
            if (board->getPiece((Board::Position){i, j}) != Board::PieceType::EMPTY)
            {
                white = board->isWhitePiece(board->getPiece((Board::Position){i, j}));;
            }
            
            fmt::print(fg(white ? fmt::color::dark_red : fmt::color::black) | bg((i+j) % 2 == 1 ? fmt::color::light_gray : fmt::color::lime_green) | fmt::emphasis::bold,
                       " {} ", c);
        }
        fmt::print(fg(fmt::color::turquoise) | fmt::emphasis::bold,
                   " {}", i + 1);
        fmt::print("\n");
    }
    fmt::print(fg(fmt::color::turquoise) | fmt::emphasis::bold,
               "   a  b  c  d  e  f  g  h\n");
    fmt::print("\n");
}
