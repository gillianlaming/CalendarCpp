
#include "stdafx.h"
#include "IncrementalCalendarBuilder.h"
#include "CalendarComponent.h"
#include "DisplayableDay.h"
#include "DisplayableMonth.h"
#include "DisplayableYear.h"
#include "DisplayableEvent.h"
#include "utilityfunctions.h"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

shared_ptr<Calendar> IncrementalCalendarBuilder::buildCalendar(string name, size_t years) {
	currentCalendar = make_shared<Calendar>(name, years);
	// construct each year in a recursive way, add each year as a child of the calendar
	tm y = currentCalendar->dateInfo;
	y.tm_wday = (y.tm_wday + CalendarComponent::DAYSINAYEAR ) % CalendarComponent::DAYSINAWEEK; // calculate day of the week for first day of the year
	currentCalendar->addComponent(buildYear(y, currentCalendar));
	return currentCalendar;
}

shared_ptr<DisplayableEvent> IncrementalCalendarBuilder::buildEvent(shared_ptr<DisplayableComponent> cal, string name, tm when, int recurrEvery, int recurrFor, bool a) {
	//fully pack this struct tm
	tm newTime = when;
	newTime.tm_sec = 0;   // seconds of minutes from 0 to 61
	newTime.tm_min = when.tm_min;   // minutes of hour from 0 to 59
	newTime.tm_hour = when.tm_hour;  // hours of day from 0 to 24
	newTime.tm_mday = when.tm_mday;  // day of month from 1 to 31
	newTime.tm_mon = when.tm_mon;   // month of year from 0 to 11
	newTime.tm_year = when.tm_year;  // year since 1900
	newTime.tm_wday = when.tm_wday; // days since sunday
	newTime.tm_yday = when.tm_yday;  // days since January 1st
	newTime.tm_isdst = when.tm_isdst; // hours of daylight savings time

	when.tm_mday -= 1;
	shared_ptr <DisplayableComponent> day = getComponentByDate(cal, when, "day"); //USE THIS to call getComponentbyDate
	when.tm_mday += 1; //bad fix to problem but works

	for (int i = 0; i < recurrFor; ++i) {
		int index = i* recurrEvery;
		tm newTime1 = addDays(newTime, index); //is this correct
		shared_ptr <DisplayableEvent> newEvent = make_shared<DisplayableEvent>(newTime1, cal, name); //make a new displayable event
		newEvent->parent = day;
		if (a) {
			newEvent->calNum = currentCalendar->numCals;
		}
		day->addComponent(newEvent); //add the event to the correct day
		sort(day->children.begin(), day->children.end());
		currentCalendar->myEvents.insert(pair<string, shared_ptr<DisplayableEvent>>(name, newEvent)); //add to multimap

	}
	if (recurrEvery == 0 && recurrFor == 0) { //in the case of a onetime event

		shared_ptr <DisplayableEvent> newEvent = make_shared<DisplayableEvent>(when, cal, name);
		newEvent->parent = day;
		day->addComponent(newEvent); //add the event to the correct day
		if (a) {
			newEvent->calNum = currentCalendar->numCals;
		}
		sort(day->children.begin(), day->children.end());
		currentCalendar->myEvents.insert(pair<string, shared_ptr<DisplayableEvent>>(name, newEvent));//add to multimap
	}
	return make_shared<DisplayableEvent>(when, cal, name); //do we need to return the new event thing we made
}

shared_ptr<DisplayableComponent> IncrementalCalendarBuilder::getComponentByDate(shared_ptr<DisplayableComponent> cal, tm d, string granularity) {

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	CalendarComponent *a = dynamic_cast<CalendarComponent*>(cal.get());

	shared_ptr <DisplayableComponent> year = cal->getChild(d.tm_year - a->dateInfo.tm_year); //index of the year of the event
	if (year == NULL) {
		cout << "Adding new year to cal" << endl;
		int curYear = a->dateInfo.tm_year;
		int newYear = d.tm_year;
		year = addYears(curYear, newYear, currentCalendar);
		year->parent = cal;
		currentCalendar->addComponent(year);
		
	}
	shared_ptr <DisplayableComponent> month = year->getChild(d.tm_mon); //index of the month of the event
	if (month == NULL) {
		cout << "need to add month" << endl;
		month = buildMonth(d, currentCalendar);
		month->parent = year;
		currentCalendar->addComponent(month);
	}
	shared_ptr <DisplayableComponent> day = month->getChild(d.tm_mday); //index of the day of the event
	if (day == NULL) {
		cout << "Day doesn't exist in this cal, sry dude" << endl;
		day = buildDay(d, currentCalendar);
		day->parent = month;
		currentCalendar->addComponent(day);
	}
	if (granularity == "day") {
		return day;
	}
	if (granularity == "month") {
		return month;

	}
	if (granularity == "year") {
		return year;
	}
	return nullptr;
}

shared_ptr<DisplayableComponent> IncrementalCalendarBuilder::buildDay(std::tm d, std::shared_ptr<DisplayableComponent> p) {
	shared_ptr<DisplayableComponent> day = make_shared<DisplayableDay>(d, p);

	return day;
}

shared_ptr<DisplayableComponent>  IncrementalCalendarBuilder::buildMonth(std::tm d, std::shared_ptr<DisplayableComponent> p) {
	int index = d.tm_mon;
	shared_ptr<DisplayableComponent> m = make_shared<DisplayableMonth>(d, p, CalendarComponent::months[index], CalendarComponent::days[index]);
	return m;
}
shared_ptr<DisplayableComponent>  IncrementalCalendarBuilder::buildYear(std::tm d, std::shared_ptr<DisplayableComponent> p) {
	shared_ptr<DisplayableComponent> y = make_shared<DisplayableYear>(d, p, false);
	
	return y;
}
shared_ptr<DisplayableComponent> IncrementalCalendarBuilder::addYears(int curYear, int newYear, shared_ptr<Calendar> currentCalendar) {
	int diff = newYear - curYear;
	if (diff < 0) {
		cout << "Error: cannot add event in the past" << endl;
	}
	else {
		
		for (int i = 1; i < diff; ++i) {
			cout << "adding more years" << endl;
			tm y = currentCalendar->dateInfo;
			y.tm_year += i;
			y.tm_wday = (y.tm_wday + CalendarComponent::DAYSINAYEAR * i) % CalendarComponent::DAYSINAWEEK; // calculate day of the week for first day of the year
			currentCalendar->addComponent(buildYear(y, currentCalendar));
		}
		tm y = currentCalendar->dateInfo;
		y.tm_year += diff;
		y.tm_wday = (y.tm_wday + CalendarComponent::DAYSINAYEAR * diff) % CalendarComponent::DAYSINAWEEK; // calculate day of the week for first day of the year
		return currentCalendar->addComponent(buildYear(y, currentCalendar));
	}

	return nullptr;
}
