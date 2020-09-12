#ifndef QUEUE2_H
#define QUEUE2_H

#include "ticket.h"
#include <vector>

class queue2
{			
	public:
		std::vector<process> list;
		std::vector<process> prom;
		bool age_check(int total);	
		void age();
		std::vector<process> promote();	
};

#endif//QUEUE2_H
