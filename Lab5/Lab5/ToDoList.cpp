#include "stdafx.h"
#include "ToDoList.h"
#include "DisplayableTask.h"
#include "DisplayableComponent.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;


ToDoList::ToDoList() : CalendarComponent() {
}

void ToDoList::display(int depth) {
	cout << "ToDo List: " << endl;
	for (size_t i = 0; i < children.size(); ++i) { // forward request to all children
		int depth = 9;
		if (children[i] != nullptr) {
			children[i]->display(depth);
		}
	}
	
}


std::shared_ptr<DisplayableComponent> ToDoList::addComponent(std::shared_ptr<DisplayableComponent> apple) {
	children.push_back(apple);
	return apple;
}

