#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

const int time_unit = 5;

// Class process: these are our customers which are processed
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

// Struct queue1: this object represents queue 1
struct queue1
{
    std::queue<process> subqueue1;
    std::queue<process> subqueue2;
    std::queue<process> subqueue3;

    void print_queue1();
    void add_to_queue1(process new_process);
    bool is_empty();

    void process_subqueue1();
    void process_subqueue2();
    void process_subqueue3();
};

void print_subqueue(std::queue<process>);
bool process_customer(process&, int&);

// Prints all the processes in a queue
void print_subqueue(queue<process> subqueue)
{
    while (!subqueue.empty()) {
        subqueue.front().print_process();
        subqueue.pop();
    }
}

// Prints all the processes in queue 1 ONLY
// Printed in order of priority.
void queue1::print_queue1()
{
    cout << "Queue 1" << endl;
    print_subqueue(subqueue1);

    cout << "Queue 2" << endl;
    print_subqueue(subqueue2);

    cout << "Queue 3" << endl;
    print_subqueue(subqueue3);
}

// Adds a process of priority 1 - 3 to queue1.
// It should be impossible to add a process with any other priority.
void queue1::add_to_queue1(process new_process)
{
    if (new_process.priority == 1) {
        subqueue1.push(new_process);
    } else if (new_process.priority == 2) {
        subqueue2.push(new_process);
    } else if (new_process.priority == 3) {
        subqueue3.push(new_process);
    } else {
        cout << "***Q1 - SOMETHING IS WRONG: Added invalid process***" << endl;
        cout << "Caused by priority " << new_process.priority << endl; 
    }
}

bool queue1::is_empty()
{
    if (subqueue1.empty() && subqueue2.empty() && subqueue3.empty()) {
        return true;
    }

    return false;
}

static int current_time = 0;
static queue<process> input;
static queue1 q1;

// Process a customer with queue 1 logic, i.e. Weighted Round Robin.
// Returns true if all of the customer's tickets are processed.
// Else, returns false.
bool process_customer(process& customer)
{

    int weighted_time_quantum = (10 - customer.priority) * 10;
    int tickets_processed = weighted_time_quantum/time_unit;

    customer.how_many_processes++;

    // If customer has never been processed, record time it was first processed.
    // Else, add amount of time it waited to be processed again.
    if (!customer.is_processed) {
        customer.ready = current_time;
        customer.is_processed = true;
    } else {
        customer.waiting += current_time - customer.last_time_processed;
    }

    // If number of tickets that can be processed is greater than or equal to customer's remaining tickets,
    // all of a customer's tickets can be processed.
    // Else, process the number of tickets calculated using the weighted_time_quantum.
    if (customer.tickets <= tickets_processed) {
        customer.running += customer.tickets * time_unit;
        current_time += customer.tickets * time_unit;


        customer.tickets = 0;
        
        customer.end = current_time;
        customer.last_time_processed = current_time;

		// cout << "finished processing" << endl;
        customer.print_details();
        return true;
    } else {
        customer.running += tickets_processed * time_unit;
        current_time += tickets_processed * time_unit;

        customer.last_time_processed = current_time;

        customer.tickets -= tickets_processed;
    }

    if (customer.how_many_processes == 2) {
        customer.how_many_processes = 0;
        customer.priority++;
    }

    return false;
}

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

queue<process> vector_to_queue(vector<process> list)
{
	queue<process> new_queue;

	for (int i = 0; i < list.size(); i++) {
		new_queue.push(list.at(i));
	}

	return new_queue;
}

// Adds customer in input queue to queue 1 and queue 2.
// It stops adding customers to these queues when current_time < process.arrival.
void add_to_queues()
{
	if (input.empty()) return;

	process temp = input.front();

	while ((!input.empty()) && temp.arrival <= current_time) {

		// TESTING
		// cout << "added at: " << current_time << endl; 

		// cout << "added at " << current_time << endl;
		// temp.print_process();

		if (temp.priority < 4) {
			q1.add_to_queue1(temp);
		} else {
			// add to queue2
		}

		input.pop();

		if (!input.empty()) {
			temp = input.front();
		}
	}
}

/* 
The following logic applies to all subqueues of queue 1.
If a customer has all of its tickets processed, it is removed from the queue.
Else, it is moved to the back of queue 1. If the customer's priority number changed,
it should be added to the appropriate subqueue.
*/

void process_subqueue1() 
{
    if (process_customer(q1.subqueue1.front())) {
        q1.subqueue1.pop();
    } else {
        process temp = q1.subqueue1.front();
        q1.subqueue1.pop();
		add_to_queues();

		// cout << "after adding" << endl;
		// q1.print_queue1();
        q1.add_to_queue1(temp);
    }
}

void process_subqueue2() 
{
    if (process_customer(q1.subqueue2.front())) {
        q1.subqueue2.pop();
    } else {
        process temp = q1.subqueue2.front();
        q1.subqueue2.pop();
		add_to_queues();

        q1.add_to_queue1(temp);
    }
}

void process_subqueue3() 
{
    if (process_customer(q1.subqueue3.front())) {
        q1.subqueue3.pop();
    } else {
        process temp = q1.subqueue3.front();
        q1.subqueue3.pop();
		add_to_queues();

		// This should be another function, which adds to queue 2
		// if new priority > 3.
        q1.add_to_queue1(temp);
    }
}

// Process customers in queue 1 ONLY
void process_queue1()
{
	if (!q1.is_empty()) {
		if (!q1.subqueue1.empty()) {
			process_subqueue1();
		}

		if (!q1.subqueue2.empty() && (q1.subqueue1.empty())) {
			process_subqueue2();
		}

		if (!q1.subqueue3.empty() && (q1.subqueue1.empty() && q1.subqueue2.empty())) {
			process_subqueue3();
		}
	}
}

// Processes all the customers in queue 1 and queue 2
void process_queues()
{
	process_queue1();

	// Also process queue 2
}

// Processes all the customers in the input queue
void process_tickets()
{
	while (!input.empty()) {
		add_to_queues();

		process_queues();

		/* 
		What if our queues are empty, but there are still customers in the input queue?
		There are no tickets being processed, but we will be stuck in this while loop.
		Since there is nothing to keep time "going".
		I'm thinking there should be a check here that increments current_time, until a new
		process from the input queue can be added to the queues.
		*/

		if (q1.is_empty()) {
			current_time += time_unit;
		}
	}

	// POSSIBLY need to do a while-loop here, which keeps looping
	// until q1 and q2 are empty.
	// At that point, we can say all customers have been processed.
	while (!q1.is_empty()) {
		process_queues();

		// cout << "after processing" << endl;
		// q1.print_queue1();
	}
}

int main(int argc, char *argv[])
{
	int total;
	vector<process> input1;

	string id, arrival, priority, age, tickets;

	freopen(argv[1], "r", stdin);

	while(cin >> id >> arrival >> priority >> age >> tickets) {
		input1.push_back(process(id, stoi(arrival), stoi(priority), stoi(age), stoi(tickets)));
	}

	// Sorts input by arrival
	stable_sort(input1.begin(), input1.end(), arrival_compare);

	// By end of program, input_queue should be empty (all customers added to queues).
	input = vector_to_queue(input1);

	// TESTING
	// cout << "printing queue of input" << endl;
	// print_subqueue(input);
	// cout << endl;

	cout << "name arrival end ready running waiting" << endl;
	process_tickets();

	return 0;
}
