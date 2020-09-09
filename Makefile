input = input.txt

all: main
	
main: main.cpp ticket.cpp queue1.cpp
	g++ -o main main.cpp ticket.cpp queue1.cpp

run:
	./main $(input)