CC = g++

CXXFLAGS = -std=gnu++0x  

CLEANFILES = mandelbrot


all: mandelbrot

mandelbrot: mandelbrot.o
			$(CC) $(CXXFLAGS) mandelbrot.cpp -o mandelbrot

clean:
		rm -rf *o $(CLEANFILES)
