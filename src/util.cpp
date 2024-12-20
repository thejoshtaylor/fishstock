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
            char c = board->getPieceLetter((Board::Position){i, j});
            Board::Color color = board->getPieceColor((Board::Position){i, j});
            bool white = color == Board::Color::WHITE;

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

Board::Position Util::pos(std::string str)
{
    if (str.length() != 2)
    {
        throw std::invalid_argument("Invalid position");
    }
    if (str[0] < 'a' || str[0] > 'h' || str[1] < '1' || str[1] > '8')
    {
        throw std::invalid_argument("Position out of bounds");
    }
    return (Board::Position){str[1] - '1', str[0] - 'a'};
}

std::string Util::str(Board::Position pos)
{
    if (pos.row > 8 || pos.col > 8)
    {
        throw std::invalid_argument("Position out of bounds");
    }
    char c = pos.col + 'a';
    char r = pos.row + '1';
    return std::string() + c + r;
}
