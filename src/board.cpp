// Chess board and rules implementation
// (c) Fishstock 2024

#include "board.h"

using namespace std;

Board::Board()
{
    turn = Color::WHITE;

    canCastle[0][0] = true;
    canCastle[0][1] = true;
    canCastle[1][0] = true;
    canCastle[1][1] = true;
    for (int i = 0; i < 8; i++)
    {
        canEnPassant[0][i] = false;
        canEnPassant[1][i] = false;
    }
    for (int i = 0; i < 8; i++)
    {
        pawnPromote[0][i] = PieceType::PAWN;
        pawnPromote[1][i] = PieceType::PAWN;
    }

    // Board layout is from a1 to h8 and the value is the piece index
    for (int i = 0; i < 8; i++)
    {
        // White pieces
        board[0][i] = i;
        board[1][i] = i + 8;

        // Black pieces
        board[7][i] = i + 16;
        board[6][i] = i + 24;

        // Empty spaces
        for (int j = 2; j < 6; j++)
        {
            board[j][i] = 32;
        }
    }
}


Board::Board( const std::vector<pieceLocationInput>& piecePosistions, bool canCastleMapping[], bool canEnPassantMapping[],  PieceType pawnPromoteMapping[], Color playerTurn)
{

    if (playerTurn != Color::EMPTY)
    {
        throw invalid_argument("Invalid player turn");
    }

    turn = playerTurn;


    int index = 0; 
    for (int row = 0; row < 2; ++row)
    {
        for (int col = 0; col < 2; ++col)
        {
            canCastle[row][col] = canCastleMapping[index];
            ++index;

        }


    }
    

    index = 0; 
    for (int row = 0; row < 2; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            canEnPassant[row][col] = canEnPassantMapping[index];
            ++index;

        }


    }

    index = 0;
    for (int row = 0; row < 2; ++row)
    {
        for (int col = 0; col < 8; ++col)
       {
            pawnPromote[row][col] = pawnPromoteMapping[index];
            ++index;
        
       }

    }
   

    // making an empty board so we can populate it with pieces from our input vector
    for (int row = 0; row < 8; row++)
    {
        // Empty spaces
        for (int col = 0; col < 8; col++)
        {
            board[row][col] = 32;
        }
    }

}



char Board::getPieceLetter(Position pos)
{
    // Validate the pos.row and column
    if (pos.row < 0 || pos.row > 7 || pos.col < 0 || pos.col > 7)
    {
        throw invalid_argument("Invalid pos.row or column");
    }

    // Validate that it's not empty
    if (board[pos.row][pos.col] == 32)
    {
        return ' ';
    }

    // Get the piece type
    PieceType pt = getPieceType(board[pos.row][pos.col]);

    // Get the piece letter
    switch (pt)
    {
    case PieceType::PAWN:
        return 'P';
    case PieceType::ROOK:
        return 'R';
    case PieceType::KNIGHT:
        return 'N';
    case PieceType::BISHOP:
        return 'B';
    case PieceType::QUEEN:
        return 'Q';
    case PieceType::KING:
        return 'K';
    default:
        throw invalid_argument("Invalid piece type");
    }
}

// Get the type of a piece from its location
Board::Color Board::getPieceColor(Position pos)
{
    // Validate the pos.row and column
    if (pos.row < 0 || pos.row > 7 || pos.col < 0 || pos.col > 7)
    {
        throw invalid_argument("Invalid pos.row or column");
    }

    // Get the color of the piece
    if (board[pos.row][pos.col] >= 32)
    {
        return Color::EMPTY;
    }
    else if (board[pos.row][pos.col] < 16)
    {
        return Color::WHITE;
    }
    else
    {
        return Color::BLACK;
    }
}

// Set the en passant position
void Board::setEnPassant(Position pos)
{
    // Validate the pos.row and column
    if ((pos.row != 1 && pos.row != 6) || pos.col < 0 || pos.col > 7)
    {
        throw invalid_argument("Invalid pos.row or column");
    }

    // Set the en passant position
    if (pos.row == 1)
    {
        canEnPassant[0][pos.col] = true;
    }
    else
    {
        canEnPassant[1][pos.col] = true;
    }
}

