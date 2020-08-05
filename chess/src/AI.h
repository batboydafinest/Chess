/* AI.h" */
/* Author: Ayesha Parvez */

#ifndef AI_H
#define AI_H
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "Constants.h"
#include "Board.h"
#include "Piece.h"
#include "PieceMoves.h"

/* function to move a piece for the computer */
double BestMove(Board b_array[8][8],enum Color MyColor, enum Color userSide, int opponent);


#endif
