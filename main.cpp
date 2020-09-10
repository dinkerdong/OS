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
	int total = 0;
	process temp;
	vector<process> queue2;

	freopen("input.txt", "r", stdin);

	while(cin >> temp.id >> temp.arrival >> temp.priority >> temp.age >> temp.tickets) {
		if (temp.priority >= 4) {
			if (temp.arrival == 0) {
				queue2.push_back(temp);
			} else {
				waiting.push_back(temp);
			}
		}
	}

	stable_sort(queue2.begin(), queue2.end(), SBJ_compare);

	while(0) {
		queue1.arrival_check(total);

		while (queue2.age_check() && queue1.arrival_check()) {
			queue2[0].tickets -= 1;
			queue2.age();	
			total += 5;

			if (queue2[0].tickets == 0) {
				queue2.erase(queue2.begin());
				if (queue2.arrival_check(total)) {
					stable_sort(queue2.begin(), queue2.end(), SBJ_compare);
				}
			}
		}

		queue1.push_back(queue2.promote());
	}



	freopen("output.txt", "w", stdin);

	fclose(stdin);
	fclose(stdout);	

	return 0;
}
