#pragma once
#include "DisplayableComponent.h"
#include "ToDoList.h"
#include <string>
#include <map>


class calendarInterface;
class FullCalendarBuilder;
class calendarBuilder;

using namespace std;

class Task : public DisplayableComponent {
	friend FullCalendarBuilder;
	friend calendarInterface;
	friend class ToDoList;
	friend class displayableComponenet;
	friend class calendarBuilder;
	friend class calendarInterface;
	
	
public:
	virtual void display(int depth) override;
	Task(string name, shared_ptr<DisplayableComponent> ptr, tm deadline);
	std::string name;
	std::tm deadline;
	bool completed;
	//multimap<string, shared_ptr<Task>> myTasks;
};
