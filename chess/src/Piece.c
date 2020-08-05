/* Piece.c */
/* Author: Ayesha Parvez, Aadi Padmawar */

#include "Piece.h"
#include "FileIO.h"
#include "Board.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

/* function to create a piece */
Piece *createPiece(char name[10],enum Color color, Moves moves, int points){
	/*int row = 8;
	int col = 8;*/
	Piece *new_piece = malloc(sizeof(Piece));
	new_piece -> PossibleMoves = (int*)malloc(sizeof(int)*64);
	strcpy(new_piece -> PieceName, name);
	new_piece -> PieceColor = color;
	new_piece -> points = points;
	new_piece -> move = moves;
	new_piece -> hasMoved = 0;
	new_piece -> lastMoved = 0;
	return(new_piece);
}


/* function to delete a piece */
void Deletepiece(Piece *piece){
	/*assert(piece -> PossibleMoves != NULL);
	free(piece -> PossibleMoves);*/
	assert(piece != NULL);
	free(piece);
}


/* function to check if a piece can move from one location to another */
bool canMove(Board *init_position, Board *fin_position,enum Color color){
	int x = fin_position -> row;
	int y = fin_position -> col;
	if (init_position -> piece ->PieceColor != color) {
		return false;
	}
	/* checking if desired final location is available */
	if(init_position -> piece -> PossibleMoves[x + (y*8)] == 1){
		return true;
	}
	return false;
}

bool DoubleCheck(Board *initial_board, Board *final_board, Board array[8][8], enum Color color) {
	Piece *ini = initial_board->piece, *fin = final_board->piece;

	//enpassant
	if (strcmp(initial_board->piece->PieceName, "pawn") == 0 && final_board->piece == NULL && (final_board->row - initial_board->row == 1 || final_board->row - initial_board->row == -1)) {
		Piece *temp;
		Board *b;
		if (initial_board->piece->PieceColor == White) {
			temp = array[final_board->row][final_board->col - 1].piece;
			b = &array[final_board->row][final_board->col - 1];
			placePiece(final_board, &array[final_board->row][final_board->col - 1]);
		}
		else {
			temp = array[final_board->row][final_board->col + 1].piece;
			b = &array[final_board->row][final_board->col + 1];
			placePiece(final_board, &array[final_board->row][final_board->col + 1]);
		}
		placePiece(initial_board,final_board);
		CallAllPoss(array);

		for(int i = 0; i < 8; i++) {
			for(int j = 0; j < 8; j++) {
				if (array[i][j].piece != NULL && strcmp(array[i][j].piece->PieceName, "king") == 0 && array[i][j].piece->PieceColor == color) {
					if (color == White && array[i][j].BlackHit == 1) {
						initial_board->piece = ini;
						final_board->piece = fin;
						b->piece = temp;
						CallAllPoss(array);
						return false;
					}
					else if (array[i][j].WhiteHit == 1) {
						initial_board->piece = ini;
						final_board->piece = fin;
						b->piece = temp;
						CallAllPoss(array);
						return false;
					}
				}
			}
		}
		initial_board->piece = ini;
		final_board->piece = fin;
		b->piece = temp;
		CallAllPoss(array);
		return true;

	}
	//all other moves (don't care about castling cause u cant castle into check)
	placePiece(initial_board, final_board);
	CallAllPoss(array);
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			if (array[i][j].piece != NULL && strcmp(array[i][j].piece->PieceName, "king") == 0 && array[i][j].piece->PieceColor == color) {
				if (color == White && array[i][j].BlackHit == 1) {
					initial_board->piece = ini;
					final_board->piece = fin;
					CallAllPoss(array);
					return false;
				}
				else if (array[i][j].WhiteHit == 1) {
					initial_board->piece = ini;
					final_board->piece = fin;
					CallAllPoss(array);
					return false;
				}
			}
		}
	}
	initial_board->piece = ini;
	final_board->piece = fin;
	CallAllPoss(array);
	return true;
}



//Promotion(boardArray,userSide,opponent, fr,fc);
/*opponent == 0 for pvp, 1 for user vs PC*/

