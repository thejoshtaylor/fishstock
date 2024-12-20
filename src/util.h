// Header file for the chess utilities class
// (c) Fishstock 2024

#ifndef UTIL_H
#define UTIL_H

#include <fmt/core.h>
#include <fmt/color.h>
#include <string>

class Board;

class Util
{
public:
    static void printBoard(Board *board);
    static Board::Position pos(std::string pos);
};

#endif