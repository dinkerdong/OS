#include <iostream>
#include "ticket.h"
#include <vector>
#include <algorithm>

using namespace std;

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

void print_process(vector<process> list)
{
	for (int i = 0; i < list.size(); i++) {
		cout << list[i].id << " " << list[i].arrival << " " << list[i].priority << " " << list[i].age << " " << list[i].tickets << endl;
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

	stable_sort(queue2.begin(), queue2.end(), SBJ_compare);

	freopen("output.txt", "w", stdin);

	fclose(stdin);
	fclose(stdout);	

	return 0;
}
