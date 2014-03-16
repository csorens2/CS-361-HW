CC = g++

CSSFLAGS = -std=gnu++0x

CLEANFILES = calculate display generate

all: calculate display generate

calculate: calculate.o
			$(CC) $(CXXFLAGS) calculate.cpp -o calculate

display: display.o
			$(CC) $(CXXFLAGS) display.cpp -o display

generate: generate.o
			$(CC) $(CXXFLAGS) generate.cpp -o generate

clean:
			rm -rf *o $(CLEANFILES)
