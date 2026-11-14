CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic
OBJ=main.o artemis.o validaciones.o
all: artemis
artemis: $(OBJ)
	$(CC) $(CFLAGS) -o artemis $(OBJ) -lm
main.o: main.c artemis.h
	$(CC) $(CFLAGS) -c main.c
artemis.o: artemis.c artemis.h validaciones.h
	$(CC) $(CFLAGS) -c artemis.c
validaciones.o: validaciones.c validaciones.h
	$(CC) $(CFLAGS) -c validaciones.c
clean:
	rm -f $(OBJ) artemis
.PHONY: all clean
