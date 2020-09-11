#include "queue2.h"

bool queue2::age_check() {	
	bool check = true;

	for (int i = 0; i < list.size(); i++) {
		if (list[i].age == 100) {
			check = false;
			list[i].age = 0;
			prom.push_back(list[i]);
			list.erase(list.begin() + i);
		}
	}

	return check;
}

void queue2::age() {
	for (int i = 0; i < list.size(); i++) {
		list[i].age += 5;
	}
}

std::vector<process> queue2::promote() {
	return prom;
}
