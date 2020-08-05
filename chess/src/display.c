#include <stdio.h>
#include <string.h>
#include "display.h"
//


void printBoard(Board bigBoard[8][8]){

    char horiLine[] = "   -----------------------------------------\n";
    char emtyLine[] = "   |    |    |    |    |    |    |    |    |\n";
    Piece *PIECE;
   /* Board BOARD;*/
    char pieceName[10];
    char pieceIcon[] = " ";
    char x_location_label[] = "     A    B    C    D    E    F    G    H	\n";

    int lineNum;

    printf("%s", x_location_label);//print A...H


    for(int y = 0; y < 8; y++){
        lineNum = 8-y;

        printf("%s", horiLine);
        printf("%s", emtyLine);
        printf(" %d ", lineNum);
        for(int x = 0; x < 8; x++){
            
            
            PIECE = bigBoard[x][lineNum - 1].piece;

            if(PIECE == NULL){
                strcpy(pieceIcon, "  ");//set piece display to empty
            }
            
            else{
            strcpy(pieceName, PIECE->PieceName);
            
            //assign piece names
            if(strcmp(pieceName, "pawn") == 0){
                if(PIECE->PieceColor == White){
                    strcpy(pieceIcon, "WP"); 
                }
                else{
                    strcpy(pieceIcon, "BP");
                }}

            else if(strcmp(pieceName, "rook") == 0){
                if(PIECE->PieceColor == White){
                    strcpy(pieceIcon, "WR"); 
                }
                else{
                    strcpy(pieceIcon, "BR");
                }
            }
            else if(strcmp(pieceName, "knight") == 0){
                if(PIECE->PieceColor == White){
                    strcpy(pieceIcon, "WN"); 
                }
                else{
                    strcpy(pieceIcon, "BN");
                }
            }
            else if(strcmp(pieceName, "bishop") == 0){
                if(PIECE->PieceColor == White){
                    strcpy(pieceIcon, "WB"); 
                }
                else{
                    strcpy(pieceIcon, "BB");
                }
            }
            else if(strcmp(pieceName, "queen") == 0){
                if(PIECE->PieceColor == White){
                    strcpy(pieceIcon, "WQ"); 
                }
                else{
                    strcpy(pieceIcon, "BQ");
                }
            }
            else if(strcmp(pieceName, "king") == 0){
                if(PIECE->PieceColor == White){
                    strcpy(pieceIcon, "WK"); 
                }
                else{
                    strcpy(pieceIcon, "BK");
                }
            }
            }
            printf("| %s ", pieceIcon);
        }
        printf("|  ");

        printf("%d\n", lineNum);// print line numbers

        printf("%s", emtyLine);


    }
    printf("%s", horiLine);

    printf("%s", x_location_label);


}

