#include "stdafx.h"
#include "DisplayableEvent.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

DisplayableEvent::DisplayableEvent(std::tm now, std::shared_ptr<DisplayableComponent> cal, string name) : CalendarComponent(now, cal), name(name), when(now) {} // does this need more params?

void DisplayableEvent::display(int depth) {
	int yr = when.tm_year + 1900;
	int mon = when.tm_mon + 1;
	//vector<string> daysOfTheWeek = { "Sunday" , "Monday" , "Tuesday" , "Wednesday" , "Thursday" , "Friday" , "Saturday" };
	//int index = when.tm_wday;
	//cout << daysOfTheWeek[index] << '/t' << mon << "/" << when.tm_mday << "/" << yr << endl; --> THIS IS ALREADY BEING PRINTED (good news)
	//cout << when.tm_hour << ":" << when.tm_min << '/t' << name << endl;
	
	cout << name << " " << "date: " << mon << "/" << when.tm_mday << "/" << yr << " start time: " << when.tm_hour << ":" << when.tm_min << endl;
}

//shared_ptr<DisplayableComponent> DisplayableEvent::setName(string a) {}
void DisplayableEvent::setName(char *a) {
	string nameA(a);

	DisplayableEvent::name = nameA; //set this equal to the name
}


