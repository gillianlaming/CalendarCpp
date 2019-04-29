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
#include "utilityfunctions.h"

#include <iostream>
#include <string>
#include <map>

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
	//TOFO:FIX DATE OF RECURRING EVENTS
	shared_ptr <DisplayableComponent> day =getComponentByDate(cal, when, "day"); //USE THIS to call getComponentbyDate
	CalendarComponent *a = dynamic_cast<CalendarComponent*>(cal.get());
	
	shared_ptr <DisplayableComponent> year1 = cal->getChild(when.tm_year - a->dateInfo.tm_year); //index of the year of the event
	shared_ptr <DisplayableComponent> month1 = year1->getChild(when.tm_mon); //index of the month of the event
	shared_ptr <DisplayableComponent> day1 = month1->getChild(when.tm_mday); //index of the day of the event
	//DisplayableDay(when, day1).dateInfo;
	
	//TODO: fully pack the struct tm
	tm time = currentCalendar->dateInfo;
	//print out when
	DisplayableDay newTimed = DisplayableDay(when, day1); //this is wrong, but it is a fully packed struct tm so it recurrs properly
	tm newTime = newTimed.dateInfo;
	for (int i = 0; i < recurrFor; ++i) {
		int index = i* recurrEvery;
		tm newTime1 = addDays(newTime, index); //is this correct
		//cout << "Date of struct tm after passing thru " << newTime.tm_mon + 1 << "/" << newTime.tm_mday << "/" << newTime.tm_year << endl;
		shared_ptr <DisplayableComponent> newEvent = make_shared<DisplayableEvent>(newTime1, cal, name); //make a new displayable event
		newEvent->display();
		//DisplayableEvent(newTime, newEvent).name = name;
		day->addComponent(newEvent); //add the event to the correct day
		currentCalendar-> myEvents.insert(pair<string, shared_ptr<DisplayableComponent>>(name, newEvent)); //add to multimap
	
	}
	if (recurrEvery == 0 && recurrFor == 0) { //in the case of a onetime event
		shared_ptr <DisplayableComponent> newEvent = make_shared<DisplayableEvent>(when, cal, name);
		//DisplayableEvent(when, newEvent).name = name;
		newEvent->display();
		day->addComponent(newEvent); //add the event to the correct day
		currentCalendar->myEvents.insert(pair<string, shared_ptr<DisplayableComponent>>(name, newEvent));//add to multimap
		
	}
	return make_shared<DisplayableEvent>(when, cal, name); //do we need to return the new event thing we made
}

//warning not all paths return. What should we return if improper so it doesn't break
shared_ptr<DisplayableComponent> FullCalendarBuilder::getComponentByDate(shared_ptr<DisplayableComponent> cal, tm d, string granularity) {
	
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	CalendarComponent *a = dynamic_cast<CalendarComponent*>(cal.get());

	shared_ptr <DisplayableComponent> year = cal->getChild(d.tm_year - a->dateInfo.tm_year); //index of the year of the event
	if (year == NULL) {
	cout << "Year doesn't exist in this cal, sry dude" << endl;
	return nullptr; //return null pointer so code does break later
	}
	shared_ptr <DisplayableComponent> month = year->getChild(d.tm_mon ); //index of the month of the event
	if (month == NULL) {
		cout << "Month doesn't exist in this cal, sry dude" << endl;
		return nullptr; //return null pointer so code does break later
	}
	shared_ptr <DisplayableComponent> day = month->getChild(d.tm_mday ); //index of the day of the event
	

	
	if (day == NULL) {
		cout << "Day doesn't exist in this cal, sry dude" << endl;
		return nullptr; //return null pointer so code does break later
	}

	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

	if (granularity == "day") {
		return day;
	}
	if (granularity == "month") {
		//shared_ptr<DisplayableComponent> a = buildMonth(d, month);
		//a->display();
		return month;
		
	}
	if (granularity == "year") {
		//shared_ptr<DisplayableComponent> a = buildYear(d, year);
		//a->display();
		return year;
	}
	return nullptr; //hopefully this will fix warning from up top

	
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