#pragma once
#include "DisplayableComponent.h"
#include "DisplayableTask.h"
#include "ToDoList.h"
#include <string>
#include <map>
#include <memory>

class FullCalendarBuilder;
class CalendarInterface;

using namespace std;

class ToDoList : public DisplayableComponent {
friend FullCalendarBuilder;
friend CalendarInterface;
protected:
	std::string name;

private:
	static ToDoList* tdlist;
	ToDoList() {};
	ToDoList(string name, shared_ptr<DisplayableComponent>);
	
public:
	virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent> apple) override;
	virtual void display(int depth) override;
	static ToDoList* getList();
	multimap <string, shared_ptr<DisplayableComponent>> myTasks;
};
