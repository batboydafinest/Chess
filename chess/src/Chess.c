/* Module: Chess.c */
/* Author: Hafsah Arain, Aadi Padmawar */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "FileIO.h"
#include "Piece.h"
#include "Board.h"
#include "display.h"
#include "AI.h"
#include "PieceMoves.h"


int main (void) {
	/* variables */
	Board boardArray[WIDTH][HEIGHT];
	enum Color userSide;
	enum Color computerSide;
	double time = 0;
	//Moves possibleMovesFunc;
 	struct piece *Pieces;
	Board Board1;
	int x = 0, y = 0, s = 0, userValidInput = 0,ir = 0,ic = 0,fr = 0,fc = 0, game = 0, cont = 0, opponent=-1;
	char *buffer;
	char userInputInit[2], userInputFinal[2];
	char stringLocation[SLEN], userInputSide [SLEN], captureName[SLEN];
	char message[SLEN];
	int checkValue = 0, captureValue = 0, winValue = 0, stalemate = 0;  /* winValue = 2 means computer won, winValue = 1 means user won, used for printing messages */
	Board *boardPtr;
	//Moves temp = NULL;
	struct piece *WhitePiecesPtr[16];
	struct piece *BlackPiecesPtr[16];
	bool possMoveValue = false;
	char white[SLEN] = "white", black[SLEN] = "black";



	/* set up board/pieces,
	create White piece structs and append to array */
	for (x=0;x<8;x++) {
		Pieces = createPiece("pawn", White, &PawnPossibleMoves, 1);
		WhitePiecesPtr[x] = Pieces;
	} /*rof*/
	WhitePiecesPtr[8]  = createPiece("rook", White, &RookPossibleMoves, 5);
	WhitePiecesPtr[9]  = createPiece("knight", White, &KnightPossibleMoves, 3);
	WhitePiecesPtr[10] = createPiece("bishop", White, &BishopPossibleMoves, 3);
	WhitePiecesPtr[11] = createPiece("queen", White, &QueenPossibleMoves, 9);
	WhitePiecesPtr[12] = createPiece("king", White, &KingPossibleMoves, 10);
	WhitePiecesPtr[13] = createPiece("bishop", White, &BishopPossibleMoves, 3);
	WhitePiecesPtr[14] = createPiece("knight", White, &KnightPossibleMoves, 3);
	WhitePiecesPtr[15] = createPiece("rook", White, &RookPossibleMoves, 5);


	/* create Black piece structs and append to array */
	for (x=0;x<8;x++) {
		Pieces = createPiece("pawn", Black, &PawnPossibleMoves, 1);
		BlackPiecesPtr[x] = Pieces;
	} /*rof*/
	BlackPiecesPtr[8]  = createPiece("rook", Black, &RookPossibleMoves, 5);
	BlackPiecesPtr[9]  = createPiece("knight", Black, &KnightPossibleMoves, 3);
	BlackPiecesPtr[10] = createPiece("bishop", Black, &BishopPossibleMoves, 3);
	BlackPiecesPtr[11] = createPiece("queen", Black, &QueenPossibleMoves, 9);
	BlackPiecesPtr[12] = createPiece("king", Black, &KingPossibleMoves, 10);
	BlackPiecesPtr[13] = createPiece("bishop", Black, &BishopPossibleMoves, 3);
	BlackPiecesPtr[14] = createPiece("knight", Black, &KnightPossibleMoves, 3);
	BlackPiecesPtr[15] = createPiece("rook", Black, &RookPossibleMoves, 5);



	/* create board structures, append to 2D array */
	for (x=0;x<8;x++) {
		for (y=0;y<8;y++) {
			buffer = Givelocation(x,y);
			//stringLocation = *buffer;
			strcpy(stringLocation, buffer);
			if (y == 0) {
				boardPtr = createBoard(stringLocation, WhitePiecesPtr[x+8], x, y);
			} /*fi*/
			else if (y == 1) {
				boardPtr = createBoard(stringLocation, WhitePiecesPtr[x], x, y);
			} /* fi esle*/
			else if (y == 2 || y == 3 || y ==4 || y == 5) {
				boardPtr = createBoard(stringLocation, NULL, x, y);
			} /*fi esle*/
			else if (y == 7) {
				boardPtr = createBoard(stringLocation, BlackPiecesPtr[x+8], x, y);
			} /*fi esle*/
			else if (y == 6) {
				boardPtr = createBoard(stringLocation, BlackPiecesPtr[x], x, y);
			} /*fi esle*/
			Board1 = *boardPtr;
			boardArray[x][y] = Board1;
		} /*rof*/
	} /*rof*/

	/* create log file */
	createLogFile();

	/* print out beginning statements, allow user to choose sides */
	printf("Welcome to the game of chess!\n");

	while (userValidInput == 0) {
		printf("Would you like to play against another (player or computer)?: ");
		scanf("%s", userInputSide);
		if (strcmp(userInputSide, "player") == 0) {
			opponent = 0;
			userValidInput = 1;
		}
		else if (strcmp(userInputSide, "computer") == 0) {
			opponent = 1;
			userValidInput = 1;
		}
		else {
			printf("Please input a valid input (player or computer)\n");
		}
	}

	userValidInput = 0;

	while (userValidInput == 0) {
		printf("Please enter which side Player 1 would like to be on (white or black)?: ");
		scanf("%s", userInputSide);
		if (strcmp(userInputSide, white) == 0) {
			userSide = White;
			computerSide = Black;
			userValidInput = 1;
		}
		else if (strcmp(userInputSide, black) == 0) {
			userSide = Black;
			computerSide = White;
			userValidInput = 1;
		}
		else {
			printf("Please input a valid side (white or black)\n");
		}
	}

	/* start game */
	while (game == 0) {

			CallAllPoss(boardArray);

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (Stalemate(boardArray, White) == 1) {
				printf("Stalemate!\n");
				strcpy(message,"Stalemate!");
				LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
				game = 1;
				printBoard(boardArray);
				continue;
			}

			if (userSide == Black) {
				if (opponent == 0) {
					printBoard(boardArray);

					printf("Player 2's turn to move!\n");

					ir = -1;
					fr = -1;

					while (cont == 0) {

						/* takes user inputs and places into unsigned char array */
						printf("Enter the coordinates of the piece you would like to move (Use Capital Letters): ");
						scanf("%s", userInputInit);
						printf("Enter the coordinates of where you would like to move this piece (Use Capital Letters): ");
						scanf("%s", userInputFinal);

						/* creates board initial and final structures */
						for (x=0;x<8;x++) {
							for (y=0;y<8;y++) {
								if(strcmp(boardArray[x][y].location, userInputInit) == 0) {
									ir = x;
									ic = y;
								} /*fi*/
								if(strcmp(boardArray[x][y].location, userInputFinal) == 0) {
									fr = x;
									fc = y;
								} /*fi*/
							} /*rof*/
						} /*rof*/

						if (ir == -1 || fr == -1) {
							printf("ERROR: Please enter valid coordinates\n");
						}
						else {
							/* check if user move is possible */
							if (boardArray[ir][ic].piece->PieceName == NULL) {
								possMoveValue = false;
							} /*fi*/
							else {
								possMoveValue = canMove(&boardArray[ir][ic], &boardArray[fr][fc], computerSide);
								if (possMoveValue == true) {
									possMoveValue = DoubleCheck(&boardArray[ir][ic], &boardArray[fr][fc], boardArray, computerSide);
								}
							} /*esle*/
							if (possMoveValue == false) {
								printf("Not a possible move! Try again!\n");
								strcpy(message, "Player 2 tried making move that was not possible");
								LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
							} /*fi*/
							else {
								cont = 1;
							}
						}

					}

					cont = 0;

					/* set messages */
					if (possMoveValue == true) {
						s = snprintf(message,SLEN, "Player 2 moves white %s at %s to %s", boardArray[ir][ic].piece->PieceName, boardArray[ir][ic].location, boardArray[fr][fc].location);
						LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
					} /*fi*/
					if (strcmp(boardArray[ir][ic].piece->PieceName,"pawn") == 0 && boardArray[fr][fc].piece == NULL && (boardArray[fr][fc].row - boardArray[ir][ic].row == 1 || boardArray[fr][fc].row - boardArray[ir][ic].row == -1)) {
						s = snprintf(message,SLEN, "Player 2 captures black pawn at %s", boardArray[fr][fc-1].location);
						LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
					} /*fi*/
					if (boardArray[fr][fc].piece != NULL && boardArray[fr][fc].piece->PieceColor == 1) {
						s = snprintf(message,SLEN, "Player 2 captures black %s at %s", boardArray[fr][fc].piece->PieceName, boardArray[fr][fc].location);
						LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
					} /*fi*/

					/* actually move piece and update in boardArray*/
					captureValue = actuallyMoving(&boardArray[ir][ic], &boardArray[fr][fc], boardArray);

					Promotion(boardArray,userSide,opponent, fr,fc);

					CallAllPoss(boardArray);

					/* check for check/checkmate */
					checkValue = isCheck(boardArray, computerSide);
					if (checkValue == 1 && Stalemate(boardArray, computerSide) == 1) {
						printf("Checkmate!\n");
						printf("Player 2 wins!\n");
						strcpy(message, "Checkmate! White (Player 2) wins!");
						LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
						winValue = 1;
						game = 1;
						printBoard(boardArray);
						continue;
					} /*fi*/
					else if (checkValue == 1) {
						printf("Check!\n");
						strcpy(message, "White (Player 2) checks black!");
						LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
					} /*fi esle*/

					possMoveValue = false;
					checkValue = 0;
					captureValue = 0;

					//LogFile stuff

				}
				else {
					printBoard(boardArray);
					printf("computer's turn to move!\n");
					time = BestMove(boardArray, White,userSide, opponent);
					checkValue = isCheck(boardArray, computerSide);
					if (checkValue == 1 && Stalemate(boardArray, userSide) == 1) {
						printf("Checkmate!\n");
						printf("Computer wins!\n");
						strcpy(message, "Checkmate! White (Computer) wins!");
						LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
						winValue = 1;
						game = 1;
						printBoard(boardArray);
						continue;
					} /*fi*/
					else if (checkValue == 1) {
						printf("Check!\n");
						strcpy(message, "White (Computer) checks black!");
						LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
					} /*fi esle*/

					possMoveValue = false;
					checkValue = 0;
					captureValue = 0;
				}
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			CallAllPoss(boardArray);


			printBoard(boardArray);

			if (Stalemate(boardArray, userSide) == 1) {
				printf("Stalemate!\n");
				strcpy(message,"Stalemate!");
				LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
				game = 1;
				printBoard(boardArray);
				continue;
			}

			printf("Player 1's turn to move!\n");

			ir = -1;
			fr = -1;

			while (cont == 0) {

				/* takes user inputs and places into unsigned char array */
				printf("Enter the coordinates of the piece you would like to move (Use Capital Letters): ");
				scanf("%s", userInputInit);
				printf("Enter the coordinates of where you would like to move this piece (Use Capital Letters): ");
				scanf("%s", userInputFinal);

				/* creates board initial and final structures */
				for (x=0;x<8;x++) {
					for (y=0;y<8;y++) {
						if(strcmp(boardArray[x][y].location, userInputInit) == 0) {
							ir = x;
							ic = y;
						} /*fi*/
						if(strcmp(boardArray[x][y].location, userInputFinal) == 0) {
							fr = x;
							fc = y;
						} /*fi*/
					} /*rof*/
				} /*rof*/

				if (ir == -1 || fr == -1) {
					printf("ERROR: Please enter valid coordinates\n");
				}
				else {
					/* check if user move is possible */
					if (boardArray[ir][ic].piece->PieceName == NULL) {
						possMoveValue = false;
					} /*fi*/
					else {
						possMoveValue = canMove(&boardArray[ir][ic], &boardArray[fr][fc], userSide);
						if (possMoveValue == true) {
							possMoveValue = DoubleCheck(&boardArray[ir][ic], &boardArray[fr][fc], boardArray, userSide);
						}

					} /*esle*/
					if (possMoveValue == false) {
						printf("Not a possible move! Try again!\n");
						strcpy(message, "Player 1 tried making move that was not possible");
						LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
					} /*fi*/
					else {
						cont = 1;
					}
				}

			}

			cont = 0;

			/*set messages*/
			if (userSide == Black) {
				if (possMoveValue == true) {
					s = snprintf(message,SLEN, "Player 1 moves black %s at %s to %s", boardArray[ir][ic].piece->PieceName, boardArray[ir][ic].location, boardArray[fr][fc].location);
					LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
				} /*fi*/
				if (strcmp(boardArray[ir][ic].piece->PieceName,"pawn") == 0 && boardArray[fr][fc].piece == NULL && (boardArray[fr][fc].row - boardArray[ir][ic].row == 1 || boardArray[fr][fc].row - boardArray[ir][ic].row == -1)) {
					s = snprintf(message,SLEN, "Player 1 captures white pawn at %s", boardArray[fr][fc+1].location);
					LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
				} /*fi*/
				if (boardArray[fr][fc].piece != NULL && boardArray[fr][fc].piece->PieceColor == 1) {
					s = snprintf(message,SLEN, "Player 1 captures white %s at %s", boardArray[fr][fc].piece->PieceName, boardArray[fr][fc].location);
					LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
				} /*fi*/
			} /*fi*/
			else if (userSide == White) {
				if (possMoveValue == true) {
					s = snprintf(message,SLEN, "Player 1 moves white %s at %s to %s", boardArray[ir][ic].piece->PieceName, boardArray[ir][ic].location, boardArray[fr][fc].location);
					LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
				} /*fi*/
				if (strcmp(boardArray[ir][ic].piece->PieceName,"pawn") == 0 && boardArray[fr][fc].piece == NULL && (boardArray[fr][fc].row - boardArray[ir][ic].row == 1 || boardArray[fr][fc].row - boardArray[ir][ic].row == -1)) {
					s = snprintf(message,SLEN, "Player 1 captures black pawn at %s", boardArray[fr][fc-1].location);
					LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
				} /*fi*/
				if (boardArray[fr][fc].piece != NULL && boardArray[fr][fc].piece->PieceColor == 1) {
					s = snprintf(message,SLEN, "Player 1 captures black %s at %s", boardArray[fr][fc].piece->PieceName, boardArray[fr][fc].location);
					LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
				} /*fi*/
			} /*fi esle*/

			/* actually move piece and update in boardArray*/
			captureValue = actuallyMoving(&boardArray[ir][ic], &boardArray[fr][fc], boardArray);

			Promotion(boardArray,userSide,opponent, fr,fc);

			CallAllPoss(boardArray);

			/* check for check/checkmate */
			checkValue = isCheck(boardArray, userSide);
			if (checkValue == 1 && Stalemate(boardArray, Black) == 1) {
				printf("Checkmate!\n");
				printf("Player 1 wins!\n");
				if (userSide == Black) {
					strcpy(message, "Checkmate! Black (Player 1) wins!");
					LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
				} /*fi*/
				else if (userSide == White) {
					strcpy(message, "Checkmate! White (Player 1) wins!");
					LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
				} /*fi*/
				winValue = 1;
				game = 1;
				printBoard(boardArray);
				continue;
			} /*fi*/
			else if (checkValue == 1) {
				printf("Check!\n");
				if (userSide == Black) {
					strcpy(message, "Black (Player 1) checks white!");
					LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
				} /*fi*/
				else if (userSide == White) {
					strcpy(message, "White (Player 1) checks black!");
					LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
				} /*fi*/
			} /*fi esle*/

		possMoveValue = false;
		checkValue = 0;
		captureValue = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		CallAllPoss(boardArray);

		if (Stalemate(boardArray, Black) == 1) {
			printf("Stalemate!\n");
			strcpy(message,"Stalemate!");
			LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
			printBoard(boardArray);
			game = 1;
			continue;
		}



		if (userSide == White) {
			if (opponent == 0) {
				printBoard(boardArray);

				printf("Player 2's turn to move!\n");

				ir = -1;
				fr = -1;

				while (cont == 0) {

					/* takes user inputs and places into unsigned char array */
					printf("Enter the coordinates of the piece you would like to move (Use Capital Letters): ");
					scanf("%s", userInputInit);
					printf("Enter the coordinates of where you would like to move this piece (Use Capital Letters): ");
					scanf("%s", userInputFinal);

					/* creates board initial and final structures */
					for (x=0;x<8;x++) {
						for (y=0;y<8;y++) {
							if(strcmp(boardArray[x][y].location, userInputInit) == 0) {
								ir = x;
								ic = y;
							} /*fi*/
							if(strcmp(boardArray[x][y].location, userInputFinal) == 0) {
								fr = x;
								fc = y;
							} /*fi*/
						} /*rof*/
					} /*rof*/

					if (ir == -1 || fr == -1) {
						printf("ERROR: Please enter valid coordinates\n");
					}
					else {
						/* check if user move is possible */
						if (boardArray[ir][ic].piece->PieceName == NULL) {
							possMoveValue = false;
						} /*fi*/
						else {
							possMoveValue = canMove(&boardArray[ir][ic], &boardArray[fr][fc], computerSide);
							if (possMoveValue == true) {
								possMoveValue = DoubleCheck(&boardArray[ir][ic], &boardArray[fr][fc], boardArray, computerSide);
							}
						} /*esle*/
						if (possMoveValue == false) {
							printf("Not a possible move! Try again!\n");
							strcpy(message, "Player 2 tried making move that was not possible");
							LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
						} /*fi*/
						else {
							cont = 1;
						}
					}

				}

				cont = 0;

				/*set messages*/
				if (possMoveValue == true) {
					s = snprintf(message,SLEN, "Player 2 moves black %s at %s to %s", boardArray[ir][ic].piece->PieceName, boardArray[ir][ic].location, boardArray[fr][fc].location);
					LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
				} /*fi*/
				if (strcmp(boardArray[ir][ic].piece->PieceName,"pawn") == 0 && boardArray[fr][fc].piece == NULL && (boardArray[fr][fc].row - boardArray[ir][ic].row == 1 || boardArray[fr][fc].row - boardArray[ir][ic].row == -1)) {
					s = snprintf(message,SLEN, "Player 2 captures white pawn at %s", boardArray[fr][fc+1].location);
					LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
				} /*fi*/
				if (boardArray[fr][fc].piece != NULL && boardArray[fr][fc].piece->PieceColor == 1) {
					s = snprintf(message,SLEN, "Player 2 captures white %s at %s", boardArray[fr][fc].piece->PieceName, boardArray[fr][fc].location);
					LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
				} /*fi*/


				/* actually move piece and update in boardArray*/
				captureValue = actuallyMoving(&boardArray[ir][ic], &boardArray[fr][fc], boardArray);

				Promotion(boardArray,userSide,opponent, fr,fc);

				CallAllPoss(boardArray);

				/* check for check/checkmate */
				checkValue = isCheck(boardArray, computerSide);
				if (checkValue == 1 && Stalemate(boardArray, White) == 1) {
					printf("Checkmate!\n");
					printf("Player 2 wins!\n");
					strcpy(message, "Checkmate! Black (Player 2) wins!");
					LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
					printBoard(boardArray);
					winValue = 1;
					game = 1;
					continue;
				} /*fi*/
				else if (checkValue == 1) {
					printf("Check!\n");
					strcpy(message, "Black (Player 2) checks white!");
					LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
				} /*fi esle*/

				possMoveValue = false;
				checkValue = 0;
				captureValue = 0;

				//LogFile stuff

			}
			else {
				printBoard(boardArray);
				printf("computer's turn to move!\n");
				time = BestMove(boardArray, Black , userSide, 1);
				checkValue = isCheck(boardArray, computerSide);
				if (checkValue == 1 && Stalemate(boardArray, White) == 1) {
					printf("Checkmate!\n");
					printf("Computer wins!\n");
					strcpy(message, "Checkmate! Black (Computer) wins!");
					LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
					printBoard(boardArray);
					winValue = 1;
					game = 1;
					continue;
				} /*fi*/
				else if (checkValue == 1) {
					printf("Check!\n");
					strcpy(message, "Black (Computer) checks white!");
					LogFile(&boardArray[ir][ic], &boardArray[fr][fc], message);
				} /*fi esle*/

				possMoveValue = false;
				checkValue = 0;
				captureValue = 0;
			}
		}
	}



return 0;
}