// Private exposure of the en passant check
bool Board::checkEnPassant(Position pos)
{
    // Validate the pos.row and column
    if (pos.col < 0 || pos.col > 7)
    {
        throw invalid_argument("Invalid column");
    }

    // Check if this is a valid en passant pos.row
    if (pos.row != 2 && pos.row != 5)
    {
        return false;
    }

    // Check if the en passant is valid
    if (pos.row == 2)
    {

        return canEnPassant[0][pos.col];
    }
    else
    {
        return canEnPassant[1][pos.col];
    }
}

void Board::promotePawn(Position pos, PieceType pieceType)
{
    // Validate the pos.row and column
    if (pos.row < 0 || pos.row > 7 || pos.col < 0 || pos.col > 7)
    {
        throw invalid_argument("Invalid pos.row or column");
    }

    // Get pawn id
    uint8_t piece = board[pos.row][pos.col];
    if (piece < 8 || piece > 15)
    {
        throw invalid_argument("Invalid piece ID");
    }

    // Promote the pawn
    pawnPromote[piece < 16][piece % 8] = pieceType;
}

// Remove a piece from the board
void Board::removePiece(Position pos)
{
    // Validate the pos.row and column
    if (pos.row < 0 || pos.row > 7 || pos.col < 0 || pos.col > 7)
    {
        throw invalid_argument("Invalid pos.row or column");
    }

    // Remove the piece
    board[pos.row][pos.col] = 32;
}



// add a piece to the board, should only be used in the constructor for blank boards
 void Board::addPiece(const pieceLocationInput& inputPiece)
 {

 }


std::vector<uint8_t> Board::reversePieceLookup(PieceType PieceInput ,Color PieceColor) // does the opposite of getPieceType, takes a piece kind and gives possible id's  
{
    std::vector <uint8_t> output;

    





} 


// Get the type of a piece from its ID
Board::PieceType Board::getPieceType(uint8_t pieceId)
{
    // Validate the piece ID
    if (pieceId > 31)
    {
        throw invalid_argument("Invalid piece ID");
    }

    switch (pieceId % 16)
    {
    case 0:
    case 7:
        return PieceType::ROOK;
    case 1:
    case 6:
        return PieceType::KNIGHT;
    case 2:
    case 5:
        return PieceType::BISHOP;
    case 3:
        return PieceType::QUEEN;
    case 4:
        return PieceType::KING;
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        // Check if we've promoted a pawn
        return pawnPromote[pieceId < 16][pieceId % 16 - 8];
    default:
        throw invalid_argument("Invalid piece ID");
    }
}

// Check if a proposed move is valid
bool Board::isValidMove(Position from, Position to)
{
    // Check if the move is within the board
    if (from.row < 0 || from.row > 7 || from.col < 0 || from.col > 7 || to.row < 0 || to.row > 7 || to.col < 0 || to.col > 7)
    {
        return false;
    }

    // Check if the piece actually exists
    if (board[from.row][from.col] == 32)
    {
        return false;
    }

    // Check if the piece is moving to the same position
    if (from.row == to.row && from.col == to.col)
    {
        return false;
    }

    // Check if the piece is moving to the same color
    Color fromColor = getPieceColor(from);
    Color toColor = getPieceColor(to);
    if (fromColor == toColor)
    {
        return false;
    }

    // Check if it's this pieces turn
    if (fromColor != turn)
    {
        return false;
    }

    // Piece-specific move validation
    uint8_t piece = board[from.row][from.col];
    PieceType pieceType = getPieceType(piece);

    Piece *pieceObj;
    switch (pieceType)
    {
    case PieceType::PAWN:
        pieceObj = new Pawn(fromColor);
        break;

    default:
        throw invalid_argument("Invalid piece type");
        break;
    }

    if (!pieceObj->isValidMove(this, from, to))
    {
        return false;
    }

    return true;
}

// Execute a move on the board
void Board::move(Position from, Position to)
{
    // Check if the move is valid
    if (!isValidMove(from, to))
    {
        throw invalid_argument("Invalid move");
    }

    // Move the piece
    uint8_t piece = board[from.row][from.col];
    board[from.row][from.col] = 32;

    // Tell the piece that we're moving
    PieceType pieceType = getPieceType(piece);
    Piece *pieceObj;
    pieceObj = new Pawn(getPieceColor(from));
    pieceObj->doMove(this, from, to);

    // Finish the move
    board[to.row][to.col] = piece;

    // Update the turn
    if (turn == Color::WHITE)
    {
        turn = Color::BLACK;
    }
    else
    {
        turn = Color::WHITE;
    }
}
