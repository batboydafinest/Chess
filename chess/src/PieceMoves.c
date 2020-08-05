//PieceMoves.c
//Aadi Padmawar

#include <stdio.h>
#include <string.h>

#include "PieceMoves.h"



void BishopPossibleMoves(Board *initial, Board array[8][8]) {

  int counter = 0;

  reset(initial);

  //checks top right diagonal
  counter = checkFree(initial, array, counter, 1, 1, 8);

  //check top left diagonal
  counter = checkFree(initial, array, counter, -1, 1, 8);

  //check bottom right diagonal
  counter = checkFree(initial, array, counter, 1, -1, 8);

  //check bottom left diagonal
  counter = checkFree(initial, array, counter, -1, -1, 8);

}

void RookPossibleMoves(Board *initial, Board array[8][8]) {

  int counter = 0;

  reset(initial);

  //checks right row
  counter = checkFree(initial, array, counter, 1, 0, 8);

  //check left row
  counter = checkFree(initial, array, counter, -1, 0, 8);

  //check top col
  counter = checkFree(initial, array, counter, 0, 1, 8);

  //check bottom col
  counter = checkFree(initial, array, counter, 0, -1, 8);

}

void QueenPossibleMoves(Board *initial, Board array[8][8]) {

  int counter = 0;

  reset(initial);

  //checks right row
  counter = checkFree(initial, array, counter, 1, 0, 8);

  //check left row
  counter = checkFree(initial, array, counter, -1, 0, 8);

  //check top col
  counter = checkFree(initial, array, counter, 0, 1, 8);

  //check bottom col
  counter = checkFree(initial, array, counter, 0, -1, 8);

  //checks top right diagonal
  counter = checkFree(initial, array, counter, 1, 1, 8);

  //check top left diagonal
  counter = checkFree(initial, array, counter, -1, 1, 8);

  //check bottom right diagonal
  counter = checkFree(initial, array, counter, 1, -1, 8);

  //check bottom left diagonal
  counter = checkFree(initial, array, counter, -1, -1, 8);

}

void KingPossibleMoves(Board *initial, Board array[8][8]) {

  int counter = 0;

  //makes PossibleMoves array in initial piece to null
  reset(initial);

  //checks right row
  counter = checkFree(initial, array, counter, 1, 0, 1);

  //check left row
  counter = checkFree(initial, array, counter, -1, 0, 1);

  //check top col
  counter = checkFree(initial, array, counter, 0, 1, 1);

  //check bottom col
  counter = checkFree(initial, array, counter, 0, -1, 1);

  //checks top right diagonal
  counter = checkFree(initial, array, counter, 1, 1, 1);

  //check top left diagonal
  counter = checkFree(initial, array, counter, -1, 1, 1);

  //check bottom right diagonal
  counter = checkFree(initial, array, counter, 1, -1, 1);

  //check bottom left diagonal
  counter = checkFree(initial, array, counter, -1, -1, 1);

}

void KnightPossibleMoves(Board *initial, Board array[8][8]) {

  int counter = 0;

  reset(initial);

  //check 2,1
  counter = checkFree(initial, array, counter, 2, 1, 1);

  //check 1,2
  counter = checkFree(initial, array, counter, 1, 2, 1);

  //check -1,2
  counter = checkFree(initial, array, counter, -1, 2, 1);

  //check -2,1
  counter = checkFree(initial, array, counter, -2, 1, 1);

  //check -2,-1
  counter = checkFree(initial, array, counter, -2, -1, 1);

  //check -1,-2
  counter = checkFree(initial, array, counter, -1, -2, 1);

  //check 1,-2
  counter = checkFree(initial, array, counter, 1, -2, 1);

  //check 2,-1
  counter = checkFree(initial, array, counter, 2, -1, 1);

}

void PawnPossibleMoves(Board *initial, Board array[8][8]) {

  int counter = 0;

  reset(initial);

  //checks if space in front is free
  if (initial->piece->PieceColor == Black) {
    counter = PawnForwardMoves(initial, array, counter, 0, -1);
  }
  else {
    counter = PawnForwardMoves(initial, array, counter, 0, 1);
  }

  //sees if it can move 2 spaces

  if (initial->piece->PieceColor == Black && initial->piece->hasMoved == 0 && counter == 1) {
    counter = PawnForwardMoves(initial, array, counter, 0, -2);
  }
  else if (initial->piece->PieceColor == White && initial->piece->hasMoved == 0 && counter == 1) {
    counter = PawnForwardMoves(initial, array, counter, 0, 2);
  }

  //checks if there are pieces that can be taken in diagonal

  if (initial->piece->PieceColor == Black) {
    counter = PawnDiagonalMoves(initial, array, counter, 1, -1);
    counter = PawnDiagonalMoves(initial, array, counter, -1, -1);
  }
  else {
    counter = PawnDiagonalMoves(initial, array, counter, 1, 1);
    counter = PawnDiagonalMoves(initial, array, counter, -1, 1);
  }

}



