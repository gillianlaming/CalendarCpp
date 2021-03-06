#pragma once
/*
author: by Gillian and Natalie
purpose: support functionality for adding events to the calendar
*/

#include "CalendarComponent.h"
#include <string>
#include <memory>
class FullCalendarBuilder;
class CalendarInterface;
class DisplayableMonth;

using namespace std;

class DisplayableEvent : public CalendarComponent {
	friend class DisplayableDay;
	friend class DisplayableComponent;
	friend FullCalendarBuilder;
	friend CalendarInterface;
public:
	DisplayableEvent(std::tm now, std::shared_ptr<DisplayableComponent> cal, string name); 
	virtual void display(int depth) override;
	std::string name;
	string calNum = "";
	std::tm when; //contains date/time of the event

protected: //unclear if i need this part
	
	
	
	unsigned int recurrEvery;
	unsigned int recurrFor;

};

