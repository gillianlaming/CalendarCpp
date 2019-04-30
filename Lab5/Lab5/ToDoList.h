#pragma once
#include "DisplayableComponent.h"
#include "CalendarComponent.h"
#include "DisplayableTask.h"
#include "ToDoList.h"
#include <string>
#include <map>
#include <memory>

class FullCalendarBuilder;
class CalendarInterface;

using namespace std;

class ToDoList : public CalendarComponent {
friend FullCalendarBuilder;
friend CalendarInterface;
protected:
	//std::string name;
//ToDoList(string name, shared_ptr<DisplayableComponent>);
	
public:
	virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent> apple) override;
	virtual void display(int depth) override;
	ToDoList();
	static shared_ptr<ToDoList> ToDoList::getList();
//	multimap <string, shared_ptr<Task>> myTasks;
};
