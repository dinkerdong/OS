#include <iostream>
#include "ticket.h"
#include "queue1.h"
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int time_unit = 5;
static int current_time = 0;
static queue1 q1;

/*
Used for sorting queue 2. 
Compares processes in queue 2 ONLY
If a process has less tickets, it should be processed first, i.e. moves ahead in the queue.
If two processes have the same # of tickets, they should be processed according to priority.
If two processes have the same # of tickets AND priority, they should be processed according to arrival.
*/
bool SBJ_compare(const process& p1, const process& p2)
{
	if (p1.tickets < p2.tickets) {
		return true;
	} else if (p1.tickets == p2.tickets && p1.arrival <= p2.arrival) {
		return true;
	} else {
		return false;
	}
}

bool arrival_compare(const process& p1, const process& p2)
{
	if (p1.arrival < p2.arrival) {
		return true;
	} else {
		return false;
	}
}

void print_processes(vector<process>& list)
{
	for (int i = 0; i < list.size(); i++) {
		list.at(i).print_process();
	}
}

// Should print the results after all customers have been processed.
// TO-DO: Make the vector global?
void output(vector<process>& list)
{
	cout << "name   arrival   end   ready   running   waiting" << endl;
	// NEED A FUNCTION WHICH CORRECTLY PRINTS THE RESULTS IN THE ABOVE ORDER
}

queue<process> vector_to_queue(vector<process> list)
{
	queue<process> new_queue;

	for (int i = 0; i < list.size(); i++) {
		new_queue.push(list.at(i));
	}

	return new_queue;
}

// Adds customer in input queue to queue 1 and queue 2.
// It does NOT add customers to these queues if current_time < process.arrival
// as a customer  would be processed before it has arrived.
void add_to_queues(queue<process>& input)
{
	process temp = input.front();

	// keep adding to queues until current_time < arrival of next added ticket
	// i.e. only add processes which can be processed at this point in time
	while (current_time <= temp.arrival && !input.empty()) {
		if (temp.priority < 4) {
			q1.add_to_queue1(temp);
		} else {
			// add to queue2
		}

		input.pop();

		if (!input.empty()) temp = input.front();
	}
}

void process_subqueue1() 
{
    if (process_customer(q1.subqueue1.front(), current_time)) {
        q1.subqueue1.pop();
    } else {
        process temp = q1.subqueue1.front();
        q1.subqueue1.pop();
        q1.subqueue1.push(temp);
    }
}

void process_subqueue2() 
{
    if (process_customer(q1.subqueue2.front(), current_time)) {
        q1.subqueue2.pop();
    } else {
        process temp = q1.subqueue2.front();
        q1.subqueue2.pop();
        q1.subqueue2.push(temp);
    }
}

void process_subqueue3() 
{
    if (process_customer(q1.subqueue3.front(), current_time)) {
        q1.subqueue3.pop();
    } else {
        process temp = q1.subqueue3.front();
        q1.subqueue3.pop();
        q1.subqueue3.push(temp);
    }
}

// Process customers in queue 1 ONLY
void process_queue1()
{
	while (!q1.is_empty()) {
		if (!q1.subqueue1.empty()) {
			process_subqueue1();	
		}

		if (!q1.subqueue2.empty()) {
			process_subqueue2();
		}

		if (!q1.subqueue3.empty()) {
			process_subqueue3();
		}
	}
}

// Processes all the customers in queue 1 and queue 2
void process_queues()
{
	if (!q1.is_empty()) {
		process_queue1();
	}
}

// Processes all the customers in the input queue
void process_tickets(queue<process>& input)
{
	while (!input.empty()) {
		add_to_queues(input);

		// process all customers at this point in time
		process_queues();
	}

	// POSSIBLY need to do a while-loop here, which keeps looping
	// until q1 and q2 are empty.
	// At that point, we can say all customers have been processed.
}

int main()
{
	int total;
	vector<process> input;

	string id, arrival, priority, age, tickets;

	freopen("input.txt", "r", stdin);

	while(cin >> id >> arrival >> priority >> age >> tickets) {
		input.push_back(process(id, stoi(arrival), stoi(priority), stoi(age), stoi(tickets)));
	}

	// Sorts input by arrival
	stable_sort(input.begin(), input.end(), arrival_compare);

	// Queue is in order of arrival
	// By end of program, this queue should be empty.
	queue<process> input_queue = vector_to_queue(input);

	// TESTING
	cout << "printing queue of input" << endl;
	print_subqueue(input_queue);
	cout << endl;

	process_tickets(input_queue);

	freopen("output.txt", "w", stdin);

	fclose(stdin);
	fclose(stdout);	

	return 0;
}
