//PieceMoves.h
//Aadi Padmawar

#ifndef PIECEMOVES_H
#define PIECEMOVES_H
#include "Constants.h"

void BishopPossibleMoves(Board *initial, Board array[8][8]);

void RookPossibleMoves(Board *initial, Board array[8][8]);

void QueenPossibleMoves(Board *initial, Board array[8][8]);

void KingPossibleMoves(Board *initial, Board array[8][8]);

void KnightPossibleMoves(Board *initial, Board array[8][8]);

void PawnPossibleMoves(Board *initial, Board array[8][8]);

Board *getBoardPos(Board *array, int x, int y);

int checkFree(Board *initial, Board array[8][8], int counter, int x, int y, int repeat);

void reset(Board *initial);

int PawnForwardMoves(Board *initial, Board array[8][8], int counter, int x, int y);

int PawnDiagonalMoves(Board *initial, Board array[8][8], int counter, int x, int y);

void CallAllPoss(Board BigBoard[8][8]);

void PossCastle(Board array[8][8]);

void PossEnPass(Board array[8][8]);

#endif
