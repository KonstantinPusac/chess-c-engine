#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "whitePieces.h"

#define NUMBER_OF_PIECES 32
#define NUMBER_OF_LETTERS 8
#define BOARD 9

char rankNumbers[BOARD][NUMBER_OF_PIECES];

// Function that adds an element to a dynamic array, checking the capacity beforehand
void addElement(int **array, int *counter, int *capacity, int element) {
    if (*counter >= *capacity) {
        *capacity *= 2;  // Expanding capacity
        int *temp = realloc(*array, *capacity * sizeof(int));
        if (temp == NULL) {
            fprintf(stderr, "Error: reallocating memory\n");
            free(*array);
            exit(EXIT_FAILURE);
        }
        *array = temp;
    }
    (*array)[*counter] = element;
    (*counter)++;
}

int inputCheck(Pieces piece[NUMBER_OF_PIECES], Letters letter[NUMBER_OF_LETTERS], char playerInput[5], char seg_piece[3], char seg_letter[3], char seg_rank[2], char seg_capture)
{
    // Input elements: Piece
    int bool_piece = 0;
    int bool_letter = 0;
    for (int i = 0; i < NUMBER_OF_PIECES; i++)
    {
        if (strcmp(seg_piece, piece[i].piece_name) == 0)
        {
            bool_piece = 1;
            break;
        } 
    }
    if (!strcmp(playerInput, "O-O") || !strcmp(playerInput, "O-O-O"))
    {
        bool_piece = 1;
        bool_letter = 1;
    }
    
    if (!bool_piece)
    {
        printf("Error: Incorrectly enterow command (piece)(x optional)(letter)(number) (example input: P3xc4) \n");
        return 0;
    }
    
    // Input elements: Letter
    for (int i = 0; i < NUMBER_OF_LETTERS; i++)
    {
        if (strcmp(seg_letter, letter[i].letter) == 0)
        {
            bool_letter = 1;
            break;
        }
        
    }
    if (!bool_letter)
    {
        printf("Error: Incorrectly enterow command (piece)(x optional)(letter)(number) (example input: P3xc4) \n");
        return 0;
    }

    if(strcmp(playerInput, "O-O") && strcmp(playerInput, "O-O-O"))
    {
        // Input elements: Number
        if(atoi(seg_rank) < 1 || atoi(seg_rank) > 8)
        {
            printf("Error: Incorrectly enterow command (piece)(x optional)(letter)(number) (example input: P3xc4) \n");
            return 0;
        }

        // Input elements: Capture
        if (seg_capture != 'x' && strlen(playerInput) > 4)
        {
            printf("Error: Incorrectly enterow command (piece)(x optional)(letter)(number) (example input: P3xc4) \n");
            return 0;
        }
    }

    return 1;
}

// Convering letters into numbers
int letterToNumber(char inp_letter[1], Letters letter[NUMBER_OF_LETTERS])
{
    for (int i = 0; i < NUMBER_OF_LETTERS; i++)
    {
        if(strcmp(letter[i].letter, inp_letter) == 0)
        {
            return letter[i].broj;
        }
    }

    printf("Error: Function letterToNumber \n");
    return 0;
}

int auxiliaryLookingAtWhite(Pieces piece[NUMBER_OF_PIECES], int x_axis, int y_axis, int x_aux, int y_aux)
{
    int output = 0;
    for (int j = 0; j < NUMBER_OF_PIECES; j++)
    {
        if(piece[j].pos.row == x_axis+x_aux && piece[j].pos.column == y_axis+y_aux)
        {
            if (piece[j].piece_name[0] == 'k')
            {
                output = 1;
            }
        }
    }

    return output;
}

int auxiliaryLookingAtBlack(Pieces piece[NUMBER_OF_PIECES], int x_axis, int y_axis, int x_aux, int y_aux)
{
    int output = 0;
    for (int j = 0; j < NUMBER_OF_PIECES; j++)
    {
        if(piece[j].pos.row == x_axis+x_aux && piece[j].pos.column == y_axis+y_aux)
        {
            if (piece[j].piece_name[0] == 'K')
            {
                output = 2;
            }
        }
    }

    return output;
}

