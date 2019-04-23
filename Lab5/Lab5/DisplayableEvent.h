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

protected:
	string name;
	int month;
	int day;
	int year;

};

