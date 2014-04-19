all : master worker

master : master.cpp message.h
	g++ -o master master.cpp
       
worker : worker.cpp message.h
	g++ -o worker worker.cpp

clean :
	rm master worker core *.o
      
debug : master.cpp worker.cpp
	g++ -o master -DDEBUG master.cpp
	g++ -o worker -DDEBUG worker.cpp