int lookingAt(Pieces piece[NUMBER_OF_PIECES], int pieceColor)
{
    int check = 0;
    int capacity = NUMBER_OF_PIECES;
    int *check_array = malloc(capacity * sizeof(int));
    if (check_array == NULL) 
    {
        fprintf(stderr, "Error: Memory allocation\n");
        exit(EXIT_FAILURE);
    }
    int counter = 0;
    // Emptying lookingAt array
    for (int i = 0; i < NUMBER_OF_PIECES; i++)
    {   
        for (int j = 0; j < 8; j++)
        {
            piece[i].pos.watching[j] = NULL;
        }
        piece[i].pos.count = 0;
    }
    
    for (int i = 0; i < NUMBER_OF_PIECES; i++)
    {
        if(!(piece[i].pos.row == 8 && piece[i].pos.column == 0))
        {
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // WHITE PAWN

            if(piece[i].piece_name[0] == 'P')
            {
                int x_axis = piece[i].pos.row;
                int y_axis = piece[i].pos.column;

                // Looking into left square for capture
                if(y_axis-1 > 0 && x_axis+1 < 8 && strcmp(board[x_axis+1][y_axis-1], "OO") && strcmp(board[x_axis+1][y_axis-1], "00"))
                {
                    addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, +1, -1));
                }
                // Looking into right square for capture
                else if (y_axis+1 < 9 && x_axis+1 < 8 && strcmp(board[x_axis+1][y_axis+1], "OO") && strcmp(board[x_axis+1][y_axis+1], "00"))
                {
                    addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, +1, +1));
                }
            }
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // BLACK PAWN

            if(piece[i].piece_name[0] == 'p')
            {
                int x_axis = piece[i].pos.row;
                int y_axis = piece[i].pos.column;

                // Looking into left square for capture
                if(y_axis-1 > 0 && x_axis-1 >= 0 &&  strcmp(board[x_axis-1][y_axis-1], "OO") && strcmp(board[x_axis-1][y_axis-1], "00"))
                {
                    // Prolalazenje figure u koju watching
                    addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, -1, -1));
                }
                // Looking into right square for capture
                else if (y_axis+1 < 9 && x_axis-1 >= 0 && strcmp(board[x_axis-1][y_axis+1], "OO") && strcmp(board[x_axis-1][y_axis+1], "00"))
                {
                    addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, -1, +1));
                }
            }
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // ROOK 

            if(piece[i].piece_name[0] == 'R' || piece[i].piece_name[0] == 'r')
            {
                int x_axis = piece[i].pos.row;
                int y_axis = piece[i].pos.column;

                // Moving on X axis up
                for (int shifter = 1; x_axis+shifter < 8; shifter++)
                {
                    if(strcmp(board[x_axis+shifter][y_axis], "00") && strcmp(board[x_axis+shifter][y_axis], "OO"))
                    {
                        if(piece[i].piece_name[0] == 'R')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, shifter, 0));
                        }
                        else if(piece[i].piece_name[0] == 'r')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, shifter, 0));
                        }
                        else
                            printf("Error: lookingAt function: Rook\n");

                        break;
                    }
                }

                // Moving on X axis down
                for (int shifter = 1; x_axis-shifter > 0-1; shifter++)
                {
                    if(strcmp(board[x_axis-shifter][y_axis], "00") && strcmp(board[x_axis-shifter][y_axis], "OO"))
                    {
                        if(piece[i].piece_name[0] == 'R')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, -shifter, 0));
                        }
                        else if(piece[i].piece_name[0] == 'r')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, -shifter, 0));
                        }
                        else
                            printf("Error: lookingAt function: Rook\n");

                        break;
                    }
                }

                // Moving on Y axis right
                for (int shifter = 1; y_axis+shifter < 9; shifter++)
                {
                    if(strcmp(board[x_axis][y_axis+shifter], "00") && strcmp(board[x_axis][y_axis+shifter], "OO"))
                    {
                        if(piece[i].piece_name[0] == 'R')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, 0, shifter));
                        }
                        else if(piece[i].piece_name[0] == 'r')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, 0, shifter));
                        }
                        else
                            printf("Error: lookingAt function: Rook\n");
                            
                        break;
                    }
                }

                // Moving on Y axis left
                for (int shifter = 1; y_axis-shifter > 0; shifter++)
                {
                    if(strcmp(board[x_axis][y_axis-shifter], "00") && strcmp(board[x_axis][y_axis-shifter], "OO"))
                    {
                        if(piece[i].piece_name[0] == 'R')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, 0, -shifter));
                        }
                        else if(piece[i].piece_name[0] == 'r')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, 0, -shifter));
                        }
                        else
                            printf("Error: lookingAt function: Rook\n");
                                
                        break;
                    }
                }
            }
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // BISHOP

            if(piece[i].piece_name[0] == 'B' || piece[i].piece_name[0] == 'b')
            {
                int x_axis = piece[i].pos.row;
                int y_axis = piece[i].pos.column;

                // Diagonal up-right
                for (int shifter = 1; x_axis+shifter < 8 && y_axis+shifter < 9; shifter++)
                {
                    if(strcmp(board[x_axis+shifter][y_axis+shifter], "00") && strcmp(board[x_axis+shifter][y_axis+shifter], "OO"))
                    {
                        if(piece[i].piece_name[0] == 'B')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, shifter, shifter));
                        }
                        else if(piece[i].piece_name[0] == 'b')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, shifter, shifter));
                        }
                        else
                            printf("Error: lookingAt function: Bishop\n");

                        break;
                    }
                }
                
                // Diagonal up-left
                for (int shifter = 1; x_axis+shifter < 8 && y_axis-shifter > 0; shifter++)
                {
                    if(strcmp(board[x_axis+shifter][y_axis-shifter], "00") && strcmp(board[x_axis+shifter][y_axis-shifter], "OO"))
                    {
                        if(piece[i].piece_name[0] == 'B')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, shifter, -shifter));
                        }
                        else if(piece[i].piece_name[0] == 'b')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, shifter, -shifter));
                        }
                        else
                            printf("Error: lookingAt function: Bishop\n");

                        break;
                    }
                }
                
                // Diagonal down-right
                for (int shifter = 1; x_axis-shifter > -1 && y_axis+shifter < 9; shifter++)
                {
                    if(strcmp(board[x_axis-shifter][y_axis+shifter], "00") && strcmp(board[x_axis-shifter][y_axis+shifter], "OO"))
                    {
                        if(piece[i].piece_name[0] == 'B')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, -shifter, shifter));
                        }
                        else if(piece[i].piece_name[0] == 'b')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, -shifter, shifter));
                        }
                        else
                            printf("Error: lookingAt function: Bishop\n");

                        break;
                    }
                }
                
                // Diagonal down-left
                for (int shifter = 1; x_axis-shifter > -1 && y_axis-shifter > 0; shifter++)
                {
                    if(strcmp(board[x_axis-shifter][y_axis-shifter], "00") && strcmp(board[x_axis-shifter][y_axis-shifter], "OO"))
                    {
                        if(piece[i].piece_name[0] == 'B')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, -shifter, -shifter));
                        }
                        else if(piece[i].piece_name[0] == 'b')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, -shifter, -shifter));
                        }
                        else
                            printf("Error: lookingAt function: Bishop\n");

                        break;
                    }
                }
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // KNIGHT

            if(piece[i].piece_name[0] == 'N' || piece[i].piece_name[0] == 'n')
            {
                int x_axis = piece[i].pos.row;
                int y_axis = piece[i].pos.column;
                
                // Up-left
                if(x_axis+2 < 8 && y_axis-1 > 0 && strcmp(board[x_axis+2][y_axis-1], "00") && strcmp(board[x_axis+2][y_axis-1], "OO"))
                {
                    if(piece[i].piece_name[0] == 'N')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, 2, -1));
                    }
                    else if(piece[i].piece_name[0] == 'n')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, 2, -1));
                    }
                    else
                        printf("Error: lookingAt function: Knight\n");
                }

                // Up-right
                if(x_axis+2 < 8 && y_axis+1 < 9 && strcmp(board[x_axis+2][y_axis+1], "00") && strcmp(board[x_axis+2][y_axis+1], "OO"))
                {
                    if(piece[i].piece_name[0] == 'N')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, 2, 1));
                    }
                    else if(piece[i].piece_name[0] == 'n')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, 2, 1));
                    }
                    else
                        printf("Error: lookingAt function: Knight\n");
                }

                // Down-left
                if(x_axis-2 > -1 && y_axis-1 > 0 && strcmp(board[x_axis-2][y_axis-1], "00") && strcmp(board[x_axis-2][y_axis-1], "OO"))
                {
                    if(piece[i].piece_name[0] == 'N')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, -2, -1));
                    }
                    else if(piece[i].piece_name[0] == 'n')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, -2, -1));
                    }
                    else
                        printf("Error: lookingAt function: Knight\n");
                }

                // Down-right
                if(x_axis-2 > -1 && y_axis+1 < 9 && strcmp(board[x_axis-2][y_axis+1], "00") && strcmp(board[x_axis-2][y_axis+1], "OO"))
                {
                    if(piece[i].piece_name[0] == 'N')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, -2, 1));
                    }
                    else if(piece[i].piece_name[0] == 'n')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, -2, 1));
                    }
                    else
                        printf("Error: lookingAt function: Knight\n");
                }
                
                // Left-up
                if(x_axis+1 < 8 && y_axis-2 > 0 && strcmp(board[x_axis+1][y_axis-2], "00") && strcmp(board[x_axis+1][y_axis-2], "OO"))
                {
                    if(piece[i].piece_name[0] == 'N')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, 1, -2));
                    }
                    else if(piece[i].piece_name[0] == 'n')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, 1, -2));
                    }
                    else
                        printf("Error: lookingAt function: Knight\n");
                }
                // Left-down
                if(x_axis-1 > -1 && y_axis-2 > 0 && strcmp(board[x_axis-1][y_axis-2], "00") && strcmp(board[x_axis-1][y_axis-2], "OO"))
                {
                    if(piece[i].piece_name[0] == 'N')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, -1, -2));
                    }
                    else if(piece[i].piece_name[0] == 'n')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, -1, -2));
                    }
                    else
                        printf("Error: lookingAt function: Knight\n");
                }
                // Right-up
                if(x_axis+1 < 8 && y_axis+2 < 9 && strcmp(board[x_axis+1][y_axis+2], "00") && strcmp(board[x_axis+1][y_axis+2], "OO"))
                {
                    if(piece[i].piece_name[0] == 'N')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, 1, 2));
                    }
                    else if(piece[i].piece_name[0] == 'n')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, 1, 2));
                    }
                    else
                        printf("Error: lookingAt function: Knight\n");
                }
                // Right-down
                if(x_axis-1 > -1 && y_axis+2 < 9 && strcmp(board[x_axis-1][y_axis+2], "00") && strcmp(board[x_axis-1][y_axis+2], "OO"))
                {
                    if(piece[i].piece_name[0] == 'N')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, -1, 2));
                    }
                    else if(piece[i].piece_name[0] == 'n')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, -1, 2));
                    }
                    else
                        printf("Error: lookingAt function: Knight\n");
                }
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // QUEEN

            if(piece[i].piece_name[0] == 'Q' || piece[i].piece_name[0] == 'q')
            {
                int x_axis = piece[i].pos.row;
                int y_axis = piece[i].pos.column;

                // Moving on X axis up
                for (int shifter = 1; x_axis+shifter < 8; shifter++)
                {
                    if(strcmp(board[x_axis+shifter][y_axis], "00") && strcmp(board[x_axis+shifter][y_axis], "OO"))
                    {
                        if(piece[i].piece_name[0] == 'Q')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, shifter, 0));
                        }
                        else if(piece[i].piece_name[0] == 'q')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, shifter, 0));
                        }
                        else
                            printf("Error: lookingAt function: Queen\n");

                        break;
                    }
                }

                // Moving on X axis down
                for (int shifter = 1; x_axis-shifter > 0-1; shifter++)
                {
                    if(strcmp(board[x_axis-shifter][y_axis], "00") && strcmp(board[x_axis-shifter][y_axis], "OO"))
                    {
                        if(piece[i].piece_name[0] == 'Q')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, -shifter, 0));
                        }
                        else if(piece[i].piece_name[0] == 'q')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, -shifter, 0));
                        }
                        else
                            printf("Error: lookingAt function: Queen\n");

                        break;
                    }
                }

                // Moving on Y axis right
                for (int shifter = 1; y_axis+shifter < 9; shifter++)
                {
                    if(strcmp(board[x_axis][y_axis+shifter], "00") && strcmp(board[x_axis][y_axis+shifter], "OO"))
                    {
                        if(piece[i].piece_name[0] == 'Q')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, 0, shifter));
                        }
                        else if(piece[i].piece_name[0] == 'q')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, 0, shifter));
                        }
                        else
                            printf("Error: lookingAt function: Queen\n");
                            
                        break;
                    }
                }

                // Moving on Y axis left
                for (int shifter = 1; y_axis+shifter > 0; shifter++)
                {
                    if(strcmp(board[x_axis][y_axis-shifter], "00") && strcmp(board[x_axis][y_axis-shifter], "OO"))
                    {
                        if(piece[i].piece_name[0] == 'Q')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, 0, -shifter));
                        }
                        else if(piece[i].piece_name[0] == 'q')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, 0, -shifter));
                        }
                        else
                            printf("Error: lookingAt function: Queen\n");
                                
                        break;
                    }
                }

                // Diagonal up-right
                for (int shifter = 1; x_axis+shifter < 8 && y_axis+shifter < 9; shifter++)
                {
                    if(strcmp(board[x_axis+shifter][y_axis+shifter], "00") && strcmp(board[x_axis+shifter][y_axis+shifter], "OO"))
                    {
                        if(piece[i].piece_name[0] == 'Q')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, shifter, shifter));
                        }
                        else if(piece[i].piece_name[0] == 'q')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, shifter, shifter));
                        }
                        else
                            printf("Error: lookingAt function: Queen\n");

                        break;
                    }
                }

                // Diagonal up-left
                for (int shifter = 1; x_axis+shifter < 8 && y_axis-shifter > 0; shifter++)
                {
                    if(strcmp(board[x_axis+shifter][y_axis-shifter], "00") && strcmp(board[x_axis+shifter][y_axis-shifter], "OO"))
                    {
                        if(piece[i].piece_name[0] == 'Q')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, shifter, -shifter));
                        }
                        else if(piece[i].piece_name[0] == 'q')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, shifter, -shifter));
                        }
                        else
                            printf("Error: lookingAt function: Queen\n");

                        break;
                    }
                }

                // Diagonal down-right
                for (int shifter = 1; x_axis-shifter > -1 && y_axis+shifter < 9; shifter++)
                {
                    if(strcmp(board[x_axis-shifter][y_axis+shifter], "00") && strcmp(board[x_axis-shifter][y_axis+shifter], "OO"))
                    {
                        if(piece[i].piece_name[0] == 'Q')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, -shifter, shifter));
                        }
                        else if(piece[i].piece_name[0] == 'q')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, -shifter, shifter));
                        }
                        else
                            printf("Error: lookingAt function: Queen\n");

                        break;
                    }
                }

                // Diagonal down-left
                for (int shifter = 1; x_axis-shifter > -1 && y_axis-shifter > 0; shifter++)
                {
                    if(strcmp(board[x_axis-shifter][y_axis-shifter], "00") && strcmp(board[x_axis-shifter][y_axis-shifter], "OO"))
                    {
                        if(piece[i].piece_name[0] == 'Q')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, -shifter, -shifter));
                        }
                        else if(piece[i].piece_name[0] == 'q')
                        {
                            addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, -shifter, -shifter));
                        }
                        else
                            printf("Error: lookingAt function: Queen\n");
                        break;
                    }
                }
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // KING

            if(piece[i].piece_name[0] == 'K' || piece[i].piece_name[0] == 'k')
            {
                int x_axis = piece[i].pos.row;
                int y_axis = piece[i].pos.column;

                // Up
                if(x_axis+1 < 8 && strcmp(board[x_axis+1][y_axis], "00") && strcmp(board[x_axis+1][y_axis], "OO"))
                {
                    if(piece[i].piece_name[0] == 'K')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, 1, 0));
                    }
                    else if(piece[i].piece_name[0] == 'k')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, 1, 0));
                    }
                    else
                        printf("Error: lookingAt function: King\n");
                }

                // Down
                if(x_axis-1 > -1 && strcmp(board[x_axis-1][y_axis], "00") && strcmp(board[x_axis-1][y_axis], "OO"))
                {
                    if(piece[i].piece_name[0] == 'K')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, -1, 0));
                    }
                    else if(piece[i].piece_name[0] == 'k')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, -1, 0));
                    }
                    else
                        printf("Error: lookingAt function: King\n");
                }

                // Left
                if(y_axis-1 > 0 && strcmp(board[x_axis][y_axis-1], "00") && strcmp(board[x_axis][y_axis-1], "OO"))
                {
                    if(piece[i].piece_name[0] == 'K')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, 0, -1));
                    }
                    else if(piece[i].piece_name[0] == 'k')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, 0, -1));
                    }
                    else
                        printf("Error: lookingAt function: King\n");
                }

                // Right
                if(y_axis+1 < 9 && strcmp(board[x_axis][y_axis+1], "00") && strcmp(board[x_axis][y_axis+1], "OO"))
                {
                    if(piece[i].piece_name[0] == 'K')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, 0, 1));
                    }
                    else if(piece[i].piece_name[0] == 'k')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, 0, 1));
                    }
                    else
                        printf("Error: lookingAt function: King\n");
                }

                // Up-left
                if(x_axis+1 < 8 && y_axis-1 > 0 && strcmp(board[x_axis+1][y_axis-1], "00") && strcmp(board[x_axis+1][y_axis-1], "OO"))
                {
                    if(piece[i].piece_name[0] == 'K')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, 1, -1));
                    }
                    else if(piece[i].piece_name[0] == 'k')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, 1, -1));
                    }
                    else
                        printf("Error: lookingAt function: King\n");
                }

                // Up-right
                if(x_axis+1 < 8 && y_axis+1 < 9 && strcmp(board[x_axis+1][y_axis+1], "00") && strcmp(board[x_axis+1][y_axis+1], "OO"))
                {
                    if(piece[i].piece_name[0] == 'K')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, 1, 1));
                    }
                    else if(piece[i].piece_name[0] == 'k')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, 1, 1));
                    }
                    else
                        printf("Error: lookingAt function: King\n");
                }

                // Down-left
                if(x_axis-1 > -1 && y_axis-1 > 0 && strcmp(board[x_axis-1][y_axis-1], "00") && strcmp(board[x_axis-1][y_axis-1], "OO"))
                {
                    if(piece[i].piece_name[0] == 'K')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, -1, -1));
                    }
                    else if(piece[i].piece_name[0] == 'k')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, -1, -1));
                    }
                    else
                        printf("Error: lookingAt function: King\n");
                }

                // Down-right
                if(x_axis-1 > -1 && y_axis+1 < 9 && strcmp(board[x_axis-1][y_axis+1], "00") && strcmp(board[x_axis-1][y_axis+1], "OO"))
                {
                    if(piece[i].piece_name[0] == 'K')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtWhite(piece, x_axis, y_axis, -1, 1));
                    }
                    else if(piece[i].piece_name[0] == 'k')
                    {
                        addElement(&check_array, &counter, &capacity, auxiliaryLookingAtBlack(piece, x_axis, y_axis, -1, 1));
                    }
                    else
                        printf("Error: lookingAt function: King\n");
                }
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        }
    }

    // Going trough array to see if there is check
    for (int i = 0; i < counter; i++)
    {
        if (check_array[i] == 1 && pieceColor == 1)
        {
            check = 1;
            printf("Check!\n");     // White checks black
            break;
        }
        else if (check_array[i] == 2 && pieceColor == 2)
        {
            check = 2;
            printf("Check!\n");     // Black checks white
            break;
        }
    }

    free(check_array);
    
    return check;
}

