#include "ticket.h"
#include <iostream>
using namespace std;

process::process()
{

}

void process::print_process()
{
	cout << id;
	cout << " " << arrival;
	cout << " " << priority;
	cout << " " << age;
	cout << " " << tickets << endl;
}
