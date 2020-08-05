#include <stdio.h>
#include <stdlib.h>
#include "FileIO.h"

/* Creates text file (Log.txt) for log of moves */
int createLogFile() {
	FILE *fptr;
	fptr = fopen("Log.txt", "w");
// Checks for seg fault
	if (fptr == NULL) {
		printf("Error!");
		return 0;
	}
// Frees FILE memory
	fclose(fptr);
	return 0;
}

/*  Writes the move that happened during that turn into log.txt. Message will be things such as "check" or "piece capture" */

void LogFile(Board *initial_board, Board *final_board, char message[SLEN]) {
//  Enter append mode for Log.txt
	FILE *fptr;
	fptr = fopen("Log.txt", "a");
// Format of message in the text file
	fprintf(fptr, "%s to %s: %s\n", initial_board->location, final_board->location, message);
// Frees FILE memory
	fclose(fptr);

}
