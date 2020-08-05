//Aadi Padmawar
#ifndef CONSTANT_H_INCLUDED_
#define CONSTANT_H_INCLUDED_

/* constant definitions */
#define WIDTH 8
#define HEIGHT 8
#define SLEN 120

typedef struct Board board;

enum Color {White, Black};
typedef void * (*Moves)(struct Board *initial, struct Board *array);

typedef struct piece {
	char PieceName[10];
	enum Color PieceColor;
	int points;
	int *PossibleMoves; /* replicates the board, 1 if it can move there, 0 if it cannot */
	Moves move;  /* pointer to functions that define possible moves for a piece */
	int hasMoved;
	int lastMoved;
} Piece;

typedef struct board {
	char location[2]; /*character array that stores the current location*/
	int row;          /*Int to the row of the location*/
	int col;	  /*Int to the col of the location*/
	Piece *piece;      /*Piece type objecct to the current piece*/
	int WhiteHit;
	int BlackHit;
} Board;

typedef void (*possibleMoves)(Board *board_struct);
#endif
