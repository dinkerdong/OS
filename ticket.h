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
};

#endif//TICKET_H
