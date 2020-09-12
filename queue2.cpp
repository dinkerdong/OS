#include "queue2.h"

bool queue2::age_check(int total) {	
	bool check = false;

	for (int i = 0; i < list.size(); i++) {
		if (list[i].age == 100) {
			check = true;
			list[i].age = 0;
			list[i].priority++;
			if (list[i].priority == 3) {
				list[i].promote_time = total;
				prom.push_back(list[i]);
				list.erase(list.begin() + i);
			}
		}
	}

	return check;
}

void queue2::age() {
	for (int i = 0; i < list.size(); i++) {
		if (i != 0) {
			list[i].age += 5;
		}

		if (list[i].proc == 1 && i != 0) {
			list[i].wait += 5;
		}
	}
}

std::vector<process> queue2::promote() {
	return prom;
}

