# Compiler
CC = gcc

# Include Files
INCLUDE = .

# Options for development 
CFLAGS = -g -Wall -ansi

myapp: main.o sqr.o cube.o
	$(CC) -o myapp main.o sqr.o cube.o
main.o: main.c main.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c main.c
sqr.o:  sqr.c main.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c sqr.c
cube.o: cube.c main.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c cube.c

clean:
	-rm main.o sqr.o cube.o



