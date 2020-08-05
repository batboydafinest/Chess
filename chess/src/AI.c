/* AI.c */
/* Authors:  Ayesha Parvez, Yuchen Yen， Huiquan Li*/

#include "AI.h"
#include "Piece.h"
#include "FileIO.h" 
#include "display.h"

/* Selects a move to make*/ 
double BestMove(Board b_array[8][8],enum Color MyColor, enum Color userSide, int opponent){ 
  int flag = 0; // variable to check if a move can be made 
  // for each piece, check if it can be moved
  time_t start = time(NULL);
  time_t time_lapse = 57;//3 seconds for moving piece, etc.
  time_t runtime = start + time_lapse;
	int score = 0;
	int temp_m = 0;
	int temp_i = 0;
	int temp_j = 0;
	int temp_k = 0;

	int changed = 0; 
  char Message[SLEN];
  int s = 0;  
  while(start < runtime && flag == 0){    
    for(int m = 0; m <8; m++){
	for(int i=0; i < 8; i++){
           if(b_array[m][i].piece != NULL && b_array[m][i].piece->PieceColor == MyColor){
		for(int j = 0; j < 8; j++){
			for(int k = 0; k < 8; k++){
				if(b_array[m][i].piece->PossibleMoves[j + 8*k] == 1 && DoubleCheck(&b_array[m][i],&b_array[j][k],b_array,MyColor)){
					if(changed == 0){
					temp_m = m;
					temp_i = i;
					temp_j = j;
					temp_k = k;
					}
					if(b_array[j][k].piece != NULL){ 
					if(b_array[j][k].piece->points >= score){
						score = b_array[j][k].piece->points;
						temp_m = m;
						temp_i = i;
						temp_j = j;
						temp_k = k;
						changed = 1;

					}
					}
					/*
					actuallyMoving(&b_array[m][i], &b_array[j][k],b_array);  
					flag = 1;
					break;
					*/
			       }
			}
			if(flag == 1){
				break;
			}
		}
		if(flag == 1){
			break;
		}
	    }
	}
    }
	if (MyColor == White) { 
		s = snprintf(Message,SLEN, "Computer moves white %s at %s to %s", b_array[temp_m][temp_i].piece->PieceName, b_array[temp_m][temp_i].location, b_array[temp_j][temp_k].location);
		LogFile(&b_array[temp_m][temp_i], &b_array[temp_j][temp_k], Message);
		if (strcmp(b_array[temp_m][temp_i].piece->PieceName,"pawn") == 0 && b_array[temp_j][temp_k].piece == NULL && (b_array[temp_j][temp_k].row - b_array[temp_m][temp_i].row == 1 || b_array[temp_j][temp_k].row - b_array[temp_m][temp_i].row == -1)) {
			s = snprintf(Message,SLEN, "Computer captures black pawn at %s", b_array[temp_j][temp_k-1].location);
			LogFile(&b_array[temp_m][temp_i], &b_array[temp_j][temp_k], Message);
		} 
		if (b_array[temp_j][temp_k].piece != NULL && b_array[temp_j][temp_k].piece->PieceColor == Black) {
			s = snprintf(Message,SLEN, "Computer captures black %s at %s", b_array[temp_j][temp_k].piece->PieceName, b_array[temp_j][temp_k].location);
			LogFile(&b_array[temp_m][temp_i], &b_array[temp_j][temp_k], Message);
		} 
	} 
	else if (MyColor == Black) { 
		s = snprintf(Message,SLEN, "Computer moves black %s at %s to %s", b_array[temp_m][temp_i].piece->PieceName, b_array[temp_m][temp_i].location, b_array[temp_j][temp_k].location);
		LogFile(&b_array[temp_m][temp_i], &b_array[temp_j][temp_k], Message);
		if (strcmp(b_array[temp_m][temp_i].piece->PieceName,"pawn") == 0 && b_array[temp_j][temp_k].piece == NULL && (b_array[temp_j][temp_k].row - b_array[temp_m][temp_i].row == 1 || b_array[temp_j][temp_k].row - b_array[temp_m][temp_i].row == -1)) {
			s = snprintf(Message,SLEN, "Computer captures white pawn at %s", b_array[temp_j][temp_k+1].location);
			LogFile(&b_array[temp_m][temp_i], &b_array[temp_j][temp_k], Message);
		} 
		if (b_array[temp_j][temp_k].piece != NULL && b_array[temp_j][temp_k].piece->PieceColor == White) {
			s = snprintf(Message,SLEN, "Computer captures white %s at %s", b_array[temp_j][temp_k].piece->PieceName, b_array[temp_j][temp_k].location);
			LogFile(&b_array[temp_m][temp_i], &b_array[temp_j][temp_k], Message);
		} 
	} 
	actuallyMoving(&b_array[temp_m][temp_i], &b_array[temp_j][temp_k],b_array);
/*
	printBoard(b_array);
*/
	Promotion(b_array ,userSide,opponent, temp_j,temp_k);
	printf("AI moves %s from %s to %s \n",b_array[temp_j][temp_k].piece->PieceName,b_array[temp_m][temp_i].location,b_array[temp_j][temp_k].location);
	changed = 0;
	flag = 1;
	break;
    start = time(NULL);
   }
  // stalemate 
   if(flag == 0){
	printf("\n\nSTALEMATE\n\n");
   }
   return((double)(time_lapse)); 
}	

/*
Board *Medium_Move(Board board[8][8], enum Color player_color){
	Board *final_board;
	for(x=0;x<8;x++){
		for(y=0;y<8;y++){
			board[x][y].piece->points
			
     			

		}
	}

}
*/
