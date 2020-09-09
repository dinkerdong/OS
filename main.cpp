#include <iostream>
#include "ticket.h"
#include <vector>
#include <algorithm>

using namespace std;

// static int time = 5;

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

void print_process(process& p)
{
	cout << p.id;
	cout << " " << p.arrival;
	cout << " " << p.priority;
	cout << " " << p.age;
	cout << " " << p.tickets << endl;
}

void print_processes(vector<process>& list)
{
	for (int i = 0; i < list.size(); i++) {
		print_process(list.at(i));
	}
}

int main()
{
	int total;
	process temp;
	vector<process> queue2;

	freopen("input.txt", "r", stdin);

	while(cin >> temp.id >> temp.arrival >> temp.priority >> temp.age >> temp.tickets) {
		queue2.push_back(temp);
	}

	// TESTING
	cout << "before sort" << endl;
	print_processes(queue2);

	stable_sort(queue2.begin(), queue2.end(), SBJ_compare);

	// TESTING
	cout << "after sort" << endl;
	print_processes(queue2);

	freopen("output.txt", "w", stdin);

	fclose(stdin);
	fclose(stdout);	

	return 0;
}
