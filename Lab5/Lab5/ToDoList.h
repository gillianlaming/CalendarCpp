#pragma once
#include "DisplayableComponent.h"
#include <string>
#include <memory>

using namespace std;
class ToDoBuilder;
class ToDoInterface;

class ToDoList : public DisplayableComponent {
friend ToDoBuilder;
friend ToDoInterface;
protected:
	std::string name;


public:
	ToDoList(string name);
	virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent> apple);
	virtual void display(int depth);
};