void Promotion(Board bigBoard[8][8], enum Color userColor, int opponent, int target_x, int target_y){

	Piece *thePiece;
	Board *theBoard;
	enum Color newPieceColor;
	char newPieceName[10];
	int newHasMoved;
	int newLastMoved;
	int promoPossible = 0;
	int done = 0;
	char messages[SLEN];
	if(target_y == 0 || target_y == 7){

		theBoard = &bigBoard[target_x][target_y];
		thePiece = theBoard->piece;

		if(strcmp(thePiece->PieceName, "pawn") == 0){
			promoPossible = 1;
			newPieceColor = thePiece->PieceColor;
			newHasMoved = thePiece->hasMoved;
			newLastMoved = thePiece->lastMoved;
			Deletepiece(thePiece);

			}



	if(promoPossible){
		while(done == 0){

			if(newPieceColor == userColor || opponent == 0){//if promoting piece is players
				printf("\nEnter what piece you want to promo to(lower case): ");
				scanf("%s", newPieceName);
			}
			else{
				strcpy(newPieceName,"queen");//promo to queen if it's PC
			}

			if(strcmp(newPieceName, "rook") == 0){
				thePiece = createPiece(newPieceName, newPieceColor, &RookPossibleMoves, 5);
				snprintf(messages,SLEN, "Pawn at %s promoted to rook", bigBoard[target_x][target_y].location);
				if (bigBoard[target_x][target_y].piece->PieceColor == White) {
					LogFile(&bigBoard[target_x][target_y-1],&bigBoard[target_x][target_y],messages);
				}
				else if (bigBoard[target_x][target_y].piece->PieceColor == Black) {
					LogFile(&bigBoard[target_x][target_y+1],&bigBoard[target_x][target_y],messages);
				}
				break;
			}
			else if(strcmp(newPieceName, "knight") == 0){
				thePiece = createPiece(newPieceName, newPieceColor, &KnightPossibleMoves, 3);
				snprintf(messages,SLEN, "Pawn at %s promoted to knight", bigBoard[target_x][target_y].location);
				if (bigBoard[target_x][target_y].piece->PieceColor == White) {
					LogFile(&bigBoard[target_x][target_y-1],&bigBoard[target_x][target_y],messages);
				}
				else if (bigBoard[target_x][target_y].piece->PieceColor == Black) {
					LogFile(&bigBoard[target_x][target_y+1],&bigBoard[target_x][target_y],messages);
				}
				break;
			}
			else if(strcmp(newPieceName, "bishop") == 0){
				thePiece = createPiece(newPieceName, newPieceColor, &BishopPossibleMoves, 3);
				snprintf(messages,SLEN, "Pawn at %s promoted to bishop", bigBoard[target_x][target_y].location);
				if (bigBoard[target_x][target_y].piece->PieceColor == White) {
					LogFile(&bigBoard[target_x][target_y-1],&bigBoard[target_x][target_y],messages);
				}
				else if (bigBoard[target_x][target_y].piece->PieceColor == Black) {
					LogFile(&bigBoard[target_x][target_y+1],&bigBoard[target_x][target_y],messages);
				}
				break;
			}
			else if(strcmp(newPieceName, "queen") == 0){
				thePiece = createPiece(newPieceName, newPieceColor, &QueenPossibleMoves, 9);
				snprintf(messages,SLEN, "Pawn at %s promoted to queen", bigBoard[target_x][target_y].location);
				if (bigBoard[target_x][target_y].piece->PieceColor == White) {
					LogFile(&bigBoard[target_x][target_y-1],&bigBoard[target_x][target_y],messages);
				}
				else if (bigBoard[target_x][target_y].piece->PieceColor == Black) {
					LogFile(&bigBoard[target_x][target_y+1],&bigBoard[target_x][target_y],messages);
				}
				break;
			}
			else{
				printf("not valid input try again.");
			}
		}

			thePiece->hasMoved = newHasMoved;
			thePiece->lastMoved = newLastMoved;
	}

	}}
