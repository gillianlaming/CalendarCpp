#include "stdafx.h"
#include "ToDoList.h"
#include "DisplayableComponent.h"
#include <iostream>
#include <string>
using namespace std;


//why isn't this working?

ToDoList* ToDoList::tdlist = 0;

ToDoList::ToDoList(string name, std::shared_ptr<DisplayableComponent> p) : DisplayableComponent(p) {
	ToDoList::name = name;
	

}

void ToDoList::display(int depth) {
	cout << "ToDo List: " << name << endl;
	for (size_t i = 0; i < children.size(); ++i) { // forward request to all children
		int depth = 9;
		if (children[i] != nullptr) {
			//cout << "index: " << i;
			children[i]->display(depth);
		}
	}
	
}


std::shared_ptr<DisplayableComponent> ToDoList::addComponent(std::shared_ptr<DisplayableComponent> apple) {
	children.push_back(apple);
	return apple;
}


ToDoList* ToDoList::getInstance() {
	if (ToDoList::tdlist == nullptr) {
		ToDoList::tdlist = new ToDoList;
	}
	return ToDoList::tdlist;
}

