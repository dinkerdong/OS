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
    print_subqueue(subqueue1);
    print_subqueue(subqueue2);
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
    }
}

