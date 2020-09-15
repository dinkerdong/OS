/* 
Created by: Norahmat Razmi, a1724818
	    Byung hun Hyun, a1732470

Contact emails: a1724818@student.adelaide.edu.au
		a1732470@student.adelaide.edu.au
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

#define TIME_UNIT 5

using namespace std;

// process Class: represents the customers to be processed
class process
{
	public:
		process(string new_id, int new_arrival, int new_priority, int new_age, int new_tickets, int unique_id);

		string id;
		int arrival;
		int priority;
		int age;
		int tickets;

		int unique_id;

		bool is_processed = false;
		int last_time_processed = -1;
		int how_many_processes = 0;

		int end = 0;
		int ready = 0;
		int running = 0;
		int waiting = 0;

		void print_process() const;
		void print_details() const;
};

process::process(string new_id, int new_arrival, int new_priority, int new_age, int new_tickets, int new_unique_id)
{
    id = new_id;
    arrival = new_arrival;
    priority = new_priority;
    age = new_age;
    tickets = new_tickets;
	unique_id = new_unique_id;
}

void process::print_process() const
{
	cout << id;
	cout << " " << arrival;
	cout << " " << priority;
	cout << " " << age;
	cout << " " << tickets;
	cout << " " << how_many_processes << endl;
}

void process::print_details() const
{
    cout << id;
    cout << " " << arrival;
    cout << " " << end;
    cout << " " << ready;
    cout << " " << running;
    cout << " " << waiting << endl;
}

struct queue1
{
    queue<process> subqueue1;
    queue<process> subqueue2;
    queue<process> subqueue3;

    void print_queue1();
    void add_to_queue1(process new_process);
    bool is_empty();

    void process_subqueue1();
    void process_subqueue2();
    void process_subqueue3();
};

void print_subqueue(queue<process>);
bool process_customer_q1(process&, int&);

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
    cout << "Printing Queue 1" << endl;
    cout << "Sub-Queue 1" << endl;
    print_subqueue(subqueue1);

    cout << "Sub-Queue 2" << endl;
    print_subqueue(subqueue2);

    cout << "Sub-Queue 3" << endl;
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
        // cout << "***Q1 - SOMETHING IS WRONG: Added invalid process***" << endl;
        // cout << "Caused by priority " << new_process.priority << endl; 
    }
}

bool queue1::is_empty()
{
    if (subqueue1.empty() && subqueue2.empty() && subqueue3.empty()) {
        return true;
    }

    return false;
}

// Struct queue2: this struct represents queue 2
// Queue 2 is represented by a vector,
// This vector of customers is sorted according to number of remaining tickets.
// Every time a new customer is added to queue 2, the vector stable sorts itself.

// Overload operator for vector to work with our process class
bool operator<(const process& a, const process& b) 
{
	if (a.tickets < b.tickets) {
		return true;
	} else if (a.tickets == b.tickets && a.arrival < b.arrival) {
		return true;
	}

	return false;
}

struct queue2
{
    vector<process> que2;

    void print_queue2();
    void add_to_queue2(process new_process);
    bool is_empty();
};

void print_subqueue(queue<process>);
bool process_customer_q1(process&, int&);

// Prints all the processes in queue 2 ONLY
// Printed according to tickets remaining, in ascending order.
void queue2::print_queue2()
{
	cout << "Printing Queue2" << endl;
	for (int i = 0; i < que2.size(); i++) {
		que2.at(i).print_process();
	}

	// cout << endl;
}

// Adds a process of priority > 3 to queue2.
// It should be impossible to add a process with any other priority, and prints an error otherwise.
void queue2::add_to_queue2(process new_process)
{
    if (new_process.priority > 3) {
        que2.push_back(new_process);
		stable_sort(que2.begin(), que2.end());
    } else {
        // cout << "***Q2 - SOMETHING IS WRONG: Added invalid process***" << endl;
        // cout << "Caused by priority " << new_process.priority << endl; 
    }
}

bool queue2::is_empty()
{
	return que2.empty();
}

static int current_time = 0;
static queue<process> input;
static queue1 q1;
static queue2 q2;

bool compare(const process& a, const process& b)
{
	if (a.age < b.age) {
		return true;
	} else if (a.age == b.age) {
		return a.unique_id < b.unique_id;
	}
}

// Process a customer with queue 1 logic, i.e. Weighted Round Robin.
// Returns true if all of the customer's tickets are processed.
// Else, returns false.
bool process_customer_q1(process& customer)
{
    int weighted_time_quantum = (10 - customer.priority) * 10;
    int tickets_processed = weighted_time_quantum/TIME_UNIT;

    customer.how_many_processes++;

    // If customer has never been processed, record time it was first processed.
    // Else, add amount of time it waited to be processed again.
    if (!customer.is_processed) {
        customer.ready = current_time;
        customer.is_processed = true;
    } else {
        customer.waiting += current_time - customer.last_time_processed;
    }

	// Holds all processes waiting to be promoted to queue 1.
	vector<process> buffer;

    // If number of tickets that can be processed is greater than or equal to customer's remaining tickets,
    // all of a customer's tickets can be processed.
    // Else, process the number of tickets calculated using the weighted_time_quantum.
    if (customer.tickets <= tickets_processed) {
        customer.running += customer.tickets * TIME_UNIT;
        current_time += customer.tickets * TIME_UNIT;

		for (int i = 0; i < q2.que2.size(); i++) {
			q2.que2.at(i).age += TIME_UNIT;
		}

		for (int i = 0; i < q2.que2.size(); i++) {
			if (q2.que2.at(i).age >= 100) {
				if (q2.que2.at(i).age > 100) {
					q2.que2.at(i).age -= 100;
				} else {
					q2.que2.at(i).age = 0;
				}

				q2.que2.at(i).priority--;

				if (q2.que2.at(i).priority <= 3) {
					buffer.push_back(q2.que2.at(i));
					q2.que2.erase(q2.que2.begin() + i);
					i--;
				} 

				stable_sort(buffer.begin(), buffer.end(), compare);
			}
		}

		// cout << "I'LL BE THERE FOR YOU" << endl;
		for (int i = 0; i < buffer.size(); i++) {
			buffer.at(i).age = 0;
			q1.add_to_queue1(buffer.at(i));
		}

        customer.tickets = 0;
        
        customer.end = current_time;
        customer.last_time_processed = current_time;

		customer.waiting = customer.end - customer.running - customer.ready;

		// TESTING
		// cout << "\nfinished processing at " << current_time << endl;

        customer.print_details();
        return true;
    } else {
        customer.running += tickets_processed * TIME_UNIT;
        current_time += tickets_processed * TIME_UNIT;

		for (int i = 0; i < q2.que2.size(); i++) {
			q2.que2.at(i).age += tickets_processed * TIME_UNIT;
		}

		for (int i = 0; i < q2.que2.size(); i++) {
			if (q2.que2.at(i).age >= 100) {
				if (q2.que2.at(i).age > 100) {
					q2.que2.at(i).age -= 100;
				} else {
					q2.que2.at(i).age = 0;
				}

				q2.que2.at(i).priority--;

				if (q2.que2.at(i).priority <= 3) {
					buffer.push_back(q2.que2.at(i));
					q2.que2.erase(q2.que2.begin() + i);
					i--;
				} 

				stable_sort(buffer.begin(), buffer.end(), compare);
			}
		}

		sort(buffer.begin(), buffer.end(), compare);

		// cout << "I'LL BE THERE FOR YOU" << endl;
		for (int i = 0; i < buffer.size(); i++) {
			buffer.at(i).age = 0;
			q1.add_to_queue1(buffer.at(i));
		}

        customer.last_time_processed = current_time;

        customer.tickets -= tickets_processed;

		// TESTING
		// cout << "processed at " << current_time << endl;
		// customer.print_process();
    }

    if (customer.how_many_processes == 2) {
        customer.how_many_processes = 0;
        customer.priority++;
    }

    return false;
}

// Process a customer with queue 2 logic, i.e. Shortest Remaining Time First.
// Returns true if all of the customer's tickets are processed.
bool process_customer_q2(process& customer)
{
	if (!customer.is_processed) {
		customer.ready = current_time;
		customer.is_processed = true;
	} 

	customer.running += TIME_UNIT;
	current_time += TIME_UNIT;
	customer.tickets--;

	for (int i = 1; i < q2.que2.size(); i++) {
		q2.que2.at(i).age += TIME_UNIT;
	}

	for (int i = 0; i < q2.que2.size(); i++) {
		if (q2.que2.at(i).age >= 100) {
			if (q2.que2.at(i).age > 100) {
				q2.que2.at(i).age -= 100;
			} else {
				q2.que2.at(i).age = 0;
			}

			q2.que2.at(i).priority--;

			if (q2.que2.at(i).priority <= 3) {
				q1.add_to_queue1(q2.que2.at(i));
				q2.que2.erase(q2.que2.begin() + i);
				i--;
			} 

			stable_sort(q2.que2.begin(), q2.que2.end(), compare);
		}
	}

	if (customer.tickets == 0) {
		customer.end = current_time;
		customer.last_time_processed = current_time;

		// TESTING
		// cout << "\nfinished processing at " << current_time <<  endl;

		customer.waiting = customer.end - customer.running - customer.ready;

		customer.print_details();
		return true;
	}

	return false;
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

// Only used for input vector
queue<process> vector_to_queue(vector<process> list)
{
	queue<process> new_queue;

	for (int i = 0; i < list.size(); i++) {
		new_queue.push(list.at(i));
	}

	return new_queue;
}

// It stops adding customers to these queues when current_time < process.arrival.
// i.e. when next customer can't be added at this point in time.
// Also stops when there are no more customers to add.
void add_to_queues()
{
	if (input.empty()) return;

	process temp = input.front();

	while ((!input.empty()) && temp.arrival <= current_time) {

		// // TESTING
		//cout << "\nadded at: " << current_time << endl; 
		// temp.print_process();

		if (temp.priority < 4) {
			q1.add_to_queue1(temp);
		} else {
			q2.add_to_queue2(temp);
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
Else, it is moved to the back of the appropriate subqueue of queue 1.
*/

