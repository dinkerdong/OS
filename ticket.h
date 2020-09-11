#ifndef TICKET_H
#define TICKET_H

#include <string>

class process
{
	public:
		process(std::string new_id, int new_arrival, int new_priority, int new_age, int new_tickets);

		std::string id;
		int arrival;
		int priority;
		int age;
		int tickets;

		bool is_processed = false;
		int last_time_processed = -1;
		int how_many_processes = 0;

		int end = 0;
		int ready = 0;
		int running = 0;
		int waiting = 0;

		void print_process();
		void print_details();
};

#endif//TICKET_H
