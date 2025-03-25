#ifndef WHITEPIECES_H
#define WHITEPIECES_H

#define NUMBER_OF_PIECES 32
#define NUMBER_OF_LETTERS 8
#define BOARD 9

#include "structures.h"

int whitePawnMove(Pieces piece[NUMBER_OF_PIECES], int row, int column, char pawn_piece[3], char pawn_capture, char last_move[5], int last_row_black, Letters letter[NUMBER_OF_LETTERS]);
int whiteRookMove(Pieces piece[NUMBER_OF_PIECES], int row, int column, char rook_piece[3], char rook_capture, Letters letter[NUMBER_OF_LETTERS]);
int whiteBishopMove(Pieces piece[NUMBER_OF_PIECES], int row, int column, char bishop_piece[3], char bishop_capture, Letters letter[NUMBER_OF_LETTERS]);
int whiteKingMove(Pieces piece[NUMBER_OF_PIECES], int row, int column, char king_capture, Letters letter[NUMBER_OF_LETTERS]);
int whiteKnightMove(Pieces piece[NUMBER_OF_PIECES], int row, int column, char knight_piece[3], char knight_capture, Letters letter[NUMBER_OF_LETTERS]);
int whiteQueenMove(Pieces piece[NUMBER_OF_PIECES], int row, int column, char queen_piece[3], char queen_capture, Letters letter[NUMBER_OF_LETTERS]);
int whiteCastleKingSide(Pieces piece[NUMBER_OF_PIECES], Letters letter[NUMBER_OF_LETTERS]);
int whiteCastleQueenSide(Pieces piece[NUMBER_OF_PIECES], Letters letter[NUMBER_OF_LETTERS]);

#endif