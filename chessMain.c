#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "whitePieces.h"
#include "blackPieces.h"
#include "additionalFunctions.h"
#include "structures.h"

#define NUMBER_OF_PIECES 32
#define NUMBER_OF_LETTERS 8
#define BOARD 9

char last_move[10];
int moveInput(Pieces piece[NUMBER_OF_PIECES], Letters letter[NUMBER_OF_LETTERS], char input[10], int pieceColor)
{
    int return_value = 0;
    char playerInput[100];
    strcpy(playerInput, input);

    // Provera duzine stringa
    if (strlen(playerInput) > 5 || strlen(playerInput) < 3)
    {
        printf("Error: Incorrectly entered command (piece)(x optional)(letter)(number) (example input: P3xc4) \n");
    }
    else
    {
        char seg_piece[3]; seg_piece[2] = '\0';                             // piece sign
        char seg_letter[3]; seg_letter[1] = ' '; seg_letter[2] = '\0';      // x axis sign
        char seg_rank[2]; seg_rank[1] = '\0';                               // y axis sign
        char seg_capture[2]; seg_capture[1] = '\0';                         // capturing sign

        for (int i = 0; i < 2; i++)
        {
            seg_piece[i] = playerInput[i];
        }

        if (playerInput[2] == 'x')
        {
            seg_capture[0] = playerInput[2];
            seg_letter[0] = playerInput[3];
            seg_rank[0] = playerInput[4];
        }
        else
        {
            seg_capture[0] = 'i';
            seg_letter[0] = playerInput[2];
            seg_rank[0] = playerInput[3];
        }

        if(!inputCheck(piece, letter, playerInput, seg_piece, seg_letter, seg_rank, seg_capture[0]))
        {
            printf("Error: Input\n");
            return_value = 0;
        }
        else
        {
            // Position on the board
            if (pieceColor == 1)
            {
                if (seg_piece[0] == 'P')
                {
                    return_value = whitePawnMove(piece, atoi(seg_rank)-1, letterToNumber(seg_letter, letter), seg_piece, seg_capture[0], last_move, last_row_black, letter);
                }
                else if (seg_piece[0] == 'R')
                {
                    return_value = whiteRookMove(piece, atoi(seg_rank)-1, letterToNumber(seg_letter, letter), seg_piece, seg_capture[0], letter);
                }
                else if (seg_piece[0] == 'B')
                {
                    return_value = whiteBishopMove(piece, atoi(seg_rank)-1, letterToNumber(seg_letter, letter), seg_piece, seg_capture[0], letter);
                }
                else if (seg_piece[0] == 'K')
                {
                    return_value = whiteKingMove(piece, atoi(seg_rank)-1, letterToNumber(seg_letter, letter), seg_capture[0], letter);
                }
                else if (seg_piece[0] == 'N')
                {
                    return_value = whiteKnightMove(piece, atoi(seg_rank)-1, letterToNumber(seg_letter, letter), seg_piece, seg_capture[0], letter);
                }
                else if (seg_piece[0] == 'Q')
                {
                    return_value = whiteQueenMove(piece, atoi(seg_rank)-1, letterToNumber(seg_letter, letter), seg_piece, seg_capture[0], letter);
                }
                else if (!strcmp(playerInput, "O-O"))
                {
                    return_value = whiteCastleKingSide(piece, letter);
                }
                else if (!strcmp(playerInput, "O-O-O"))
                {
                    return_value = whiteCastleQueenSide(piece, letter);
                }
                else
                {
                    printf("Error: Entered wrong piece color\n");
                    return 0;
                }
            }
            else if (pieceColor == 2)
            {
                if (seg_piece[0] == 'p')
                {
                    return_value = blackPawnMove(piece, atoi(seg_rank)-1, letterToNumber(seg_letter, letter), seg_piece, seg_capture[0], last_move, last_row_white, letter);
                }
                else if (seg_piece[0] == 'r')
                {
                    return_value = blackRookMove(piece, atoi(seg_rank)-1, letterToNumber(seg_letter, letter), seg_piece, seg_capture[0], letter);
                }
                else if (seg_piece[0] == 'b')
                {
                    return_value = blackBishopMove(piece, atoi(seg_rank)-1, letterToNumber(seg_letter, letter), seg_piece, seg_capture[0], letter);
                }
                else if (seg_piece[0] == 'k')
                {
                    return_value = blackKingMove(piece, atoi(seg_rank)-1, letterToNumber(seg_letter, letter), seg_capture[0], letter);
                }
                else if (seg_piece[0] == 'n')
                {
                    return_value = blackKnightMove(piece, atoi(seg_rank)-1, letterToNumber(seg_letter, letter), seg_piece, seg_capture[0], letter);
                }
                else if (seg_piece[0] == 'q')
                {
                    return_value = blackQueenMove(piece, atoi(seg_rank)-1, letterToNumber(seg_letter, letter), seg_piece, seg_capture[0], letter);
                }
                else if (!strcmp(playerInput, "O-O"))
                {
                    return_value = blackCastleKingSide(piece, letter);
                }
                else if (!strcmp(playerInput, "O-O-O"))
                {
                    return_value = blackCastleQueenSide(piece, letter);
                }
                else
                {
                    printf("Error: Entered wrong piece color\n");
                    return 0;
                }
            }
            else
            {
                printf("Error: Color selection\n");
                return 0;
            }
        }

        // Last move input
        strcpy(last_move, playerInput);
    }

    return return_value;
}

