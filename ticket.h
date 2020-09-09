#ifndef TICKET_H
#define TICKET_H

#include <string>

class process
{
	public:
		process();

		std::string id;
		int arrival;
		int priority;
		int age;
		int tickets;

		void print_process();
};

#endif//TICKET_H
