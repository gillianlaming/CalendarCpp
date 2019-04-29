#pragma once
#include "CalendarBuilder.h"
#include "CalendarComponent.h"
#include<memory>
#include <string>

using namespace std;
class ToDoList : public DisplayableComponent {
protected:
	string name;

public:
	ToDoList(string name);
	virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent> apple);
	virtual void display();
};