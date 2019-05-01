#include "stdafx.h"
#include "ToDoList.h"
#include "ToDoListBuilder.h"
#include <map>
#include <algorithm>
using namespace std;

std::shared_ptr<ToDoList> ToDoListBuilder::buildToDoList() {
	currenttodo = make_shared<ToDoList>();
	return currenttodo;
	
}




std::shared_ptr<DisplayableComponent> ToDoListBuilder::buildTasks(std::shared_ptr<DisplayableComponent> list, std::string name, std::tm when, bool completed) {
	tm newTime = when;

	CalendarComponent *a = dynamic_cast<CalendarComponent*>(currenttodo.get());
	
	
	shared_ptr <Task> newTask = make_shared<Task>(name, list, when, completed);
	newTask->parent = currenttodo;
	currenttodo->addComponent(newTask);
	//Sort here
	sort(currenttodo->children.begin(), currenttodo->children.end());
	//set the parent of the task as the todo list
	currenttodo->myTasks.insert(pair<string, shared_ptr<CalendarComponent>>(name, newTask)); //add to multimap
	return newTask;
	
}
