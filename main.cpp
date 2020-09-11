#include <iostream>
#include "ticket.h"
#include <vector>
#include <algorithm>
#include "queue2.h"

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


	cout << endl;;
	cout << endl;;
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

int main()
{
	int total = 0;
	process temp;
	vector<process> wait1, wait2;
	queue2 low_pri;

	freopen("input.txt", "r", stdin);

	while(cin >> temp.id >> temp.arrival >> temp.priority >> temp.age >> temp.tickets) {
		if (temp.priority == 1 && temp.arrival == 0) {
			
		} else if (temp.priority == 2 && temp.arrival == 0) {


		} else if (temp.priority == 3 && temp.arrival == 0) {

		} else if (temp.priority >= 4) {
			if (temp.arrival == 0) {
				temp.promote_time = temp.arrival;
				low_pri.list.push_back(temp);
			} else {
				wait2.push_back(temp);
			}
		} else {
			wait1.pushback(temp);
		}
	}

	queue1 sort


	fclose(stdin);

	//print_process(low_pri.list);

	stable_sort(low_pri.list.begin(), low_pri.list.end(), SBJ_compare);

	int fuck;

	while(1) {
		/*
		queue1.arrival_check(total);
		queue1.process();
		queue1.demote();
		*/

		while (low_pri.age_check() && arrival_check(wait1, total)) {
			print_process(low_pri.list);
			low_pri.list[0].tickets -= 1;
			low_pri.age();	
			total += 5;

			if (arrival_check(wait2, total)) {
				cout << "FUCK" << endl;
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
		}

		low_pri.promote();

		//queue1.push_back(list.promote());

		if (low_pri.list.size() == 0 && queue1.size() == 0) {
			break();
		}
	}


	freopen("output.txt", "w", stdin);

	fclose(stdout);	

	return 0;
}