void process_subqueue1() 
{
    if (process_customer_q1(q1.subqueue1.front())) {
        q1.subqueue1.pop();
    } else {
        process temp = q1.subqueue1.front();
        q1.subqueue1.pop();
		add_to_queues();

        q1.add_to_queue1(temp);
    }
}

void process_subqueue2() 
{
    if (process_customer_q1(q1.subqueue2.front())) {
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
    if (process_customer_q1(q1.subqueue3.front())) {
        q1.subqueue3.pop();
    } else {
        process temp = q1.subqueue3.front();
        q1.subqueue3.pop();
		add_to_queues();

		if (temp.priority < 4) {
			q1.add_to_queue1(temp);
		} else {
			q2.add_to_queue2(temp);
		}
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

void process_queue2()
{
	if (!q2.is_empty() && q1.is_empty()) {
		if (process_customer_q2(q2.que2.front())) {
			q2.que2.erase(q2.que2.begin());
		} else {
			process temp = q2.que2.front();
			q2.que2.erase(q2.que2.begin());
			add_to_queues();

			q2.add_to_queue2(temp);
		}
	}
}

void process_queues()
{
	process_queue1();
	process_queue2();
}

// Processes all the customers in the input queue
void process_tickets()
{
	while (!input.empty()) {
		add_to_queues();

		if (q1.is_empty() && q2.is_empty()) {
			current_time += TIME_UNIT;
		}

		// TESTING
		//cout << "\n1. As of: " << current_time << endl;
		//q1.print_queue1();
		//q2.print_queue2();
		//cout << endl;

		process_queues();
	}

	while (!q1.is_empty() || !q2.is_empty()) {
		process_queues();

		// TESTING
		//cout << "\n2. As of: " << current_time << endl;
		//q1.print_queue1();
		//q2.print_queue2();
		//cout << endl;
	}
}

int main(int argc, char *argv[])
{
	int total;
	vector<process> input1;

	string id, arrival, priority, age, tickets;

	//freopen(argv[1], "r", stdin);
	freopen("input.txt", "r", stdin);

	int i = 0;

	while(cin >> id >> arrival >> priority >> age >> tickets) {
		input1.push_back(process(id, stoi(arrival), stoi(priority), stoi(age), stoi(tickets), i));
		i++;
	}

	fclose(stdin);

	// Sorts input by arrival
	stable_sort(input1.begin(), input1.end(), arrival_compare);

	// By end of program, input should be empty.
	input = vector_to_queue(input1);

	// TESTING
	// cout << "printing queue of input" << endl;
	// print_subqueue(input);
	// cout << endl;
	

	cout << "name arrival end ready running waiting" << endl;
	process_tickets();

	// TESTING
	// q2.print_queue2();


	return 0;
}
