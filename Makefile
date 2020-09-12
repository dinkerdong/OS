input = input.txt

all: main
	
main: TicketBooker.cpp ticket.cpp queue1.cpp
	g++ -o TicketBooker TicketBooker.cpp

run:
	./TicketBooker $(input)