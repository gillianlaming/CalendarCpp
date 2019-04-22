#include "stdafx.h"
#include "CalendarInterface.h"
#include "FullCalendarBuilder.h"
#include<iostream>
#include <istream>
#include <sstream>
#include <fstream>


using namespace std;

CalendarInterface::CalendarInterface(std::string builderType, std::string calendarName, size_t years) : builder(nullptr),cal(nullptr),currentDisplay(nullptr) {
	if (builderType == "full") {
		builder = make_shared<FullCalendarBuilder>();
		cal = builder->buildCalendar(calendarName, years);
		currentDisplay = cal;
	}
}

void CalendarInterface::run() {
	// run until the user quits
	while (1) {
		// display the current display of the calendar
		//currentDisplay->display(); //change thisc
		// display options to the user and respond to user input accordingly
		cout << "zoom out: out, zoom in: in, add event: add, quit: q" << endl;
		string in;
		cin >> in;
		if (in == "in") {
			if (currentDisplay->children.size() > 0) {
				cout << "index? (0-" << currentDisplay->children.size() - 1 << ")" << endl;
				int index = 0;
				cin >> index;
				zoomIn(index);
			}
			else {
				cout << "Nothing to zoom in on" << endl;
			}
		}
		else if (in == "out") {
			zoomOut();
		}
		else if (in == "add") {
			bool goodInput = true;
			while (goodInput) {
				cout << "Event Name, mm/dd/yyyy, hh:mm" << endl;
				string line;
				cin >> line;
				istringstream iss(line);
				string name;
				int month = 0;
				int day = 0;
				int year = 0;
				int hour = 0;
				char comma;
				char backslash;
				char colon;
				int minute = 0;
				//if (iss >> name >> comma >> month >> backslash >> day >> backslash >> year >> comma >> hour >> colon >> minute) {
				if (iss >> name >> month) {
					cout << name << month;
					cout << "yeet" << endl;
					addEvent(name, month, day, year, hour, minute);
					goodInput = false;
				}
			}
		}
			else if (in == "q") {
				break;
			}
			else {
				cout << ";-)" << endl;
			}
		}
	}


void CalendarInterface::zoomIn(unsigned int index) {
	shared_ptr<DisplayableComponent> temp = currentDisplay->getChild(index);
	// if the child exists, update the current display to the child. Otherwise, the current view remains the same
	if (temp != nullptr) {
		currentDisplay = temp;
	}
}

void CalendarInterface::zoomOut() {
    // if the current display has a parent, update current display to the parent
	if (currentDisplay->getParent().lock() != nullptr) {
		// create a shared_ptr from a weak_ptr, contributing to the objects reference count
		currentDisplay = currentDisplay->getParent().lock();
	}
}
void CalendarInterface::addEvent(string name,  int& month,  int& day,  int& year,  int& hour,  int& minute ) {
	cout << "yeeted" << endl;
}