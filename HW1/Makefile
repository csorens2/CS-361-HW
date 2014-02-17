CC = g++

CFLAGS = -g -w -fno-common -std=c99

CLEANFLAGSPARTONE = mainC.s mainC.i mainC.o func2C.s func2C.i func2C.o partOne 

CLEANFLAGSPARTTWO = mainCPP.s mainCPP.i mainCpp.o func2CPP.s func2CPP.i func2CPP.o myClass.i myClass.s myClass.o

all: partOne partTwo

partOne: mainC.o func2C.o
	$(CC) $(CFLAGS) mainC.c func2C.c -o mainC

partTwo: mainCPP.o func2CPP.o myClass.o
	$(CC) $(CFLAGS) mainCPP.c func2CPP.c myClass.cpp -o mainCPP


#Used in part one
mainC.o: mainC.s
	$(CC) $(CFLAGS) -o mainC.o -c mainC.s

mainC.s: mainC.i
	$(CC) $(CFLAGS) -o mainC.s -S mainC.i

mainC.i: mainC.c
	$(CC) $(CFLAGS) -o mainC.i -E mainC.c

func2C.o: func2C.s
	$(CC) $(CFLAGS) -o func2C.o -c func2C.s

func2C.s: func2C.i
	$(CC) $(CFLAGS) -o func2C.s -S func2C.i

func2C.i: func2C.c
	$(CC) $(CFLAGS) -o func2C.i -E func2C.c

#Used in part two

mainCPP.o: mainCPP.s
	$(CC) $(CFLAGS) -o mainCPP.o -c mainCPP.s

mainCPP.s: mainCPP.i
	$(CC) $(CFLAGS) -o mainCPP.s -S mainCPP.i

mainCPP.i: mainCPP.c
	$(CC) $(CFLAGS) -o mainCPP.i -E mainCPP.c

func2CPP.o: func2CPP.s
	$(CC) $(CFLAGS) -o func2CPP.o -c func2CPP.s

func2CPP.s: func2CPP.i
	$(CC) $(CFLAGS) -o func2CPP.s -S func2CPP.i

func2CPP.i: func2CPP.c
	$(CC) $(CFLAGS) -o func2CPP.i -E func2CPP.c

myClass.o: myClass.s
	$(CC) $(CFLAGS) -o myClass.o -c myClass.s

myClass.s: myClass.i
	$(CC) $(CFLAGS) -o myClass.s -S myClass.i

myClass.i: myClass.cpp
	$(CC) $(CFLAGS) -o myClass.i -E myClass.cpp


clean:
	rm -rf *o $(CLEANFLAGSPARTONE) $(CLEANFLAGSPARTTWO)
