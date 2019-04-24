#pragma once
/*
author: by Gillian and Natalie
purpose: support functionality for adding events to the calendar
*/
#include <string>
#include "CalendarComponent.h"


class FullCalendarBuilder;
class CalendarInterface;
class DisplayableMonth;

using namespace std;

class DisplayableEvent : public CalendarComponent {
public:
	void Date(); //base constructor
	//needs to support reccurrence 

protected:
	string name;
	std::tm day; //contains date/time of the event

};

