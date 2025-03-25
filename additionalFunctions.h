#ifndef ADDITIONALFUNCTIONS_H
#define ADDITIONALFUNCTIONS_H

#define NUMBER_OF_PIECES 32
#define NUMBER_OF_LETTERS 8
#define BOARD 9

#include "whitePieces.h"

int inputCheck(Pieces piece[NUMBER_OF_PIECES], Letters letter[NUMBER_OF_LETTERS], char playerInput[5], char seg_piece[3], char seg_letter[3], char seg_rank[2], char seg_capture);
int letterToNumber(char inp_slovo[1], Letters letter[NUMBER_OF_LETTERS]);
int lookingAt(Pieces piece[NUMBER_OF_PIECES], int pieceColor);
int assignmentOfPositions(int tmp_piece, int row, int column, Pieces piece[NUMBER_OF_PIECES], Letters letter[NUMBER_OF_LETTERS], int pieceColor);                 // color of piece: 1 - black, 2 - white
int assignmentOfPositionsCapture(int tmp_piece, int i, int row, int column, Pieces piece[NUMBER_OF_PIECES], Letters letter[NUMBER_OF_LETTERS], int pieceColor);   // color of piece: 1 - black, 2 - white

void boardPrint();
void startingPosition(Pieces piece[NUMBER_OF_PIECES], Letters letter[NUMBER_OF_LETTERS], int main); 

#endif