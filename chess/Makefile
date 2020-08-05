#######################################################################
# Chess Project, for EECS 22L Spring 2020
#######################################################################
# Variables
# Directory of all .c and .h files
SRC = src/
# Directory storing all .o and executables
BIN = bin/

# Compiler
CC = gcc

# Compiling flags
FLAGS = -g -ansi -std=c99 -Wall
CFLAGS = -c $(FLAGS)
DFLAGS = -DDEBUG $(FLAGS)

# List of .o files in bin/
OBJECTS = $(addprefix $(BIN), AI.o FileIO.o Chess.o Board.o display.o PieceMoves.o Piece.o)

################### Generate the executable ##########################
all: $(BIN)chess

$(BIN)chess: $(OBJECTS)
	$(CC) $(FLAGS) $^ -o $@

#################### Generate object files ###########################
# Target for FileIO.o
$(BIN)FileIO.o: $(SRC)FileIO.h $(SRC)FileIO.c $(SRC)Constants.h
	$(CC) $(CFLAGS) $(SRC)FileIO.c -o $(BIN)FileIO.o

# Target for Piece.o
$(BIN)Piece.o: $(SRC)Piece.h $(SRC)Piece.c $(SRC)PieceMoves.h $(SRC)Constants.h
	$(CC) $(CFLAGS) $(SRC)Piece.c -o $(BIN)Piece.o

# Target for Board.o
$(BIN)Board.o: $(SRC)Board.h $(SRC)Board.c $(SRC)Constants.h
	$(CC) $(CFLAGS) $(SRC)Board.c -o $(BIN)Board.o

# Target for Display.o
$(BIN)display.o: $(SRC)display.h $(SRC)display.c $(SRC)Constants.h
	$(CC) $(CFLAGS) $(SRC)display.c -o $(BIN)display.o

# Target for PieceMoves.o
$(BIN)PieceMoves.o: $(SRC)PieceMoves.h $(SRC)PieceMoves.c $(SRC)Constants.h
	$(CC) $(CFLAGS) $(SRC)PieceMoves.c -o $(BIN)PieceMoves.o

# Target for AI.o
$(BIN)AI.o: $(SRC)AI.h $(SRC)AI.c $(SRC)Board.h $(SRC)Constants.h $(SRC)Piece.h $(SRC)PieceMoves.h
	$(CC) $(CFLAGS) $(SRC)AI.c -o $(BIN)AI.o

# Target for Chess.o
$(BIN)Chess.o: $(SRC)PieceMoves.h $(SRC)Piece.h $(SRC)Constants.h $(SRC)display.h $(SRC)FileIO.h $(SRC)Board.h $(SRC)Chess.c
	$(CC) $(CFLAGS) $(SRC)Chess.c -o $(BIN)Chess.o

############################### other ################################
# Target for debuggable version of executable
test: $(OBJECTS)
	$(CC) $(DFLAGS) $^ -o $(BIN)test

# Creates tar.gz of entire directory
tar: $(BIN)chess
	tar -czvf $(CURDIR)/../Chess_V1.0_src.tar.gz $(CURDIR)

# Removes all object files and executables
clean:
	rm -f $(BIN)*.o
	rm -f $(BIN)chess
	rm -f $(BIN)test
	
