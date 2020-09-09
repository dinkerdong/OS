#include <iostream>
#include "ticket.h"
#include "queue1.h"
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

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

// Should print the results after all tickets have been processed.
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

int main()
{
	int total;
	process temp;
	vector<process> input;

	freopen("input.txt", "r", stdin);

	while(cin >> temp.id >> temp.arrival >> temp.priority >> temp.age >> temp.tickets) {
		input.push_back(temp);
	}

	// TESTING
	cout << "before sort" << endl;
	print_processes(input);

	stable_sort(input.begin(), input.end(), arrival_compare);

	// TESTING
	cout << "after arrival sort" << endl;
	print_processes(input);

	queue<process> input_queue = vector_to_queue(input);
	cout << "printing queue of input" << endl;
	print_subqueue(input_queue);

	freopen("output.txt", "w", stdin);

	fclose(stdin);
	fclose(stdout);	

	return 0;
}