int main(void) 
{
    // Piece structure is {"name", {x axis, y axis, can a king capture, array of what is piece looking at, countr of the array}}
    Pieces piece[NUMBER_OF_PIECES] = {  
        {"R1", {0,1,{NULL},0}}, {"N1", {0,2,{NULL},0}}, {"B1", {0,3,{NULL},0}}, {"QQ", {0,5,{NULL},0}}, {"KK", {0,4,{NULL},0}}, {"B2", {0,6,{NULL},0}}, {"N2", {0,7,{NULL},0}}, {"R2", {0,8,{NULL},0}}, 
        {"P1", {1,1,{NULL},0}}, {"P2", {1,2,{NULL},0}}, {"P3", {1,3,{NULL},0}}, {"P4", {1,4,{NULL},0}}, {"P5", {1,5,{NULL},0}}, {"P6", {1,6,{NULL},0}}, {"P7", {1,7,{NULL},0}}, {"P8", {1,8,{NULL},0}},

        {"p1", {6,1,{NULL},0}}, {"p2", {6,2,{NULL},0}}, {"p3", {6,3,{NULL},0}}, {"p4", {6,4,{NULL},0}}, {"p5", {6,5,{NULL},0}}, {"p6", {6,6,{NULL},0}}, {"p7", {6,7,{NULL},0}}, {"p8", {6,8,{NULL},0}},
        {"r1", {7,1,{NULL},0}}, {"n1", {7,2,{NULL},0}}, {"b1", {7,3,{NULL},0}}, {"qq", {7,5,{NULL},0}}, {"kk", {7,4,{NULL},0}}, {"b2", {7,6,{NULL},0}}, {"n2", {7,7,{NULL},0}}, {"r2", {7,8,{NULL},0}} 
                                 };

    // Dynamic allocation 
    for (int i = 0; i < NUMBER_OF_PIECES; i++) 
    {
        char *temp = strdup(piece[i].piece_name);
        if (temp == NULL) {
            fprintf(stderr, "Error: Memory allocation failed at piece %d\n", i);
            exit(EXIT_FAILURE);
        }
        piece[i].piece_name = temp;
        if (piece[i].piece_name == NULL) 
        {
            fprintf(stderr, "Error: Memory allocation\n");
            exit(EXIT_FAILURE);
        }
    
    }

    Letters letter[NUMBER_OF_LETTERS] = { {"a ", 8}, {"b ", 7}, {"c ", 6}, {"d ", 5}, {"e ", 4}, {"f ", 3}, {"g ", 2}, {"h ", 1} };
    
    char input[10];
    startingPosition(piece, letter, 1);
    for (int i = 10; ; i++)
    {
        if(i % 2 == 0)
        {
            
            printf("White piece player plays: ");
            scanf("%s", input);
            printf("\n");

            if (strcmp(input, "end") == 0)
                break;
            
            printf("\n");

            if(moveInput(piece, letter, input, 1))
            {
                startingPosition(piece, letter, 1);
            }
            else
            {
                startingPosition(piece, letter, 1);
                i = 9;
            }

            printf("If you want to end the game, type \"end\" \n");
        }
        else if(i % 2 != 0)
        {
            printf("Black piece player plays: ");
            scanf("%s", input);
            printf("\n");

            if (strcmp(input, "end") == 0)
                break;

            printf("\n");

            if(moveInput(piece, letter, input, 2))
            {
                startingPosition(piece, letter, 1);
            }
            else
            {
                startingPosition(piece, letter, 1);
                i = 10;
            }

            printf("If you want to end the game, type \"end\" \n");
        }
        else
        {
            printf("Error: Input\n");
        }
    }

    // Freeing dynmaic allocated memory for pieces names
    for (int i = 0; i < NUMBER_OF_PIECES; i++) 
    {
        if (piece[i].piece_name != NULL) 
        {
            free(piece[i].piece_name);
            piece[i].piece_name = NULL;
        }
    }

    return 0;
}
