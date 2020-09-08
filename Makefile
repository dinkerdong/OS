

all: main 
	
main: main.cpp ticket.cpp
	g++ -o main main.cpp ticket.cpp
