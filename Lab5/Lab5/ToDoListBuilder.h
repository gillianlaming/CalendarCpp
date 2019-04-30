#pragma once
#include<memory>
#include "ToDoList.h"
using namespace std;

class ToDoListBuilder {
public:
	virtual std::shared_ptr<ToDoList> buildToDoList();
	ToDoListBuilder() {};
	//virtual std::shared_ptr<DisplayableComponent> buildTasks(std::shared_ptr<DisplayableComponent> list, std::string name, std::tm when, bool completed);


protected:
	shared_ptr<ToDoList> currenttodo;

};
