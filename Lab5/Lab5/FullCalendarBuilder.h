#pragma once
/*
Author: Jon Shidal
Purpose: Declare FullCalendarBuilder, a concrete class that derives from CalendarBuilder,
which builds all components of the calendar at once.
*/
//#include "DisplayableTask.h"
#include "CalendarBuilder.h"

// Concrete builder class
// builds a full calendar, all at once
class FullCalendarBuilder : public CalendarBuilder {
public:
	virtual std::shared_ptr<DisplayableEvent> buildEvent(std::shared_ptr<DisplayableComponent> cal, std::string name, std::tm when, int recurrEvery, int recurrFor, bool a) override;
	virtual std::shared_ptr<DisplayableComponent> getComponentByDate(std::shared_ptr<DisplayableComponent> cal, std::tm d, std::string granularity) override;
	virtual std::shared_ptr<Calendar> buildCalendar(std::string name, size_t years) override;
	FullCalendarBuilder() {};
	virtual std::shared_ptr<ToDoList> buildTDList();
	//virtual std::shared_ptr<DisplayableComponent> buildTasks(std::shared_ptr<DisplayableComponent> list, tm when, std::string name);


protected:
	virtual std::shared_ptr<DisplayableComponent> buildYear(std::tm d, std::shared_ptr<DisplayableComponent> p) override;
	virtual std::shared_ptr<DisplayableComponent> buildDay(std::tm d, std::shared_ptr<DisplayableComponent> p) override;
	virtual std::shared_ptr<DisplayableComponent> buildMonth(std::tm d, std::shared_ptr<DisplayableComponent> p) override;
};
