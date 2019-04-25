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
		currentDisplay->display(); //change thisc
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
				//cout << "Event Name,mm/dd/yyyy,hh:mm" << endl;
			    cout << "mm/dd/yyyy,hh:mm,name" << endl;
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
				if (iss >> month >> backslash >> day >> backslash >> year >> comma >> hour >> colon >> minute >> comma >> name) {
					month = month - 1; //shift month over by 1 bc indexes run from 0-11, not 1-12
					addEvent(name, month, day, year, hour, minute);
					goodInput = false;
				}
				else {
					cout << "Incorrect input. Please note that you cannot include spaces. :) " << endl;
				}
			}
		}
			else if (in == "q") {
				break;
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
	
	//need to figure out if it is a recurring event
	bool runLoop = true;
	while (runLoop) {
		cout << "Is this a recurring event? (Y or N)" << endl;
		string line;
		cin >> line;
		//istringstream isss(line);
		if (line == "Y") {
			//do something
			runLoop = false;
		}
		if (line == "N") {
			//do something
			runLoop = false;
		}
		else {
			cout << "Bad input. Please enter Y for a reccurring event and N for a one time event." << endl;
		}
	}
	//need to make new struct tm object
	tm time;
	time.tm_hour = hour;
	time.tm_min = minute;
	time.tm_mday = day;
	time.tm_mon = month;
	time.tm_year = year;

	//shared_ptr<DisplayableComponent> cal, string name, tm when, int recurrEvery, int recurrFor
	builder->buildEvent(currentDisplay, name, time, 0, 0);

	//initialize tm HERE and properly
	//look for system function to add days and stuff, if u cant find, need to do manually

	//support reccurring events, "recur every __ days, recur __ times"
	//need to make a new event object
	//need to call buildEvent
	
}