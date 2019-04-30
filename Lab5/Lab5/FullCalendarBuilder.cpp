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
#include "ToDoList.h"
#include "DisplayableTask.h"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

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

shared_ptr<ToDoList> FullCalendarBuilder::buildTDList() {
	ToDoList * tdl = ToDoList::getList();
	shared_ptr<ToDoList>tp;
	return tp;
}

/*
shared_ptr<DisplayableComponent> FullCalendarBuilder::buildTasks(shared_ptr<DisplayableComponent> list, tm when, std::string name) {
	//Task t = Task(when, name);
	shared_ptr<DisplayableComponent> tsk = make_shared<DisplayableComponent>>(list, when, name));
	list->myTasks.insert(pair <string, shared_ptr<DisplayableComponent>>(name, tsk));
	list->addComponent(tsk);
	return tsk;
	//SORT TASKS
}


std::shared_ptr<Task> buildTasks(std::shared_ptr<DisplayableComponent> list, std::string name, std::tm when, bool completed) {
	shared_ptr<Task> tsk = make_shared<Task>(name, list, when);
	list->myTasks.insert(pair<string, shared_ptr<Task>>(name, tsk));
	//list->addComponent(tsk);
}
*/
// you may decide to define this.
shared_ptr<DisplayableEvent> FullCalendarBuilder::buildEvent(shared_ptr<DisplayableComponent> cal, string name, tm when, int recurrEvery, int recurrFor, bool a) {
	//TOFO:FIX DATE OF RECURRING EVENTS
	
	
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
		//cout << "Date of struct tm after passing thru " << newTime.tm_mon + 1 << "/" << newTime.tm_mday << "/" << newTime.tm_year << endl;
		shared_ptr <DisplayableEvent> newEvent = make_shared<DisplayableEvent>(newTime1, cal, name); //make a new displayable event
		//newEvent->display(currentCalendar->depth);
		newEvent->parent = day;
		if (a) {
			//newEvent->calNum = "C" + currentCalendar->numCals;
			newEvent->calNum = currentCalendar->numCals;

			
			//newEvent->numberCalendars = currentCalendar->numCals;
		//	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << newEvent->calNum << endl;

		}
		day->addComponent(newEvent); //add the event to the correct day
		
		//DisplayableDay(newTime1, day).addComponent(newEvent); //this line is new: adding to the wrong date index is one too big

		sort(day->children.begin(), day->children.end());
		currentCalendar-> myEvents.insert(pair<string, shared_ptr<DisplayableEvent>>(name, newEvent)); //add to multimap
		
	
	}
	if (recurrEvery == 0 && recurrFor == 0) { //in the case of a onetime event
		
		shared_ptr <DisplayableEvent> newEvent = make_shared<DisplayableEvent>(when, cal, name);
		//DisplayableEvent(when, newEvent).name = name;
		//newEvent->display(currentCalendar->depth);
		newEvent->parent = day;
		day->addComponent(newEvent); //add the event to the correct day
		if (a) {
			//newEvent->calNum = "C" + currentCalendar->numCals;
			//int aNumber = currentCalendar->numCals;
			//string theName = "C" + std::to_string(aNumber);
			//cout << "name " << theName << "++++++++++++++++++++++++++++" << endl;
			//newEvent->calNum = theName;
			newEvent->calNum = currentCalendar->numCals;
			//newEvent->numberCalendars = currentCalendar->numCals;
		//	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << newEvent-> calNum << endl;

		}
		//DisplayableDay(when, day).addComponent(newEvent); //this line is new: adding to the wrong date index is one too big
		sort(day->children.begin(), day->children.end());
		
		currentCalendar->myEvents.insert(pair<string, shared_ptr<DisplayableEvent>>(name, newEvent));//add to multimap
		
	}
	return make_shared<DisplayableEvent>(when, cal, name); //do we need to return the new event thing we made
}
//TODO: breaks upon adding event when not at depth of 4
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
/*
bool sortMe(shared_ptr<DisplayableComponent> e1, shared_ptr<DisplayableComponent> e2) {
	DisplayableEvent *event1 = dynamic_cast<DisplayableEvent*>(e1.get());
	DisplayableEvent *event2 = dynamic_cast<DisplayableEvent*>(e2.get());
	if (event1->when.tm_hour < event2->when.tm_hour) {
		return true;
	}
	else if (event1->when.tm_hour == event2->when.tm_hour) {
		if (event1->when.tm_min < event2->when.tm_min) {
			return true;
		}
	}
	return false;
}
*/