#include "stdafx.h"
#include "ToDoList.h"
#include "DisplayableTask.h"
#include "DisplayableComponent.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;




//ToDoList* ToDoList::tdlist = 0;

ToDoList::ToDoList() : CalendarComponent() {
	cout << "todo construct" << endl;
	//multimap <string, shared_ptr<Task>> myTasks;

}

void ToDoList::display(int depth) {
	cout << "ToDo List: " << endl;
	//cout << "tddisplay" << endl;
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


