CC = g++

CXXFLAGS = -std=gnu++0x  

CLEANFILES = mandelbrot mandelCalc mandelDisplay


all: mandelbrot mandelCalc mandelDisplay

mandelbrot: mandelbrot.o
			$(CC) $(CXXFLAGS) mandelbrot.cpp -o mandelbrot

mandelCalc: mandelCalc.o
			$(CC) $(CXXFLAGS) mandelCalc.cpp -o mandelCalc

mandelDisplay: mandelDisplay.o
			$(CC) $(CXXFLAGS) mandelDisplay.cpp -o mandelDisplay

clean:
		rm -rf *o $(CLEANFILES)
