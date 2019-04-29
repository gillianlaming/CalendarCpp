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
	DisplayableEvent(std::tm now, std::shared_ptr<DisplayableComponent> cal, string name); // does this need more params?
	virtual void display(int depth) override;
	//virtual shared_ptr<DisplayableComponent> setName(string a);
	void setName(char *a);
	std::string name;
	std::tm when; //contains date/time of the event

protected: //unclear if i need this part
	
	
	
	unsigned int recurrEvery;
	unsigned int recurrFor;

};

