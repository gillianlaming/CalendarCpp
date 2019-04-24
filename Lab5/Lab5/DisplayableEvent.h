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

//using namespace std;

class DisplayableEvent : public CalendarComponent {
	friend class DisplayableDay;
	friend class DisplayableComponent;
	friend FullCalendarBuilder;
	friend CalendarInterface;
public:
	DisplayableEvent(std::tm, std::shared_ptr<DisplayableComponent>); // does this need more params?
	virtual void display() override;
	

protected: //unclear if i need this part
	std::string name;
	std::tm when; //contains date/time of the event
	unsigned int recurrEvery;
	unsigned int recurrFor;

};

