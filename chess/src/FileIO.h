/* FileIO.h for Team 10          */
/*                               */
/* Modifiers: Jeremy Chang       */

#ifndef FILEIO_H
#define FILEIO_H

#include "Constants.h"

/* Creates text file for log of moves */
int createLogFile();

/* Writes the move that happened during that turn into log.txt. Message will be things such as "check" or "piece capture" */
void LogFile(Board *initial_board, Board *final_board, char message[SLEN]);

#endif
