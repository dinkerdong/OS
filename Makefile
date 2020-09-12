

all: main 
	
main: main.cpp ticket.cpp queue2.cpp
	g++ -o main main.cpp queue1.c ticket.cpp queue2.cpp
