#ifndef STRUCTURES_H
#define STRUCTURES_H 

// Board
extern char *board[BOARD][BOARD];
extern int last_row_white;
extern int last_row_black;
extern int allow_castle_white[2];
extern int allow_castle_black[2];

// Structure for each piece
typedef struct {
    int row;                // x or i
    int column;             // y or j
    char *watching[8];      // what piece is watching 
    int count;              // counter for watching array
} Pozicija;

// Array of pieces
typedef struct {
    char *piece_name;
    Pozicija pos;
} Pieces;

// Array of letters
typedef struct 
{
    char *letter;
    int broj;
} Letters;

#endif