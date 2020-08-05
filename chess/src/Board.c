/*EEECS22L SPRING 2020 TEAM 10*/
/*Module Name: Board Module*/
/*Author Name: Yuchen Yan, Aadi Padmawar*/



#include "Constants.h"
#include "Board.h"
#include "Piece.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

/*create the game board*/
Board *createBoard(char location_in[2], Piece *piece, int x, int y){
	Board *gameboard;
	gameboard = malloc(sizeof(Board));
	if(gameboard == NULL){
		printf("Memory allocation failed\n");
	}

strcpy(gameboard->location,location_in);
gameboard->piece = piece;
gameboard->row = x;
gameboard->col = y;
gameboard->WhiteHit = 0;
gameboard->BlackHit = 0;

return gameboard;

}

/*De-allocate the gameboard */
void deleteBoard(Board *board){
	assert(board);
	board->piece = NULL;
	free(board);
}

/*Changes the location of the piece*/
int placePiece(Board *initial_board, Board *final_board){
	Piece *before_piece, *after_piece;
	before_piece = initial_board->piece;
	after_piece = final_board->piece;

	initial_board->piece = NULL;
	if(after_piece != NULL){
		final_board->piece = NULL;
		final_board->piece = before_piece;
		return 1;
	}
	final_board->piece = before_piece;
	return 0;

}

/*Moves a piece from one place to another*/
int actuallyMoving(Board *initial_board, Board *final_board, Board array[8][8]){

		initial_board->piece->hasMoved += 1;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (array[i][j].piece != NULL) {
					array[i][j].piece->lastMoved = 0;
				}
			}
		}
		initial_board->piece->lastMoved = 1;

		//castling
		if (strcmp(initial_board->piece->PieceName, "king") == 0 && (final_board->row - initial_board->row == 2 || final_board->row - initial_board->row == -2)) {
			castle(initial_board,final_board,array);
			return placePiece(initial_board,final_board);
		}
		//enpasant
		if (strcmp(initial_board->piece->PieceName, "pawn") == 0 && final_board->piece == NULL && (final_board->row - initial_board->row == 1 || final_board->row - initial_board->row == -1)) {
			if (initial_board->piece->PieceColor == White) {
				placePiece(final_board, &array[final_board->row][final_board->col - 1]);
			}
			else {
				placePiece(final_board, &array[final_board->row][final_board->col + 1]);
			}
			placePiece(initial_board,final_board);
			return 1;
		}

	  return placePiece(initial_board,final_board);

}

void castle(Board *initial_board, Board *final_board, Board array[8][8]) {

	if (final_board->row - initial_board->row == 2) {
		placePiece(&array[7][initial_board->col],&array[5][initial_board->col]);
	}
	else {
		placePiece(&array[0][initial_board->col],&array[3][initial_board->col]);
	}

}


/*given the pointer to the board structures and return the piece of this structure*/
Piece *getPiece(Board *board){
	return board->piece;

}

/*Changes the pointer of the piece in the board struct to NULL*/
void removePiece(Board *board){
	board -> piece = NULL;

}



/*Called when the king is getting attacked. Returns 0 for nothing happends 1 for check, 2 for checkmate. The parameter is the pointer of the board array*/
int isCheck(Board array[8][8], enum Color color){
	int BlackKingX, BlackKingY, WhiteKingX, WhiteKingY;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (array[i][j].piece != NULL && strcmp(array[i][j].piece->PieceName, "king") == 0) {
				if (array[i][j].piece->PieceColor == White) {
					WhiteKingX = i;
					WhiteKingY = j;
				}
				else {
					BlackKingX = i;
					BlackKingY = j;
				}
			}
		}
	}

	if (color == White) {
		if (array[BlackKingX][BlackKingY].WhiteHit == 1) {
			return 1;
		}
		//not check
		return 0;
	}
	else {
		if (array[WhiteKingX][WhiteKingY].BlackHit == 1) {
			return 1;
		}
		//not check
		return 0;
	}

}


/*Returns the row value from the user input*/
int GiveRow(char input[2]){
	int row =0;
	char row_char ;
	row_char = input[1] - 49;
	row = row_char;
	return row;

}

/*Returns the column value from the user input*/
int GiveColumn(char input[2]){
	int col = 0;
	char col_char;
	col_char = input[0] - 65;
	col = col_char;
	return col;
}

/*return the char array of the input by taking two int parameters of the row and col*/
char *Givelocation(int col, int row){
	char Location[2];
	char col_c,row_c;
	char *Location_ptr;
	Location_ptr = &Location[0];
	col_c = col + 65;
	row_c = row + 49;
	Location[0] = col_c;
	Location[1] = row_c;

	return Location_ptr;
}

int Stalemate(Board array[8][8], enum Color color) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (array[i][j].piece != NULL && array[i][j].piece->PieceColor == color) {
				for (int a = 0; a < 8; a++) {
					for (int b = 0; b < 8; b++) {
						if (array[i][j].piece->PossibleMoves[a + (8*b)] == 1 && DoubleCheck(&array[i][j], &array[a][b],array, color) == true) {
							return 0;
						}
					}
				}
			}
		}
	}
	return 1;
}

//EOF
