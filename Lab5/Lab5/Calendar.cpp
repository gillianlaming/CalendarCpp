#include "stdafx.h"
#include "Calendar.h"
#include "DisplayableYear.h"
#include <iostream>

using namespace std;

// Calendar
Calendar::Calendar(string n, size_t y) : CalendarComponent(tm(), nullptr), name(n), yearsToHold(y) { // just initialize with a default tm for now.
	time_t now = time(0); // get the current time
	tm now_tm;
	localtime_s(&now_tm, &now); // create a struct tm(now_tm) from the current time
	currentDate = now_tm;    // set Calendar's date and time to now
	dateInfo = now_tm; // setup dateInfo to represent January 1st of the current year, start time of the calendar
	dateInfo.tm_sec = 0;
	dateInfo.tm_min = 0;
	dateInfo.tm_hour = 0;
	dateInfo.tm_mday = 1;
	dateInfo.tm_mon = 0;
	// calculate and set day of the week to that of January 1st of the current year. Very sloppy, I know...
	dateInfo.tm_wday = (now_tm.tm_wday + CalendarComponent::DAYSINAWEEK - (now_tm.tm_yday % CalendarComponent::DAYSINAWEEK)) % CalendarComponent::DAYSINAWEEK;
	dateInfo.tm_yday = 0;
	dateInfo.tm_isdst = 0;
	// intialize calendar to hold __ years
	for (size_t i = 0; i < yearsToHold; ++i) {
		children.push_back(nullptr);
	}
}

void Calendar::display(int depth) {
	cout << "Calendar: " << name << endl;

	for (size_t i = 0; i < children.size(); ++i) { // forward request to all children
		if (children[i] != nullptr) {
			cout << "index: " << i;
			children[i]->display(depth);
		}
	}
	//TODO: fix display to do years initially with indices with ability to zoom in on year, then month etc.


}

//NS
/*
 void Calendar::display2(int state) {
	 //full cal initial - list years w indices
	 if (state == 4) {
		 cout << "Calendar: " << name << endl;

	}
	 //year
	 else if (state == 3) {
		 //from DisplayableYear.cpp
		 cout << "\tYear " << dateInfo.tm_year + CalendarComponent::BASEYEAR << ":" << endl;
		 for (size_t i = 0; i < children.size(); ++i) { // forward request to all children
			 if (children[i] != nullptr) {
				 children[i]->display();
			 }
		 }
	}
	 //month
	 else if (state == 2) {
		 //from DisplayableMonth.cpp
		 cout << "\t\t" << name << ":" << endl;
		 for (size_t i = 0; i < children.size(); ++i) {
			 if (children[i] != nullptr) { // forward request to all children
				 children[i]->display();
			 }
		 }
	 }
	 //day
	 else if (state == 1) {

		 //from DisplayableDay.cpp
		 cout << "\t\t\t" << daysoftheweek[dateInfo.tm_wday] << " ";
		 cout << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR << endl;
		 //add to this to display events 
		 //int i = children.size();

		 for (unsigned int i = 0; i < children.size(); ++i) {
			 children[i]->display();
		 }
	 }
	 //event
	 else {

		 //from DisplayableEvent.cpp
		 int yr = dateInfo.tm_year + 1900;
		 int mon = dateInfo.tm_mon + 1;
		 cout << name << " " << "date: " << mon << "/" << dateInfo.tm_mday << "/" << yr << " start time: " << dateInfo.tm_hour << ":" << dateInfo.tm_min << endl;

	 }

}
*/

 //NS end

shared_ptr<DisplayableComponent> Calendar::addComponent(std::shared_ptr<DisplayableComponent> comp) {
	DisplayableYear* y = dynamic_cast<DisplayableYear *>(comp.get());
	if (y == nullptr) { // if the cast fails, return nullptr
		return nullptr;
	}
	unsigned int calendarYear = CalendarComponent::BASEYEAR + dateInfo.tm_year;
	unsigned int yearAdding = CalendarComponent::BASEYEAR + y->dateInfo.tm_year;
	int index = yearAdding - calendarYear; // which child?
	if (index >= 0 && index < children.size() && children[index] == nullptr) {
		children[index] = comp;
		return comp;
	}
	else {
		return nullptr;
	}
}