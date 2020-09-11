#include "ticket.h"
#include <iostream>
using namespace std;

process::process(std::string new_id, int new_arrival, int new_priority, int new_age, int new_tickets)
{
    id = new_id;
    arrival = new_arrival;
    priority = new_priority;
    age = new_age;
    tickets = new_tickets;
}

void process::print_process()
{
	cout << id;
	cout << " " << arrival;
	cout << " " << priority;
	cout << " " << age;
	cout << " " << tickets << endl;
}

void process::print_details()
{
    cout << id;
    cout << " " << arrival;
    cout << " " << end;
    cout << " " << ready;
    cout << " " << running;
    cout << " " << waiting << endl;
}
