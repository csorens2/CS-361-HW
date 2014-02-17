CC = g++

CFLAGS = -g -w -fno-common -std=gnu++0x

CLEANFILES = keyboard

all: keyboard


keyboard: keyboard.o
		$(CC) $(CFLAGS) keyboard.c -o keyboard


clean:
	rm -rf *o $(CLEANFILES)
