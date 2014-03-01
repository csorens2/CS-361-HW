CC = g++

CXXFLAGS = -std=gnu++0x  

CLEANFILES = mandel


all: mandel

mandel: mandel.o
			$(CC) $(CXXFLAGS) mandel.cpp -o mandel


clean:
		rm -rf *o $(CLEANFILES)
