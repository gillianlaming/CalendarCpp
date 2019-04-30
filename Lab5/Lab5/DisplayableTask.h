#pragma once
#include "DisplayableComponent.h"
#include "ToDoList.h"

using namespace std;
class ToDoList;
class Task : public DisplayableComponent {
	friend class ToDoList;
protected:
	std::string name;
public:
	virtual void display(int depth);
	Task(string name);
};
