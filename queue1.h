#include "ticket.h"
#include <iostream>
#include <queue>

#ifndef QUEUE1_H
#define QUEUE1_H

// A queue1 structure
// Made up of 3 subqueues, each corresponding to priorities 1 - 3.
struct queue1
{
    std::queue<process> subqueue1;
    std::queue<process> subqueue2;
    std::queue<process> subqueue3;

    void print_queue1();
    void add_to_queue1(process new_process);
    bool is_empty();
};

void print_subqueue(std::queue<process>);

#endif