CC = g++

CSSFLAGS = -std=gnu++0x

CLEANFILES = calculate display generate

all: calculate display generate

calculate: calculate.o
			$(CC) $(CSSFLAGS) calculate.cpp -o calculate

display: display.o
			$(CC) $(CSSFLAGS) display.cpp -o display

generate: generate.o
			$(CC) $(CSSFLAGS) generate.cpp -o generate

clean:
			rm -rf *o $(CLEANFILES)
