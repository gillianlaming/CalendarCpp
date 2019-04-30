#pragma once
#include "DisplayableComponent.h"
#include "ToDoList.h"

using namespace std;
class calendarInterface;
class FullCalendarBuilder;
class calendarBuilder;

class Task : public DisplayableComponent {
	friend class ToDoList;
	friend class displayableComponenet;
	friend class calendarBuilder;
	friend class calendarInterface;

	
public:
	virtual void display(int depth) override;
	Task(string name, shared_ptr<DisplayableComponent> p);
	std::string name;
	std::tm deadline;
	bool completed;
};
