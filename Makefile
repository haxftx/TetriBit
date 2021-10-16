CC = gcc
CFLAGS = -Wall -lm
SRC = tetribit.c
EXE = tetribit

build:
	$(CC) -o $(EXE) $(SRC) $(CFLAGS)
run:
	./$(EXE)
PHONY: clean
clean:
	rm -f $(EXE) *~
