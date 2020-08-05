/* Piece.h */
/* Author: Ayesha Parvez, Aadi Padmawar */

#ifndef PIECE_H
#define PIECE_H
#include<string.h>
#include<strings.h>
#include <stdlib.h>
#include <stdbool.h>
#include "PieceMoves.h"
#include "Constants.h"

/* function to create a piece*/
Piece *createPiece(char name[10],enum Color color, Moves move, int points);

/* function to delete a piece */
void Deletepiece(Piece *piece);

/* function to check if a piece can move from one location to another */
bool canMove(Board *init_position, Board *fin_position,enum Color color);

/* checks if it's a possible move */
bool DoubleCheck(Board *initial_board, Board *final_board, Board array[8][8], enum Color color);

/* checks if a pawn can promote */
void Promotion(Board bigBoard[8][8], enum Color userColor, int opponent, int target_x, int target_y);

#endif