Board *getBoardPos(Board *array, int x, int y) {
  return (array + (x) + (8 * y ));
}

int PawnDiagonalMoves(Board *initial, Board array[8][8], int counter, int x, int y) {
  int tempx = initial->row;
  int tempy = initial->col;
  Board *temp, *ini = &array[tempx][tempy];

  tempx += x;
  tempy += y;
  temp = &array[tempx][tempy];

  if (tempy < 0 || tempx < 0 || tempx > 7 || tempy > 7) {
    return counter;
  }

  if (ini->piece->PieceColor == White) {
    array[tempx][tempy].WhiteHit = 1;
  }
  else {
    array[tempx][tempy].BlackHit = 1;
  }

  if (temp->piece != NULL) {

    if (ini->piece->PieceColor == temp->piece->PieceColor) {
      return counter;
    }

    else {
      ini->piece->PossibleMoves[tempx + (tempy * 8)] = 1;
      counter++;
      return counter;
    }

  }
  return counter;

}

int PawnForwardMoves(Board *initial, Board array[8][8], int counter, int x, int y) {

  int tempx = initial->row;
  int tempy = initial->col;
  Board *temp, *ini = &array[tempx][tempy];

  tempx += x;
  tempy += y;
  temp = &array[tempx][tempy];

  if (tempy < 0 || tempx < 0 || tempx > 7 || tempy > 7) {
    return counter;
  }

  if (temp->piece == NULL) {

    ini->piece->PossibleMoves[tempx + (tempy * 8)] = 1;
    counter++;

  }
  return counter;
}

int checkFree(Board *initial, Board array[8][8], int counter, int x, int y, int repeat) {

  int tempx = initial->row;
  int tempy = initial->col;
  Board *temp, *ini = &array[tempx][tempy];

  for (int i = 0; i < repeat; i++) {
    tempx += x;
    tempy += y;
    temp = &array[tempx][tempy];

    if (tempy < 0 || tempx < 0 || tempx > 7 || tempy > 7) {
      return counter;
    }

    if (temp->piece == NULL) {

      ini->piece->PossibleMoves[tempx + (tempy * 8)] = 1;
      if (ini->piece->PieceColor == White) {
        array[tempx][tempy].WhiteHit = 1;
      }
      else {
        array[tempx][tempy].BlackHit = 1;
      }
      counter++;

    }
    else {

      if (ini->piece->PieceColor == temp->piece->PieceColor) {
        return counter;
      }

      else {
        ini->piece->PossibleMoves[tempx + (tempy * 8)] = 1;
        counter++;
        if (ini->piece->PieceColor == White) {
          array[tempx][tempy].WhiteHit = 1;
        }
        else {
          array[tempx][tempy].BlackHit = 1;
        }
        return counter;
      }

    }

  }

  return counter;

}

void reset(Board *initial) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      initial->piece->PossibleMoves[i + (j*8)] = 0;
    }
  }
}

void CallAllPoss(Board BigBoard[8][8]) {
  Moves mu = NULL;
  Board *temp = &BigBoard[0][0];

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      BigBoard[i][j].WhiteHit = 0;
      BigBoard[i][j].BlackHit = 0;
    }
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      temp = &BigBoard[i][j];
      if (temp->piece != NULL) {
        mu = temp->piece->move;
        mu(&BigBoard[i][j], BigBoard);
      }
    }
  }
  PossCastle(BigBoard);
  PossEnPass(BigBoard);
}

