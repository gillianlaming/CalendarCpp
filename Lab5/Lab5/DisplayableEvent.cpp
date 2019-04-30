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
	if (depth == 3) {
		if (when.tm_min == 0) {
			cout << mon << "/" << when.tm_mday << "/" << yr << " " << when.tm_hour << ":" << "00" << " " << name << endl;
		}
		else {
			cout << mon << "/" << when.tm_mday << "/" << yr << " " << when.tm_hour << ":" << when.tm_min << " " << name << endl;
		}
	}
	if (depth == 1) {
		if (when.tm_min == 0) {
			cout << when.tm_hour << ":" << "00" << " " << name << endl;
		}
		else {
			cout << when.tm_hour << ":" << when.tm_min << " " << name << endl;
		}
	}
	if (depth == 0) {
		
		if (when.tm_min == 0) {
			cout  << mon << "/" << when.tm_mday << "/" << yr << endl;
			cout<< when.tm_hour << ":" << "00" << " " << name << endl;

		}
		else {
			cout  << mon<< "/" << when.tm_mday << "/" << yr << endl;
			cout << when.tm_hour << ":" << when.tm_min << " " << name << endl;
		}
	}

	
}

//shared_ptr<DisplayableComponent> DisplayableEvent::setName(string a) {}
void DisplayableEvent::setName(char *a) {
	string nameA(a);

	DisplayableEvent::name = nameA; //set this equal to the name
}

bool DisplayableEvent::operator<(const DisplayableEvent & e1) {
	cout << "---------------------------------------------------------------" << endl;
	//DisplayableEvent *event1 = dynamic_cast<DisplayableEvent*>(e1.get());
	//DisplayableEvent *event2 = dynamic_cast<DisplayableEvent*>(e2.get());
	if (e1.when.tm_hour < dateInfo.tm_hour) {
		return false;
	}
	else if (e1.when.tm_hour == dateInfo.tm_hour) {
		if (e1.when.tm_min < dateInfo.tm_min) {
			return false;
		}
	}
	return true;
}

