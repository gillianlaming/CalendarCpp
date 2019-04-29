#include "stdafx.h"
#include "DisplayableEvent.h"
#include <iostream>
#include <string>

using namespace std;

DisplayableEvent::DisplayableEvent(std::tm now, std::shared_ptr<DisplayableComponent> cal, string name) : CalendarComponent(now, cal), name(name), when(now) {} // does this need more params?

void DisplayableEvent::display() {
	int yr = when.tm_year + 1900;
	int mon = when.tm_mon + 1;
	cout << name << " " << "date: " << mon << "/" << when.tm_mday << "/" << yr << " start time: " << when.tm_hour << ":" << when.tm_min << endl;
}

//shared_ptr<DisplayableComponent> DisplayableEvent::setName(string a) {}
void DisplayableEvent::setName(char *a) {
	string nameA(a);

	DisplayableEvent::name = nameA; //set this equal to the name
}
