#include <iostream>
#include "ticket.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <queue1.h>
#include "queue2.h"

using namespace std;

const int time_unit = 5;
static int current_time = 0;
static queue1 q1;

bool SBJ_compare(process p1, process p2)
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

bool arrival_check(vector<process> wait, int total)
{
	for (int i = 0; i < wait.size(); i++) {
		if (wait[i].arrival == total) {
			return true;
		} else {
			return false;
		}
	}
}

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

void process_queues()
{
	if (!q1.is_empty()) {
		process_queue1();
	}
}

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
	int total = 0;
	process temp;
	vector<process> input, wait1, wait2;
	queue2 low_pri;

	freopen("input.txt", "r", stdin);

	while(cin >> temp.id >> temp.arrival >> temp.priority >> temp.age >> temp.tickets) {
		temp.promote_time = temp.arrival;
		temp.proc = 0;

		if (temp.priority <= 3 && temp.arrival == 0) {
			input.push_back(temp);		
		} else if (temp.priority <= 3) {
			wait1.push_back(temp);		
		} else if (temp.priority >= 4) {
			if (temp.arrival == 0) {
				low_pri.list.push_back(temp);
			} else {
				wait2.push_back(temp);
			}
		}
	}

	stable_sort(input.begin(), input.end(), arrival_compare);
	stable_sort(wait1.begin(), wait2.end(), arrival_compare);
	queue<process> input_queue = vector_to_queue(input);			


	fclose(stdin);

	stable_sort(low_pri.list.begin(), low_pri.list.end(), SBJ_compare);

	int fuck;

	while(1) {
		wait1.arrival_check(total);
		process_ticket(input_queue);
		queue1.demote();

		while (!low_pri.age_check(total) || !arrival_check(wait1, total)) {
			print_process(low_pri.list);
			low_pri.list[0].proc = 1;
			low_pri.list[0].tickets -= 1;
			low_pri.age();	
			total += 5;

			if (arrival_check(wait2, total)) {
				for (int i = 0; i < wait2.size(); i++) {
					if (wait2[i].arrival >= total) {
						low_pri.list.push_back(wait2[i]);
					}
				}
			}

			if (low_pri.list[0].tickets == 0) {
				low_pri.list.erase(low_pri.list.begin());
				stable_sort(low_pri.list.begin(), low_pri.list.end(), SBJ_compare);
			}

			if (low_pri.list.size() == 0) {
				break;
			}
		}

		if (low_pri.promote.size() != 0) {
			low_pri.promote();
			low_pri.queue2.clear();
		}

		//queue1.push_back(list.promote());
		
		if (low_pri.list.size() == 0) {
			break;
		}
	}


	freopen("output.txt", "w", stdin);

	fclose(stdout);	

	return 0;
}
