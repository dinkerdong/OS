#include "ticket.h"
#include "queue1.h"
#include <iostream>
#include <queue>
using namespace std;

const int time_unit = 5;

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
        cout << "***SOMETHING IS WRONG***" << endl;
        cout << "added invalid process to queue1" << endl;
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

bool process_customer(process& customer, int& current_time)
{
    int weighted_time_quantum = (10 - customer.priority) * 10;
    int tickets_processed = weighted_time_quantum/time_unit;

    customer.how_many_processes++;

    if (!customer.is_processed) {
        customer.ready = current_time;
        customer.is_processed = true;
    } else {
        customer.waiting += current_time - customer.last_time_processed;
    }

    if (customer.tickets <= tickets_processed) {
        customer.running += customer.tickets * time_unit;
        current_time += customer.tickets * time_unit;

        customer.tickets = 0;
        
        customer.end = current_time;
        customer.last_time_processed = current_time;

        cout << "Finished processing!" << endl;
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
