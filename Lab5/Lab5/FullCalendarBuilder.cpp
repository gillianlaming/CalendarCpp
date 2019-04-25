/*
Author: Jon Shidal
Purpose: Define full calendar builder class, responsible for building and managing the structure of the calendar
*/
#include "stdafx.h"
#include "FullCalendarBuilder.h"
#include "CalendarComponent.h"
#include "DisplayableDay.h"
#include "DisplayableMonth.h"
#include "DisplayableYear.h"
#include "DisplayableEvent.h"

#include <iostream>

using namespace std;

shared_ptr<Calendar> FullCalendarBuilder::buildCalendar(string name, size_t years) {
	currentCalendar = make_shared<Calendar>(name, years);
	// construct each year in a recursive way, add each year as a child of the calendar
	for (unsigned int i = 0; i < years; ++i) {
		tm y = currentCalendar->dateInfo;
		y.tm_year += i;
		y.tm_wday = (y.tm_wday + CalendarComponent::DAYSINAYEAR * i) % CalendarComponent::DAYSINAWEEK; // calculate day of the week for first day of the year
		currentCalendar->addComponent(buildYear(y, currentCalendar));
	}
	return currentCalendar;
}

// you may decide to define this.
shared_ptr<DisplayableComponent> FullCalendarBuilder::buildEvent(shared_ptr<DisplayableComponent> cal, string name, tm when, int recurrEvery, int recurrFor) {

	//for the recurrence we need to make different event objects
	CalendarComponent *a = dynamic_cast<CalendarComponent*>(cal.get());
	shared_ptr <DisplayableComponent> year = cal->getChild(when.tm_year - a->dateInfo.tm_year); //index of the year of the event
	cout << "year index " << year << endl;
	if (year == NULL) {
		cout << "invalid entry 1" << endl;
		//RE PROMPT
	}
	shared_ptr <DisplayableComponent> month = year->getChild(when.tm_mon /*- a->dateInfo.tm_mon*/); //index of the month of the event
	cout << "month index " << month << endl;
	if (month == NULL) {
		cout << "invalid entry 2" << endl;
		//throw execption
	}
	shared_ptr <DisplayableComponent> day = month->getChild(when.tm_mday /*- a->dateInfo.tm_mday*/); //index of the day of the event
	cout << "day index " << day << endl;
	if (day == NULL) {
		cout << "invalid entry 3" << endl;
		//throw execption
	}
	
	for (int i = 0; i < recurrFor; ++i) {
		int index = i* recurrEvery;
		//TODO: need to make sure we are handling case when youre at the end of the month/end of the year so it carries over
		tm newTime = when;
		//shidal wrote a function to add a constant to a day but i dont think i want to deal w this rn
		newTime.tm_mday += recurrEvery; //unclear how to do this so it carries over into next month

		shared_ptr <DisplayableComponent> newEvent = make_shared<DisplayableEvent>(newTime, cal);//make a new displayable event
		//newEvent.name = name;
		day->addComponent(newEvent); //add the event to the correct day
		
	}
	return make_shared<DisplayableEvent>(when, cal);; //do we need to return the new event thing we made
}

// you may decide to define this.
shared_ptr<DisplayableComponent> FullCalendarBuilder::getComponentByDate(shared_ptr<DisplayableComponent> cal, tm d, string granularity) {
	//wut
	return nullptr;
}

shared_ptr<DisplayableComponent> FullCalendarBuilder::buildDay(std::tm d, std::shared_ptr<DisplayableComponent> p) {
	shared_ptr<DisplayableComponent> day = make_shared<DisplayableDay>(d, p);

	return day;
}

shared_ptr<DisplayableComponent> FullCalendarBuilder::buildMonth(std::tm d, std::shared_ptr<DisplayableComponent> p) {
	int index = d.tm_mon;
	shared_ptr<DisplayableComponent> m = make_shared<DisplayableMonth>(d, p, CalendarComponent::months[index], CalendarComponent::days[index]);
	for (int i = 0; i < CalendarComponent::days[index]; ++i) { // for each day in the month
		m->addComponent(buildDay(d, m)); // construct day and add as a child of the month
		++(d.tm_mday); // increment day of the month
		d.tm_wday = (d.tm_wday + 1) % CalendarComponent::DAYSINAWEEK; // increment weekday, reset to 0 if needed
	}
	return m;
}
shared_ptr<DisplayableComponent> FullCalendarBuilder::buildYear(std::tm d, std::shared_ptr<DisplayableComponent> p) {
	shared_ptr<DisplayableComponent> y = make_shared<DisplayableYear>(d,p,false);
	// construct each month and add it as a child of the year
	for (unsigned int i = 0; i < CalendarComponent::MONTHS; ++i) {
		d.tm_mon = i;
		y->addComponent(buildMonth(d, y));
		// set week day of first day of the next month
		d.tm_wday = (d.tm_wday + CalendarComponent::days[i]) % CalendarComponent::DAYSINAWEEK; 
	}
	return y;
}