void boardPrint()
{
    for (int i = 0; i < BOARD; i++)
    {
        for (int j = 0; j < BOARD; j++)
        {
            printf("%s ", board[i][j]);

            if (j == BOARD-1)
                printf("\n");
        }
    } 
}

void startingPosition(Pieces piece[NUMBER_OF_PIECES], Letters letter[NUMBER_OF_LETTERS], int main)
{ 
    for (int i = 0; i < BOARD; i++) {
        sprintf(rankNumbers[i], "%d", i + 1);
    }

    // Filling up the Board matrix
    for (int i = 0; i < BOARD; i++)
    {
        for (int j = 0; j < BOARD; j++)
        {   
            int inputCheck = 1;                   // kada nije uneta piece nastavlja se
            // Letter input
            if (i == 8 && j > 0)
            {
                for (int k = 0; k < NUMBER_OF_LETTERS; k++)
                {
                    if(j == letter[k].broj)
                    {
                        board[i][j] = letter[k].letter;
                        inputCheck = 0;
                        break;
                    }
                }
            }

            // Piece input
            if(inputCheck)
            {
                for (int pom_f = 0; pom_f < NUMBER_OF_PIECES; pom_f++)
                {
                    if (i == piece[pom_f].pos.row && j == piece[pom_f].pos.column)
                    {
                        board[i][j] = piece[pom_f].piece_name;
                        inputCheck = 0;
                        break;
                    } 
                }
            }

            // Rank number input
            if(inputCheck)
            {
                if (j == 0)
                {
                    board[i][j] = rankNumbers[i];
                    inputCheck = 0;
                }
            }

            // Square color input
            if(inputCheck)
            {
                if((i + j) % 2 == 0)
                    board[i][j] = "00";
                
                else if ((i + j) % 2 != 0)
                    board[i][j] = "OO";
                else 
                    printf("Error: Printing squares \n");
            }
        }
    }
    
    board[8][0] = "X";

    // Board print
    if(main == 1)
        boardPrint();
}

