#pragma once
#include <string>
#include <map>

#include "CalendarComponent.h"
//#include "DisplayableEvent.h"
// forward declarations needed to avoid circular includes, used to declare friends only
class FullCalendarBuilder;
class CalendarInterface;
using namespace std;
class Calendar : public CalendarComponent {
	// friends
	friend FullCalendarBuilder;
	friend CalendarInterface;
	//friend DisplayableEvent;
protected:
	std::string name;
	size_t yearsToHold;
	std::tm currentDate; // current date and time
						 // dateInfo is the start date and time

						 // Calendar contains years, so override accordingly
	virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>) override;
public:
	// arguments: name of the calendar, length of the calendar in years
	Calendar(std::string n, size_t y);
	// inherited methods
	virtual void display(int depth) override;
	// void display2(int state);
	multimap <string,shared_ptr<DisplayableComponent>> myEvents;
	multimap <string, shared_ptr<DisplayableComponent>>::iterator it;



};