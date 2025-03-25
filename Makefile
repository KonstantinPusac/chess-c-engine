CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = chessMain.o whitePieces.o blackPieces.o additionalFunctions.o

chess: $(OBJ)
	$(CC) -o chess $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o chess
