#pragma once
#include "CalendarBuilder.h"

// Concrete builder class
// builds a full calendar, all at once
class IncrementalCalendarBuilder : public CalendarBuilder {
public:
	virtual std::shared_ptr<DisplayableEvent> buildEvent(std::shared_ptr<DisplayableComponent> cal, std::string name, std::tm when, int recurrEvery, int recurrFor, bool a) override;
	virtual std::shared_ptr<DisplayableComponent> getComponentByDate(std::shared_ptr<DisplayableComponent> cal, std::tm d, std::string granularity) override;
	virtual std::shared_ptr<Calendar> buildCalendar(std::string name, size_t years) override;
	IncrementalCalendarBuilder() {};
	
protected:
	virtual std::shared_ptr<DisplayableComponent> buildYear(std::tm d, std::shared_ptr<DisplayableComponent> p) override;
	virtual std::shared_ptr<DisplayableComponent> buildDay(std::tm d, std::shared_ptr<DisplayableComponent> p) override;
	virtual std::shared_ptr<DisplayableComponent> buildMonth(std::tm d, std::shared_ptr<DisplayableComponent> p) override;
};

