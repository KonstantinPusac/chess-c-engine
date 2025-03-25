#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "whitePieces.h"
#include "structures.h"
#include "additionalFunctions.h"

// Structure that represents a position in a matrix
typedef struct {
    int x_diagonals;
    int y_diagonals;
} Axes;

// Creating an array of allowed positions
typedef struct {
    Axes position;
} Diagonals;

int last_row_black = 0;
int allow_castle_black[2] = {1,1};    // First element is castel king side, second element is castle queen side

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pawn

int blackPawnMove(Pieces piece[NUMBER_OF_PIECES], int row, int column, char pawn_piece[3], char pawn_capture, char last_move[5], int last_row_white, Letters letter[NUMBER_OF_LETTERS])
{
    // Finding a pawn in the array
    int tmp_piece = 0;
    for (int i = 1; i < 9; i++)
    {   
        char piece_index[2]; 
        piece_index[0] = pawn_piece[1]; piece_index[1] = '\0';
        if(atoi(piece_index) == i)
        {
            tmp_piece = i + 15;
            break;
        }
    }
    
    // Finding out last row of black pawn before current move
    last_row_black = piece[tmp_piece].pos.row;

    // Checking if the move is capture or not
    if(pawn_capture == 'i')
    {
        // Checking if the row and column are legal moves
        if (column != piece[tmp_piece].pos.column || row >= piece[tmp_piece].pos.row)
        {
            printf("Error: Illegal move: Row or column: Pawn\n");
            return 0;
        }  
        // Checking if the pawn is in the correct position for two steps up
        if(piece[tmp_piece].pos.row == 6)
        {
            if (row > piece[tmp_piece].pos.row - 3)
            {
                // Checking if there is a piece in the way
                for (int i = piece[tmp_piece].pos.row - 1; i > row - 1; i--)
                {
                    if (strcmp(board[i][column], "00") && strcmp(board[i][column], "OO"))
                    {
                        printf("Error: Illegal move: Piece in the way: Pawn\n");
                        return 0;
                    } 
                }

                // Position input
                if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
                    return 0;

                return 1;
            }
            else
            {
                printf("Error: Illegal move: Pawn \n");
                return 0;
            }
        }
        else
        {
            if (row > piece[tmp_piece].pos.row - 2)
            {
                // Checking if there is a piece in the way
                int future_row = piece[tmp_piece].pos.row - 1;       // future row
                if (strcmp(board[future_row][column], "00") && strcmp(board[future_row][column], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Pawn\n");
                    return 0;
                }

                // Position input
                if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
                    return 0;

                // Promoting pawn
                char promotion[3]; promotion[2] = '\0';
                char tmp_piece_char;
                if(piece[tmp_piece].pos.row == 0)
                {
                    printf("Pick: q, r, b, n \n");
                    while ((getchar()) != '\n');
                    scanf("%c", &tmp_piece_char);
                    promotion[0] = tmp_piece_char;

                    if(!(promotion[0] == 'q') && !(promotion[0] == 'r') && !(promotion[0] == 'b') && !(promotion[0] == 'n'))
                    {
                        return 0;
                    }
                    printf("\n");

                    // Assigning a number to promoted piece
                    int aux_number = 0;
                    if (pawn_piece[1] == '1')
                    {
                        aux_number = 0;
                    }
                    else 
                    {
                        aux_number = pawn_piece[1] - '0';
                        aux_number++;
                    }
                    
                    promotion[1] = '0' + aux_number;
                    
                    // Checking and freeing old memory if it was dynamically allocated
                    if (piece[tmp_piece].piece_name != NULL) 
                    {
                        free(piece[tmp_piece].piece_name);
                        piece[tmp_piece].piece_name = NULL;
                    }

                    // Memory allocation
                    piece[tmp_piece].piece_name = malloc(3 * sizeof(char));  // 2 letters + '\0'
                    if (piece[tmp_piece].piece_name == NULL) 
                    {
                        printf("Error: Memory allocation\n");
                        return 0;
                    }
                    strcpy(piece[tmp_piece].piece_name, promotion);
                }

                return 1;
            }
            else
            {
                printf("Error: Illegal move: Pawn \n");
                return 0;
            }
        }
    }
    else if (pawn_capture == 'x')
    {
        // Checking if capturing
        if ((piece[tmp_piece].pos.row == row + 1 && piece[tmp_piece].pos.column == column + 1) || (piece[tmp_piece].pos.row == row + 1 && piece[tmp_piece].pos.column == column - 1))
        {
            // Checking if there is a piece on that position
            if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
            {
                for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                {
                    if (strcmp(board[row][column], piece[i].piece_name) == 0)
                    {
                        // Position input
                        if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                        return 0;

                        // Pawn promotion
                        char promotion[3]; promotion[2] = '\0';
                        char tmp_piece_char;
                        if(piece[tmp_piece].pos.row == 0)
                        {
                            printf("Pick: Q, R, B, N \n");
                            while ((getchar()) != '\n');
                            scanf("%c", &tmp_piece_char);
                            promotion[0] = tmp_piece_char;

                            if(!(promotion[0] == 'Q') && !(promotion[0] == 'R') && !(promotion[0] == 'B') && !(promotion[0] == 'N'))
                            {
                                return 0;
                            }
                            printf("\n");

                            // Assigning a number to promoted piece
                            int aux_number = 0;
                            if (pawn_piece[1] == '1')
                            {
                                aux_number = 0;
                            }
                            else 
                            {
                                aux_number = pawn_piece[1] - '0';
                                aux_number++;
                            }
                            
                            promotion[1] = '0' + aux_number;

                            // Checking and freeing old memory if it was dynamically allocated
                            if (piece[tmp_piece].piece_name != NULL) 
                            {
                                free(piece[tmp_piece].piece_name);
                                piece[tmp_piece].piece_name = NULL;
                            }

                            // Memory allocation
                            piece[tmp_piece].piece_name = malloc(3 * sizeof(char));  // 2 letter + '\0'
                            if (piece[tmp_piece].piece_name == NULL) 
                            {
                                printf("Error: Memory allocation\n");
                                return 0;
                            }
                            strcpy(piece[tmp_piece].piece_name, promotion);
                        }

                        return 1;
                    }
                }
            }
            //En passant
            else if (board[row+1][column][0] == 'P' && piece[tmp_piece].pos.row == row + 1 && piece[tmp_piece].pos.column == column + 1) // u Left
            {
                // Checking if the pawn did the two move
                if (last_row_white == 1 && last_move[0] == 'P')
                {
                    for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                    {
                        if (piece[i].pos.row == row+1 && piece[i].pos.column == column)
                        {
                            // Position input
                            if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                                return 0;

                            return 1;
                        }
                    }
                }
                else
                {
                    printf("Error: En passant: Pawn\n");
                    return 0;
                }
            } 
            else if (board[row+1][column][0] == 'P' && piece[tmp_piece].pos.row == row + 1 && piece[tmp_piece].pos.column == column - 1) // u Right
            {
                // Checking if the pawn did the two move
                if (last_row_white == 1 && last_move[0] == 'P')
                {
                    for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                    {
                        if (piece[i].pos.row == row-1 && piece[i].pos.column == column)
                        {
                            // Position input
                            if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                                return 0;

                            return 1;
                        }
                    }
                }
                else
                {
                    printf("Error: En passant: Pawn\n");
                    return 0;
                }
            }  
            else
            {
                printf("Error: No piece to capture: Pawn\n");
                return 0;
            }
        }
        else
        {
            printf("Error: Capture: Pawn\n");
            return 0;
        }
    }
    else
    {
        printf("Error: Capture variable: Pawn\n");
        return 0;
    }

    return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int blackRookMove(Pieces piece[NUMBER_OF_PIECES], int row, int column, char rook_piece[3], char rook_capture, Letters letter[NUMBER_OF_LETTERS])
{
    // Finding piece in array
    int tmp_piece = 0;  
    for (int i = 0; i < NUMBER_OF_PIECES; i++)
    {
        if (!strcmp(piece[i].piece_name, rook_piece))
        {
            tmp_piece = i;
        }
    }

    int x_axis = piece[tmp_piece].pos.row;
    int y_axis = piece[tmp_piece].pos.column;

    // Checking if the row and column are legal
    if (!(column == y_axis || row == x_axis))
    {
        printf("Error: Illegal move: Row or column: Rook\n");
        return 0;
    }
    
    // Checking if its capturing or moving
    if(rook_capture == 'i')
    {
        // Up
        if (x_axis < row)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; x_axis+shifter <= row; shifter++)
            {
                if(strcmp(board[x_axis+shifter][y_axis], "00") && strcmp(board[x_axis+shifter][y_axis], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Pawn\n");
                    return 0;
                }
            }
            
            // Position input
            if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
                return 0;

            if (tmp_piece == 24)
                allow_castle_black[0] = 1;
            else 
                allow_castle_black[1] = 1;

            return 1;
        }
        // Down
        else if (x_axis > row)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; x_axis-shifter >= row; shifter++)
            {
                if(strcmp(board[x_axis-shifter][y_axis], "00") && strcmp(board[x_axis-shifter][y_axis], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Rook\n");
                    return 0;
                }
            }
            
            // Position input
            if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
                return 0;

            if (tmp_piece == 24)
                allow_castle_black[0] = 1;
            else 
                allow_castle_black[1] = 1;

            return 1;
        }
        // Left
        else if (y_axis > column)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; y_axis-shifter >= column; shifter++)
            {
                if(strcmp(board[x_axis][y_axis-shifter], "00") && strcmp(board[x_axis][y_axis-shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Rook\n");
                    return 0;
                }
            }

            // Position input
            if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
                return 0;

            if (tmp_piece == 24)
                allow_castle_black[0] = 1;
            else 
                allow_castle_black[1] = 1;

            return 1;
        }
        // Right
        else if (y_axis < column)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; y_axis+shifter <= column; shifter++)
            {
                if(strcmp(board[x_axis][y_axis+shifter], "00") && strcmp(board[x_axis][y_axis+shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Rook\n");
                    return 0;
                }
            }

            // Position input
            if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
                return 0;

            if (tmp_piece == 24)
                allow_castle_black[0] = 1;
            else 
                allow_castle_black[1] = 1;

            return 1;
        }
        else
        {
            printf("Error: Illegal direction: Rook\n");
            return 0;
        }
    }
    else if (rook_capture == 'x')
    {
        // Up
        if (x_axis < row)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; x_axis+shifter < row; shifter++)
            {
                if(strcmp(board[x_axis+shifter][y_axis], "00") && strcmp(board[x_axis+shifter][y_axis], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Rook\n");
                    return 0;
                }
            }

            // Checking if there is a piece on the square
            if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
            {
                for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                {
                    if (strcmp(board[row][column], piece[i].piece_name) == 0)
                    {
                        // Position input
                        if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                            return 0;

                        if (tmp_piece == 24)
                            allow_castle_black[0] = 1;
                        else 
                            allow_castle_black[1] = 1;

                        return 1;
                    }
                }
            }
            else
            {
                printf("Error: No piece to capture: Rook\n");
                return 0;
            }
        }
        // Down
        else if (x_axis > row)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; x_axis-shifter > row; shifter++)
            {
                if(strcmp(board[x_axis-shifter][y_axis], "00") && strcmp(board[x_axis-shifter][y_axis], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Rook\n");
                    return 0;
                }
            }

            // Checking if there is a piece on the square
            if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
            {
                for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                {
                    if (strcmp(board[row][column], piece[i].piece_name) == 0)
                    {
                        // Position input
                        if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                            return 0;

                        if (tmp_piece == 24)
                            allow_castle_black[0] = 1;
                        else 
                            allow_castle_black[1] = 1;

                        return 1;
                    }
                }
            }
            else
            {
                printf("Error: No piece to capture: Rook\n");
                return 0;
            }
        }
        // Left
        else if (y_axis < column)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; y_axis-shifter > column; shifter++)
            {
                if(strcmp(board[x_axis][y_axis-shifter], "00") && strcmp(board[x_axis][y_axis-shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Rook\n");
                    return 0;
                }
            }

            // Checking if there is a piece on the square
            if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
            {
                for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                {
                    if (strcmp(board[row][column], piece[i].piece_name) == 0)
                    {
                        // Position input
                        if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                            return 0;

                        if (tmp_piece == 24)
                            allow_castle_black[0] = 1;
                        else 
                            allow_castle_black[1] = 1;

                        return 1;
                    }
                }
            }
            else
            {
                printf("Error: No piece to capture: Rook\n");
                return 0;
            }
        }
        // Right
        else if (y_axis > column)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; y_axis+shifter < column; shifter++)
            {
                if(strcmp(board[x_axis][y_axis+shifter], "00") && strcmp(board[x_axis][y_axis+shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Rook\n");
                    return 0;
                }
            }

            // Checking if there is a piece on the square
            if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
            {
                for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                {
                    if (strcmp(board[row][column], piece[i].piece_name) == 0)
                    {
                        // Position input
                        if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                            return 0;

                        if (tmp_piece == 24)
                            allow_castle_black[0] = 1;
                        else 
                            allow_castle_black[1] = 1;

                        return 1;
                    }
                }
            }
            else
            {
                printf("Error: No piece to capture: Rook\n");
                return 0;
            }
        }
        else
        {
            printf("Error: Illegal direction: Rook\n");
            return 0;
        }
    }
    else
    {
        printf("Error: Capture: Rook\n");
        return 0;
    }
    
    return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int blackBishopMove(Pieces piece[NUMBER_OF_PIECES], int row, int column, char bishop_piece[3], char bishop_capture, Letters letter[NUMBER_OF_LETTERS])
{
    int tmp_piece = 0;
    for (int i = 0; i < NUMBER_OF_PIECES; i++)
    {
        if (!strcmp(piece[i].piece_name, bishop_piece))
        {
            tmp_piece = i;
        }
    }

    int x_axis = piece[tmp_piece].pos.row;
    int y_axis = piece[tmp_piece].pos.column;

    Diagonals diagonal[7];
    for (int i = 0; i < 7; i++)
    {
        diagonal[i].position.x_diagonals = 0;
        diagonal[i].position.y_diagonals = 0;
    }

    // Array of permited moves on main diagonal
    int counter = 0;
    for (int i = 0; y_axis + i + 1 < 9 && x_axis + i + 1 < 8; i++)
    {
        diagonal[i].position.x_diagonals = x_axis + i + 1;
        diagonal[i].position.y_diagonals = y_axis + i + 1;
        counter = i;
    }
    for (int i = 0; y_axis - (i + 1) > 0 && x_axis - (i + 1) > -1; i++)
    {
        diagonal[counter].position.x_diagonals = x_axis - (i + 1);
        diagonal[counter].position.y_diagonals = y_axis - (i + 1);
        counter++;
    }
    
    // Checking if the row and colum are correct
    int diagonal_check = 1;
    for (int i = 0; i < 7; i++)
    {
        if (row == diagonal[i].position.x_diagonals && column == diagonal[i].position.y_diagonals)
            diagonal_check = 0;
        else if (row+column == x_axis+y_axis)
            diagonal_check = 0;
    }
    
    if(diagonal_check)
    {
        printf("Error: Illegal move: Row or column: Bishop\n");
        return 0;
    }
    
    if (bishop_capture == 'i')
    {
        // Up Left
        if (x_axis < row && y_axis > column)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; x_axis+shifter <= row && y_axis-shifter >= column; shifter++)
            {
                if(strcmp(board[x_axis+shifter][y_axis-shifter], "00") && strcmp(board[x_axis+shifter][y_axis-shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Bishop\n");
                    return 0;
                }
            }

            // Position input
            if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
                return 0;

            return 1;
        }
        // Up Right
        else if (x_axis < row && y_axis < column)
        {
            for (int shifter = 1; x_axis+shifter <= row && y_axis+shifter <= column; shifter++)
            {
                if(strcmp(board[x_axis+shifter][y_axis+shifter], "00") && strcmp(board[x_axis+shifter][y_axis+shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Bishop\n");
                    return 0;
                }
            }

            // Position input
            if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
                return 0;

            return 1;
        }
        // Down Left
        else if (x_axis > row && y_axis > column)
        {
            for (int shifter = 1; x_axis-shifter >= row && y_axis-shifter >= column; shifter++)
            {
                if(strcmp(board[x_axis-shifter][y_axis-shifter], "00") && strcmp(board[x_axis-shifter][y_axis-shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Bishop\n");
                    return 0;
                }
            }

            // Position input
            if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
                return 0;

            return 1;
        }
        // Down Right
        else if (x_axis > row && y_axis < column)
        {
            for (int shifter = 1; x_axis-shifter >= row && y_axis+shifter <= column; shifter++)
            {
                if(strcmp(board[x_axis-shifter][y_axis+shifter], "00") && strcmp(board[x_axis-shifter][y_axis+shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Bishop\n");
                    return 0;
                }
            }

            // Position input
            if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
                return 0;

            return 1;
        }
        else
        {
            printf("Error: Illegal direction: Bishop\n");
            return 0;
        }
    }
    else if (bishop_capture == 'x')
    {
        // Up Left
        if (x_axis < row && y_axis > column)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; x_axis+shifter < row && y_axis-shifter > column; shifter++)
            {
                if(strcmp(board[x_axis+shifter][y_axis-shifter], "00") && strcmp(board[x_axis+shifter][y_axis-shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Bishop\n");
                    return 0;
                }
            }
            
            // Checking if there is a piece on the square
            if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
            {
                for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                {
                    if (strcmp(board[row][column], piece[i].piece_name) == 0)
                    {
                        // Position input
                        if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                            return 0;

                        return 1;
                    }
                }
            }
            else
            {
                printf("Error: No piece to capture: Bishop\n");
                return 0;
            }
        }
        // Up Right
        else if (x_axis < row && y_axis < column)
        {
            for (int shifter = 1; x_axis+shifter < row && y_axis+shifter < column; shifter++)
            {
                if(strcmp(board[x_axis+shifter][y_axis+shifter], "00") && strcmp(board[x_axis+shifter][y_axis+shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Bishop\n");
                    return 0;
                }
            }
            
            // Checking if there is a piece on the square
            if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
            {
                for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                {
                    if (strcmp(board[row][column], piece[i].piece_name) == 0)
                    {
                        // Position input
                        if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                            return 0;

                        return 1;
                    }
                }
            }
            else
            {
                printf("Error: No piece to capture: Bishop\n");
                return 0;
            }
        }
        // Down Left
        else if (x_axis > row && y_axis > column)
        {
            for (int shifter = 1; x_axis-shifter > row && y_axis-shifter > column; shifter++)
            {
                if(strcmp(board[x_axis-shifter][y_axis-shifter], "00") && strcmp(board[x_axis-shifter][y_axis-shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Bishop\n");
                    return 0;
                }
            }
            
            // Checking if there is a piece on the square
            if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
            {
                for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                {
                    if (strcmp(board[row][column], piece[i].piece_name) == 0)
                    {
                        // Position input
                        if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                            return 0;

                        return 1;
                    }
                }
            }
            else
            {
                printf("Error: No piece to capture: Bishop\n");
                return 0;
            }
        }
        // Down Right
        else if (x_axis > row && y_axis < column)
        {
            for (int shifter = 1; x_axis-shifter > row && y_axis+shifter < column; shifter++)
            {
                if(strcmp(board[x_axis-shifter][y_axis+shifter], "00") && strcmp(board[x_axis-shifter][y_axis+shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Bishop\n");
                    return 0;
                }
            }
            
            // Checking if there is a piece on the square
            if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
            {
                for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                {
                    if (strcmp(board[row][column], piece[i].piece_name) == 0)
                    {
                        // Position input
                        if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                            return 0;

                        return 1;
                    }
                }
            }
            else
            {
                printf("Error: No piece to capture: Bishop\n");
                return 0;
            }
        }
        else
        {
            printf("Error: Illegal direction: Bishop\n");
            return 0;
        }
    }
    else
    {
        printf("Error: Capture: Bishop\n");
        return 0;
    }
    
    return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int blackKingMove(Pieces piece[NUMBER_OF_PIECES], int row, int column, char king_capture, Letters letter[NUMBER_OF_LETTERS])
{
    int tmp_piece = 28;
    int x_axis = piece[tmp_piece].pos.row;
    int y_axis = piece[tmp_piece].pos.column;

    // Provera opsega
    if(row > 7 || row < 0 || column > 8 || column < 1)
    {
        printf("Error: Out of bounds: King\n");
        return 0;
    }
    
    // Checking if the row and colum are correct
    if (abs(x_axis-row) > 1 || abs(y_axis-column) > 1)
    {
        printf("Error: Illegal move: Row or column: King\n");
        return 0;
    }

    // Checking if capturing or moving
    if (king_capture == 'i')
    {
        // Provera da li je slobodno polje
        if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
        {
            printf("Error: Illegal move: Piece in the way: King\n");
            return 0;
        }

        // Position input
        if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
            return 0;

        allow_castle_black[0] = 1;
        allow_castle_black[1] = 1;

        return 1;
    }
    else if (king_capture == 'x')
    {
        // Checking if there is a piece on the square
        if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
        {
            for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
            {
                if (strcmp(board[row][column], piece[i].piece_name) == 0)
                {
                    // Position input
                    if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                        return 0;

                    allow_castle_black[0] = 1;
                    allow_castle_black[1] = 1;

                    return 1;
                }
            }
        }
        else
        {
            printf("Error: No piece to capture: King\n");
            return 0;
        }
    }
    else
    {
        printf("Error: Capture: King\n");
        return 0;
    }
    
    return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int blackKnightMove(Pieces piece[NUMBER_OF_PIECES], int row, int column, char knight_piece[3], char knight_capture, Letters letter[NUMBER_OF_LETTERS])
{
    int tmp_piece = 0;
    for (int i = 0; i < NUMBER_OF_PIECES; i++)
    {
        if (!strcmp(piece[i].piece_name, knight_piece))
        {
            tmp_piece = i;
        }
    }

    int x_axis = piece[tmp_piece].pos.row;
    int y_axis = piece[tmp_piece].pos.column;

    if (!((row == x_axis-2 && column == y_axis-1) || (row == x_axis-2 && column == y_axis+1) || (row == x_axis-1 && column == y_axis+2) || (row == x_axis+1 && column == y_axis+2) ||
        (row == x_axis-1 && column == y_axis-2) || (row == x_axis+1 && column == y_axis-2) || (row == x_axis+2 && column == y_axis-1) || (row == x_axis+2 && column == y_axis+1)))
    {
        printf("Error: Illegal move: Row or column: Knight\n");
        return 0;
    }
    
    if (knight_capture == 'i')
    {
        if (strcmp(board[row][column], "00") && strcmp(board[row][column], "OO"))
        {
            printf("Error: Illegal move: Piece in the way: Knight\n");
            return 0;
        }

        // Position input
        if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
            return 0;

        return 1;
    }
    else if (knight_capture == 'x')
    {
        if (strcmp(board[row][column], "00") && strcmp(board[row][column], "OO"))
        {
            for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
            {
                if (strcmp(board[row][column], piece[i].piece_name) == 0)
                {
                    // Position input
                    if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                        return 0;

                    return 1;
                }
            }
        }
        else
        {
            printf("Error: No piece to capture: Knight\n");
            return 0;
        }
    }
    else
    {
        printf("Error: Capture: Knight\n");
        return 0;
    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int blackQueenMove(Pieces piece[NUMBER_OF_PIECES], int row, int column, char queen_piece[3], char queen_capture, Letters letter[NUMBER_OF_LETTERS])
{
    int tmp_piece = 0;
    for (int i = 0; i < NUMBER_OF_PIECES; i++)
    {
        if (!strcmp(piece[i].piece_name, queen_piece))
        {
            tmp_piece = i;
        }
    }
    int x_axis = piece[tmp_piece].pos.row;
    int y_axis = piece[tmp_piece].pos.column;
    
    // Checking if the row and colum are correct
    Diagonals diagonal[7];
    for (int i = 0; i < 7; i++)
    {
        diagonal[i].position.x_diagonals = 0;
        diagonal[i].position.y_diagonals = 0;
    }

    // Array of permited moves on the main diagonal
    int counter = 0;
    for (int i = 0; y_axis + i + 1 < 9 && x_axis + i + 1 < 8; i++)
    {
        diagonal[i].position.x_diagonals = x_axis + i + 1;
        diagonal[i].position.y_diagonals = y_axis + i + 1;
        counter = i;
    }
    for (int i = 0; y_axis - (i + 1) > 0 && x_axis - (i + 1) > -1; i++)
    {
        diagonal[counter].position.x_diagonals = x_axis - (i + 1);
        diagonal[counter].position.y_diagonals = y_axis - (i + 1);
        counter++;
    }
    int diagonal_check = 1;
    for (int i = 0; i < 7; i++)
    {
        if (row == diagonal[i].position.x_diagonals && column == diagonal[i].position.y_diagonals)
            diagonal_check = 0;
        else if (row+column == x_axis+y_axis)
            diagonal_check = 0;
        else if (column == y_axis || row == x_axis)
            diagonal_check = 0;
    }

    if(diagonal_check)
    {
        printf("Error: Illegal move: Row or column: Queen\n");
        return 0;
    }

    // Checking if capturing or moving
    if (queen_capture == 'i')
    {
        // Up Left
        if (x_axis < row && y_axis > column)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; x_axis+shifter <= row && y_axis-shifter >= column; shifter++)
            {
                if(strcmp(board[x_axis+shifter][y_axis-shifter], "00") && strcmp(board[x_axis+shifter][y_axis-shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Queen\n");
                    return 0;
                }
            }

            // Position input
            if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
                return 0;

            return 1;
        }
        // Up Right
        else if (x_axis < row && y_axis < column)
        {
            for (int shifter = 1; x_axis+shifter <= row && y_axis+shifter <= column; shifter++)
            {
                if(strcmp(board[x_axis+shifter][y_axis+shifter], "00") && strcmp(board[x_axis+shifter][y_axis+shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Queen\n");
                    return 0;
                }
            }

            // Position input
            if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
                return 0;

            return 1;
        }
        // Down Left
        else if (x_axis > row && y_axis > column)
        {
            for (int shifter = 1; x_axis-shifter >= row && y_axis-shifter >= column; shifter++)
            {
                if(strcmp(board[x_axis-shifter][y_axis-shifter], "00") && strcmp(board[x_axis-shifter][y_axis-shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Queen\n");
                    return 0;
                }
            }

            // Position input
            if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
                return 0;

            return 1;
        }
        // Down Right
        else if (x_axis > row && y_axis < column)
        {
            for (int shifter = 1; x_axis-shifter >= row && y_axis+shifter <= column; shifter++)
            {
                if(strcmp(board[x_axis-shifter][y_axis+shifter], "00") && strcmp(board[x_axis-shifter][y_axis+shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Queen\n");
                    return 0;
                }
            }

            // Position input
            if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
                return 0;

            return 1;
        }
        // Up
        else if (x_axis < row)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; x_axis+shifter <= row; shifter++)
            {
                if(strcmp(board[x_axis+shifter][y_axis], "00") && strcmp(board[x_axis+shifter][y_axis], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Queen\n");
                    return 0;
                }
            }

            // Position input
            if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
                return 0;

            return 1;
        }
        // Down
        else if (x_axis > row)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; x_axis-shifter >= row; shifter++)
            {
                if(strcmp(board[x_axis-shifter][y_axis], "00") && strcmp(board[x_axis-shifter][y_axis], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Queen\n");
                    return 0;
                }
            }

            // Position input
            if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
                return 0;

            return 1;
        }
        // Left
        else if (y_axis > column)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; y_axis-shifter >= column; shifter++)
            {
                if(strcmp(board[x_axis][y_axis-shifter], "00") && strcmp(board[x_axis][y_axis-shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Queen\n");
                    return 0;
                }
            }

            // Position input
            if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
                return 0;

            return 1;
        }
        // Right
        else if (y_axis < column)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; y_axis+shifter <= column; shifter++)
            {
                if(strcmp(board[x_axis][y_axis+shifter], "00") && strcmp(board[x_axis][y_axis+shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Queen\n");
                    return 0;
                }
            }

            // Position input
            if(!assignmentOfPositions(tmp_piece, row, column, piece, letter, 1))
                return 0;

            return 1;
        }
        else
        {
            printf("Error: Illegal move: Queen\n");
            return 0;
        }
    } /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else if (queen_capture == 'x')
    {
        // Up Left
        if (x_axis < row && y_axis > column)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; x_axis+shifter < row && y_axis-shifter > column; shifter++)
            {
                if(strcmp(board[x_axis+shifter][y_axis-shifter], "00") && strcmp(board[x_axis+shifter][y_axis-shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Queen\n");
                    return 0;
                }
            }
            
            // Checking if there is a piece on the square
            if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
            {
                for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                {
                    if (strcmp(board[row][column], piece[i].piece_name) == 0)
                    {
                        // Position input
                        if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                            return 0;

                        return 1;
                    }
                }
            }
            else
            {
                printf("Error: No piece to capture: Queen\n");
                return 0;
            }
        }
        // Up Right
        else if (x_axis < row && y_axis < column)
        {
            for (int shifter = 1; x_axis+shifter < row && y_axis+shifter < column; shifter++)
            {
                if(strcmp(board[x_axis+shifter][y_axis+shifter], "00") && strcmp(board[x_axis+shifter][y_axis+shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Queen\n");
                    return 0;
                }
            }
            
            // Checking if there is a piece on the square
            if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
            {
                for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                {
                    if (strcmp(board[row][column], piece[i].piece_name) == 0)
                    {
                        // Position input
                        if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                            return 0;

                        return 1;
                    }
                }
            }
            else
            {
                printf("Error: Illegal move: Piece in the way: Queen\n");
                return 0;
            }
        }
        // Down Left
        else if (x_axis > row && y_axis > column)
        {
            for (int shifter = 1; x_axis-shifter > row && y_axis-shifter > column; shifter++)
            {
                if(strcmp(board[x_axis-shifter][y_axis-shifter], "00") && strcmp(board[x_axis-shifter][y_axis-shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Queen\n");
                    return 0;
                }
            }
            
            // Checking if there is a piece on the square
            if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
            {
                for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                {
                    if (strcmp(board[row][column], piece[i].piece_name) == 0)
                    {
                        // Position input
                        if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                            return 0;

                        return 1;
                    }
                }
            }
            else
            {
                printf("Error: No piece to capture: Queen\n");
                return 0;
            }
        }
        // Down Right
        else if (x_axis > row && y_axis < column)
        {
            for (int shifter = 1; x_axis-shifter > row && y_axis+shifter < column; shifter++)
            {
                if(strcmp(board[x_axis-shifter][y_axis+shifter], "00") && strcmp(board[x_axis-shifter][y_axis+shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Queen\n");
                    return 0;
                }
            }
            
            // Checking if there is a piece on the square
            if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
            {
                for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                {
                    if (strcmp(board[row][column], piece[i].piece_name) == 0)
                    {
                        // Position input
                        if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                            return 0;

                        return 1;
                    }
                }
            }
            else
            {
                printf("Error: No piece to capture: Queen\n");
                return 0;
            }
        }
        // Up
        else if (x_axis < row)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; x_axis+shifter < row; shifter++)
            {
                if(strcmp(board[x_axis+shifter][y_axis], "00") && strcmp(board[x_axis+shifter][y_axis], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Queen\n");
                    return 0;
                }
            }

            // Checking if there is a piece on the square
            if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
            {
                for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                {
                    if (strcmp(board[row][column], piece[i].piece_name) == 0)
                    {
                        // Position input
                        if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                            return 0;

                        return 1;
                    }
                }
            }
            else
            {
                printf("Error: No piece to capture: Queen\n");
                return 0;
            }
        }
        // Down
        else if (x_axis > row)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; x_axis-shifter > row; shifter++)
            {
                if(strcmp(board[x_axis-shifter][y_axis], "00") && strcmp(board[x_axis-shifter][y_axis], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Queen\n");
                    return 0;
                }
            }

            // Checking if there is a piece on the square
            if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
            {
                for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                {
                    if (strcmp(board[row][column], piece[i].piece_name) == 0)
                    {
                        // Position input
                        if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                            return 0;

                        return 1;
                    }
                }
            }
            else
            {
                printf("Error: No piece to capture: Queen\n");
                return 0;
            }
        }
        // Left
        else if (y_axis < column)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; y_axis-shifter > column; shifter++)
            {
                if(strcmp(board[x_axis][y_axis-shifter], "00") && strcmp(board[x_axis][y_axis-shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Queen\n");
                    return 0;
                }
            }

            // Checking if there is a piece on the square
            if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
            {
                for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                {
                    if (strcmp(board[row][column], piece[i].piece_name) == 0)
                    {
                        // Position input
                        if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                            return 0;

                        return 1;
                    }
                }
            }
            else
            {
                printf("Error: No piece to capture: Queen\n");
                return 0;
            }
        }
        // Right
        else if (y_axis > column)
        {
            // Checking if there is a piece in the way
            for (int shifter = 1; y_axis+shifter < column; shifter++)
            {
                if(strcmp(board[x_axis][y_axis+shifter], "00") && strcmp(board[x_axis][y_axis+shifter], "OO"))
                {
                    printf("Error: Illegal move: Piece in the way: Queen\n");
                    return 0;
                }
            }

            // Checking if there is a piece on the square
            if(strcmp(board[row][column],"00") && strcmp(board[row][column],"OO"))
            {
                for (int i = 0; i < NUMBER_OF_PIECES / 2; i++)
                {
                    if (strcmp(board[row][column], piece[i].piece_name) == 0)
                    {
                        // Position input
                        if(!assignmentOfPositionsCapture(tmp_piece, i, row, column, piece, letter, 1))
                            return 0;

                        return 1;
                    }
                }
            }
            else
            {
                printf("Error: No piece to capture: Queen\n");
                return 0;
            }
        }
        else
        {
            printf("Error: Illegal move: Queen\n");
            return 0;
        }
    }
    else
    {
        printf("Error: Capture: Queen\n");
        return 0;
    }
    
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int blackCastleKingSide(Pieces piece[NUMBER_OF_PIECES], Letters letter[NUMBER_OF_LETTERS])
{
    if (allow_castle_black[0] == 1)
    {
        if (strcmp(board[7][2], "00") && strcmp(board[7][2], "OO"))
        {
            printf("Error: Illegal move: Piece in the way: castleKingSide\n");
            return 0;
        }
        else if (strcmp(board[7][3], "00") && strcmp(board[7][3], "OO"))
        {
            printf("Error: Illegal move: Piece in the way: castleKingSide\n");
            return 0;
        }
        else  if (lookingAt(piece, 1) == 1)
        {
            printf("Error: Illegal move you are in check! \n");
            return 0;
        }
        else 
        {
            int old_28row = piece[28].pos.row;
            int old_28column = piece[28].pos.column;

            int old_24row = piece[24].pos.row;
            int old_24column = piece[24].pos.column;

            piece[28].pos.row = 7;
            piece[28].pos.column = 2;

            piece[24].pos.row = 7;
            piece[24].pos.column = 3;

            startingPosition(piece, letter, 0);

            if (lookingAt(piece, 1) == 1)
            {
                piece[28].pos.row = old_28row;
                piece[28].pos.column = old_28column;

                piece[24].pos.row = old_24row;
                piece[24].pos.column = old_24column;

                printf("Error: Illegal move you are in check! \n");
                return 0;
            }

            return 1;
        }
        
    }
    else
    {
        printf("Error: Can't castle\n");
        return 0;
    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int blackCastleQueenSide(Pieces piece[NUMBER_OF_PIECES], Letters letter[NUMBER_OF_LETTERS])
{
    if (allow_castle_black[1] == 1)
    {
        if (strcmp(board[7][5], "00") && strcmp(board[7][5], "OO"))
        {
            printf("Error: Illegal move: Piece in the way: castleQueenSide\n");
            return 0;
        }
        else if (strcmp(board[7][6], "00") && strcmp(board[7][6], "OO"))
        {
            printf("Error: Illegal move: Piece in the way: castleQueenSide\n");
            return 0;
        }
        else if (strcmp(board[7][7], "00") && strcmp(board[7][7], "OO"))
        {
            printf("Error: Illegal move: Piece in the way: castleQueenSide\n");
            return 0;
        }
        else  if (lookingAt(piece, 1) == 1)
        {
            printf("Error: Illegal move you are in check! \n");
            return 0;
        }
        else 
        {
            int old_28row = piece[28].pos.row;
            int old_28column = piece[28].pos.column;

            int old_31row = piece[31].pos.row;
            int old_31column = piece[31].pos.column;

            piece[28].pos.row = 7;
            piece[28].pos.column = 6;

            piece[31].pos.row = 7;
            piece[31].pos.column = 5;
            
            startingPosition(piece, letter, 0);
            
            if (lookingAt(piece, 1) == 1)
            {
                piece[28].pos.row = old_28row;
                piece[28].pos.column = old_28column;

                piece[31].pos.row = old_31row;
                piece[31].pos.column = old_31column;

                printf("Error: Illegal move you are in check! \n");
                return 0;
            }

            return 1;
        }
        
    }
    else
    {
        printf("Error: Can't castle\n");
        return 0;
    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
