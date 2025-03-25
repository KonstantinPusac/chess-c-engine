#ifndef BLACKPIECES_H
#define BLACKPIECES_H

#define NUMBER_OF_PIECES 32
#define NUMBER_OF_LETTERS 8
#define BOARD 9

#include "whitePieces.h"
#include "structures.h"

int blackPawnMove(Pieces piece[NUMBER_OF_PIECES], int row, int column, char pawn_piece[3], char pawn_capture, char last_move[5], int last_row_white, Letters letter[NUMBER_OF_LETTERS]);
int blackRookMove(Pieces piece[NUMBER_OF_PIECES], int row, int column, char rook_piece[3], char rook_capture, Letters letter[NUMBER_OF_LETTERS]);
int blackBishopMove(Pieces piece[NUMBER_OF_PIECES], int row, int column, char bishop_piece[3], char bishop_capture, Letters letter[NUMBER_OF_LETTERS]);
int blackKingMove(Pieces piece[NUMBER_OF_PIECES], int row, int column, char king_capture, Letters letter[NUMBER_OF_LETTERS]);
int blackKnightMove(Pieces piece[NUMBER_OF_PIECES], int row, int column, char knight_piece[3], char knight_capture, Letters letter[NUMBER_OF_LETTERS]);
int blackQueenMove(Pieces piece[NUMBER_OF_PIECES], int row, int column, char queen_piece[3], char queen_capture, Letters letter[NUMBER_OF_LETTERS]);
int blackCastleKingSide(Pieces piece[NUMBER_OF_PIECES], Letters letter[NUMBER_OF_LETTERS]);
int blackCastleQueenSide(Pieces piece[NUMBER_OF_PIECES], Letters letter[NUMBER_OF_LETTERS]);

#endif