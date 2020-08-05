//Aadi Padmawar
#ifndef BOARD_H
#define BOARD_H

#include "Constants.h"

// typedef struct board {
// 	char location[2]; /*character array that stores the current location*/
// 	int row;          /*Int to the row of the location*/
// 	int col;	  /*Int to the col of the location*/
// 	Piece piece;      /*Piece type objecct to the current piece*/
// } Board;

/*create the game board*/
Board *createBoard(char location[2], Piece *piece, int x, int y);

/*De-allocate the gameboard */
void deleteBoard(Board *board);

/*Moves a piece from one place to another*/
int actuallyMoving(Board *initial_board, Board *final_board, Board array[8][8]);

void castle(Board *initial_board, Board *final_board, Board array[8][8]);

/*Returns the piece that is contained in the board struct*/
Piece *getPiece(Board *board);

/*Changes the pointer of the piece in the board struct to NULL*/
void removePiece(Board *board);

/*Changes the pointer of the piece in the board struct to the given parameter*/
int placePiece(Board *initial_board, Board *final_board);

/*Called when the king is getting attacked. Returns 0 or 1 based on whether it is checkmate or check. The parameter is the pointer of the boarrd array*/
int isCheck(Board boards[8][8], enum Color color);

/*Returns the row value from the user input*/
int GiveRow(char input[2]);

/*Returns the column value from the user input*/
int GiveColumn(char input[2]);

/*return the bool True for the element is inside the array false for not inside
bool Check_array(Board Possiblemove[29],char location[2]);*/

/*return the pointer of the char array of location by taking two in parameters of the row&col*/
char *Givelocation(int col, int row);

/* returns 1 if there is a stalemate */
int Stalemate(Board array[8][8], enum Color color);


#endif
