CC = g++ -std=gnu++0x

all : master worker

master : master.cpp 
	$(CC) master.cpp -o master
       
worker : worker.cpp 
	$(CC) worker.cpp -o worker

clean :
	rm master worker core *.o
      
debug : master.cpp worker.cpp
	g++ -o master -DDEBUG master.cpp
	g++ -o worker -DDEBUG worker.cpp
