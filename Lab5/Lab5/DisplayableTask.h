#pragma once
#include "DisplayableComponent.h"
#include "CalendarComponent.h"
#include "ToDoListBuilder.h"
#include "ToDoList.h"
#include <string>
#include <map>


class calendarInterface;
class FullCalendarBuilder;

using namespace std;

class Task :public CalendarComponent {
	friend CalendarInterface;
	friend ToDoList;
	//friend class DisplayableComponenet;
	friend class ToDoListBuilder;
	
	
public:
	virtual void display(int depth) override;
	Task(string name, shared_ptr<DisplayableComponent> ptr, tm deadline, bool completed);
	std::string name;
	std::tm deadline;
	bool completed;

protected:
	std::weak_ptr<DisplayableComponent> parent; // weak_ptr to avoid cycles, does not contribute to reference count

	
};
