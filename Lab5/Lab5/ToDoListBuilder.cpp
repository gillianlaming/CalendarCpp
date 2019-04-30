#include "stdafx.h"
#include "ToDoList.h"
#include "ToDoListBuilder.h"
using namespace std;

std::shared_ptr<ToDoList> ToDoListBuilder::buildToDoList() {
	currenttodo = make_shared<ToDoList>();
	return currenttodo;
}

std::shared_ptr<DisplayableComponent> ToDoListBuilder::buildTasks(std::shared_ptr<DisplayableComponent> list, std::string name, std::tm when, bool completed) {
	tm newTime = when;
	shared_ptr<ToDoList> todo = currenttodo;
	shared_ptr <Task> newTask = make_shared<Task>(name, list, when, completed);
	//newTask->parent = todo;
	todo->addComponent(newTask);
	//sort

	return make_shared<Task>(name, list, when, completed);
}
