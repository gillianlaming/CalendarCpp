#pragma once
#include "DisplayableEvent.h"
#include <algorithm>
#include <iterator>
/*
Author: Jon Shidal
Purpose: declare the DisplayableDay class. This class may be a component of a calendar. It inherits from CalendarComponent and defines pure virtual functions
declared in DisplayableComponent
*/

#include "CalendarComponent.h"
// forward declarations needed to avoid circular includes, used to declare friends only
class FullCalendarBuilder;
class CalendarInterface;
class DisplayableMonth;

class DisplayableDay : public CalendarComponent {
	friend class DisplayableMonth;
	friend FullCalendarBuilder;
	friend CalendarInterface;
	friend bool operator<(shared_ptr<DisplayableComponent> e1, shared_ptr<DisplayableComponent> e2);
public:
	// 1st argument = start date/timeof the day, 2nd argument = its parent
	DisplayableDay(std::tm, std::shared_ptr<DisplayableComponent>);
	virtual void display(int depth) override;
	void sorter();
	virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent> e);
	//void sort(iterator it, iterator it2, bool g)
	// currently a leaf class, so no need to override addComponent()
	bool sortMe(shared_ptr<DisplayableComponent> e1, shared_ptr<DisplayableComponent> e2);
};
inline
bool operator<(shared_ptr<DisplayableComponent> e1, shared_ptr<DisplayableComponent> e2);