void PossCastle(Board array[8][8]) {

  //white right
  if (array[4][0].piece != NULL && strcmp(array[4][0].piece->PieceName, "king") == 0 && array[4][0].piece->hasMoved == 0 && array[7][0].piece != NULL && strcmp(array[7][0].piece->PieceName, "rook") == 0 && array[7][0].piece->hasMoved == 0) {
    if (array[5][0].piece == NULL && array[6][0].piece == NULL && array[4][0].BlackHit == 0 && array[5][0].BlackHit == 0 && array[6][0].BlackHit == 0) {
      array[4][0].piece->PossibleMoves[6] = 1;
    }
  }
  //white left
  if (array[4][0].piece != NULL && strcmp(array[4][0].piece->PieceName, "king") == 0 && array[4][0].piece->hasMoved == 0 && array[0][0].piece != NULL && strcmp(array[0][0].piece->PieceName, "rook") == 0 && array[0][0].piece->hasMoved == 0) {
    if (array[3][0].piece == NULL && array[2][0].piece == NULL && array[1][0].piece == NULL && array[4][0].BlackHit == 0 && array[3][0].BlackHit == 0 && array[2][0].BlackHit == 0 && array[1][0].BlackHit == 0) {
      array[4][0].piece->PossibleMoves[2] = 1;
    }
  }
  //black right
  if(array[4][7].piece != NULL && strcmp(array[4][7].piece->PieceName, "king") == 0 && array[4][7].piece->hasMoved == 0 && array[7][7].piece != NULL && strcmp(array[7][7].piece->PieceName, "rook") == 0 && array[7][7].piece->hasMoved == 0) {
    if (array[5][7].piece == NULL && array[6][7].piece == NULL && array[4][7].WhiteHit == 0 && array[5][7].WhiteHit == 0 && array[6][7].WhiteHit == 0) {
      array[4][7].piece->PossibleMoves[62] = 1;
    }
  }
  //black left
  if (array[4][7].piece != NULL && strcmp(array[4][7].piece->PieceName, "king") == 0 && array[4][7].piece->hasMoved == 0 && array[0][7].piece != NULL && strcmp(array[0][7].piece->PieceName, "rook") == 0 && array[0][7].piece->hasMoved == 0) {
    if (array[3][7].piece == NULL && array[2][7].piece == NULL && array[1][7].piece == NULL && array[4][7].WhiteHit == 0 && array[3][7].WhiteHit == 0 && array[2][7].WhiteHit == 0 && array[1][7].WhiteHit == 0) {
      array[4][7].piece->PossibleMoves[58] = 1;
    }
  }


}

void PossEnPass(Board array[8][8]) {
  for (int i = 0; i < 8; i++) {
    //white pawns
    if (array[i][4].piece != NULL && strcmp(array[i][4].piece->PieceName, "pawn") == 0 && array[i][4].piece->PieceColor == White) {
      //right
      if (i < 7 && array[i+1][5].piece == NULL && array[i+1][4].piece != NULL && strcmp(array[i+1][4].piece->PieceName, "pawn") == 0 && array[i+1][4].piece->lastMoved == 1 && array[i+1][4].piece->hasMoved == 1 && array[i+1][4].piece->PieceColor == Black) {
        array[i][4].piece->PossibleMoves[(i+1) + (8*5)] = 1;
      }
      //left
      if (i > 0 && array[i-1][5].piece == NULL && array[i-1][4].piece != NULL && strcmp(array[i-1][4].piece->PieceName, "pawn") == 0 && array[i-1][4].piece->lastMoved == 1 && array[i-1][4].piece->hasMoved == 1 && array[i-1][4].piece->PieceColor == Black) {
        array[i][4].piece->PossibleMoves[(i-1) + (8*5)] = 1;
      }

    }
    //black pawns
    if (array[i][3].piece != NULL && strcmp(array[i][3].piece->PieceName, "pawn") == 0 && array[i][3].piece->PieceColor == Black) {
      //right
      if (i < 7 && array[i+1][2].piece == NULL && array[i+1][3].piece != NULL && strcmp(array[i+1][3].piece->PieceName, "pawn") == 0 && array[i+1][3].piece->lastMoved == 1 && array[i+1][3].piece->hasMoved == 1 && array[i+1][3].piece->PieceColor == White) {
        array[i][3].piece->PossibleMoves[(i+1) + (8*2)] = 1;
      }
      //left
      if (i > 0 && array[i-1][2].piece == NULL && array[i-1][3].piece != NULL && strcmp(array[i-1][3].piece->PieceName, "pawn") == 0 && array[i-1][3].piece->lastMoved == 1 && array[i-1][3].piece->hasMoved == 1 && array[i-1][3].piece->PieceColor == White) {
        array[i][3].piece->PossibleMoves[(i-1) + (8*2)] = 1;
      }

    }


  }
}
