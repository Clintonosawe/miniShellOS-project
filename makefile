# Makefile for SmartShell

CC = gcc
CFLAGS = -Wall -g -std=c99
OBJS = main.o shell_core.o utils.o

smartshell: $(OBJS)
	$(CC) $(CFLAGS) -o smartshell $(OBJS)

main.o: main.c shell_core.h utils.h
	$(CC) $(CFLAGS) -c main.c

shell_core.o: shell_core.c shell_core.h utils.h
	$(CC) $(CFLAGS) -c shell_core.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f *.o smartshell
