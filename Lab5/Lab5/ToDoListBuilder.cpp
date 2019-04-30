#include "stdafx.h"
#include "ToDoList.h"
#include "ToDoListBuilder.h"
#include <map>
using namespace std;

std::shared_ptr<ToDoList> ToDoListBuilder::buildToDoList() {
	currenttodo = make_shared<ToDoList>();
	return currenttodo;
	
}




std::shared_ptr<DisplayableComponent> ToDoListBuilder::buildTasks(std::shared_ptr<DisplayableComponent> list, std::string name, std::tm when, bool completed) {
	tm newTime = when;
	//TODO: i think we're gonna need to fully pack this struct tm

	//shared_ptr<ToDoList> todo = currenttodo; //this line is the issue
	CalendarComponent *a = dynamic_cast<CalendarComponent*>(currenttodo.get());
	
	
	shared_ptr <Task> newTask = make_shared<Task>(name, list, when, completed);
	newTask->parent = currenttodo;
	currenttodo->addComponent(newTask);
	//set the parent of the task as the todo list
	//shared_ptr<DisplayableComponent> parent = newTask->parent.lock();
	currenttodo->myTasks.insert(pair<string, shared_ptr<CalendarComponent>>(name, newTask)); //add to multimap
	//sort
	return newTask;
	
}
