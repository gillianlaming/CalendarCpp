/*
Author: Jon Shidal
Purpose: Define Calendar component classes.
*/

#include "stdafx.h"
#include "calendarcomponents.h"
#include<iostream>
#include<string>

using namespace std;

// from <ctime>
//struct tm {
//	int tm_sec;   // seconds of minutes from 0 to 61
//	int tm_min;   // minutes of hour from 0 to 59
//	int tm_hour;  // hours of day from 0 to 24
//	int tm_mday;  // day of month from 1 to 31
//	int tm_mon;   // month of year from 0 to 11
//	int tm_year;  // year since 1900
//	int tm_wday;  // days since sunday
//	int tm_yday;  // days since January 1st
//	int tm_isdst; // hours of daylight savings time
//}

// static class variables
const std::vector<string> CalendarComponent::daysoftheweek = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
const std::vector<string> CalendarComponent::months = { "January", "February", "March", "April", "May", "June", "July", "August","September", "October", "November","December" };
const std::vector<int> CalendarComponent::days = { 31,28,31,30,31,30,31,31,30,31,30,31 };
const int CalendarComponent::DAYSINAWEEK = 7;
const int CalendarComponent::MONTHS = 12;
const int CalendarComponent::BASEYEAR = 1900;
const int CalendarComponent::DAYSINAYEAR = 365;

// CalendarComponent
CalendarComponent::CalendarComponent(std::tm d, std::shared_ptr<DisplayableComponent> p) : DisplayableComponent(p), dateInfo(d){}

// Day
DisplayableDay::DisplayableDay(std::tm d, std::shared_ptr<DisplayableComponent> p) : CalendarComponent(d, p){ } 

void DisplayableDay::display() {
	cout << "\t\t\t" << daysoftheweek[dateInfo.tm_wday] << " ";
	cout << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR << endl;
}

// Month
DisplayableMonth::DisplayableMonth(std::tm d, std::shared_ptr<DisplayableComponent> p, string monthname, unsigned int numdays) : CalendarComponent(d, p), name(monthname), numberOfDays(numdays) {
	// initialize children vector, one spot for each day
	for (size_t i = 0; i < numberOfDays; ++i) {
		children.push_back(nullptr);
	}
}

void DisplayableMonth::display() {
	cout << "\t\t" << name << ":" << endl;
	for (size_t i = 0; i < children.size(); ++i) {
		if (children[i] != nullptr) { // forward request to all children
			children[i]->display();
		}
	}
}

shared_ptr<DisplayableComponent> DisplayableMonth::addComponent(shared_ptr<DisplayableComponent> comp) {
	// try to dynamically cast comp to a pointer to a DisplayableDay, will fail if the DisplayableComponent is not a day
	DisplayableDay* d = dynamic_cast<DisplayableDay *>(comp.get()); // can only cast regular pointers, not shared_ptrs
	if (d == nullptr) { // the cast failed
		return nullptr;
	}
	// otherwise, add the day to the correct location
	int dayOfMonth = d->dateInfo.tm_mday - 1;
	if (children[dayOfMonth] == nullptr) { // day does not already exist
		children[dayOfMonth] = comp;
		return comp;
	}
	else {  // day already exist, return existing day
		return children[dayOfMonth];
	}
}

// Year
DisplayableYear::DisplayableYear(std::tm d, std::shared_ptr<DisplayableComponent> p, bool l) : CalendarComponent(d, p), leap(l) {
	for (size_t i = 0; i < CalendarComponent::MONTHS; ++i) { 
		children.push_back(nullptr);
	}
}

void DisplayableYear::display() {
	cout << "\tYear " << dateInfo.tm_year + CalendarComponent::BASEYEAR << ":" << endl;
	for (size_t i = 0; i < children.size(); ++i) { // forward request to all children
		if (children[i] != nullptr) {
			children[i]->display();
		}
	}
}

shared_ptr<DisplayableComponent> DisplayableYear::addComponent(shared_ptr<DisplayableComponent> comp) {
	// try to dynamically cast comp to a pointer to a DisplayableMonth
	DisplayableMonth * m = dynamic_cast<DisplayableMonth *>(comp.get());
	if (m == nullptr) { // if the cast fails, return nullptr
		return nullptr;
	}
	// otherwise, add the month to the correct location
	int monthOfYear = m->dateInfo.tm_mon;
	if (children[monthOfYear] == nullptr) { // month does not already exist
		children[monthOfYear] = comp;
		return comp;
	}
	else {  // month already exist, return existing month
		return children[monthOfYear];
	}
}

// Calendar
Calendar::Calendar(string n, size_t y) : CalendarComponent(tm(), nullptr), name(n), yearsToHold(y) { // just initialize with a default tm for now.
	time_t now = time(0); // get the current time
	tm now_tm;
	gmtime_s(&now_tm, &now); // create a struct tm(now_tm) from the current time
	currentDate = now_tm;    // set Calendar's date and time to now
	dateInfo = now_tm; // setup dateInfo to represent January 1st of the current year, start time of the calendar
	dateInfo.tm_sec = 0;
	dateInfo.tm_min = 0;
	dateInfo.tm_hour = 0;
	dateInfo.tm_mday = 1;
	dateInfo.tm_mon = 0;
	// calculate and set day of the week to that of January 1st, 2018. Very sloppy, I know
	dateInfo.tm_wday = (now_tm.tm_wday + CalendarComponent::DAYSINAWEEK - (now_tm.tm_yday % CalendarComponent::DAYSINAWEEK)) % CalendarComponent::DAYSINAWEEK; 
	dateInfo.tm_yday = 0;
	dateInfo.tm_isdst = 0;
	// intialize calendar to hold __ years
	for (size_t i = 0; i < yearsToHold; ++i) {
		children.push_back(nullptr);
	}
}

void Calendar::display() {
	cout << "Calendar: " << name << endl;
	for (size_t i = 0; i < children.size(); ++i) { // forward request to all children
		if (children[i] != nullptr) {
			children[i]->display();
		}
	}
}

shared_ptr<DisplayableComponent> Calendar::addComponent(std::shared_ptr<DisplayableComponent> comp) {
	DisplayableYear* y = dynamic_cast<DisplayableYear *>(comp.get());
	if (y == nullptr) { // if the cast fails, return nullptr
		return nullptr;
	}
	int calendarYear = CalendarComponent::BASEYEAR + dateInfo.tm_year;
	int yearAdding = CalendarComponent::BASEYEAR + y->dateInfo.tm_year;
	int index = yearAdding - calendarYear; // which child?
	if (index >= 0 && index < children.size() && children[index] == nullptr) {
		children[index] = comp;
		return comp;
	}
	else {
		return nullptr;
	}
}