int assignmentOfPositions(int tmp_piece, int row, int column, Pieces piece[NUMBER_OF_PIECES], Letters letter[NUMBER_OF_LETTERS], int pieceColor)
{
    int old_row = piece[tmp_piece].pos.row;
    int old_column = piece[tmp_piece].pos.column;

    // Position input
    piece[tmp_piece].pos.row = row;
    piece[tmp_piece].pos.column = column;

    startingPosition(piece, letter, 0);

    if (lookingAt(piece, pieceColor) == pieceColor)
    {
        // Previous postion input 
        piece[tmp_piece].pos.row = old_row;
        piece[tmp_piece].pos.column = old_column;

        printf("Error: Illegal move you are in check! \n");
        return 0;
    }

    return 1;
}

int assignmentOfPositionsCapture(int tmp_piece, int i, int row, int column, Pieces piece[NUMBER_OF_PIECES], Letters letter[NUMBER_OF_LETTERS], int pieceColor)
{
    int old_row_x = piece[i].pos.row;
    int old_column_x = piece[i].pos.column;

    int old_row = piece[tmp_piece].pos.row;
    int old_column = piece[tmp_piece].pos.column;

    // Capturing piece
    piece[i].pos.row = 8;
    piece[i].pos.column = 0;

    // Position input
    piece[tmp_piece].pos.row = row;
    piece[tmp_piece].pos.column = column;

    startingPosition(piece, letter, 0);

    if (lookingAt(piece, pieceColor) == pieceColor)
    {
        // Previous postion input 
        piece[i].pos.row = old_row_x;
        piece[i].pos.column = old_column_x;
        
        piece[tmp_piece].pos.row = old_row;
        piece[tmp_piece].pos.column = old_column;

        printf("Error: Illegal move you are in check! \n");
        return 0;
    }

    return 1;
}