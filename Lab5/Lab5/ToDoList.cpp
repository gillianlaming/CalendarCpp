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

/*
bool operator<(shared_ptr<DisplayableComponent> t1, shared_ptr<DisplayableComponent> t2) {
	Task *task1 = dynamic_cast<Task*>(t1.get());
	Task *task2 = dynamic_cast<Task*>(t2.get());
	if (task1->deadline.tm_year < task2->deadline.tm_year) {
		return true;
	}
	else if (task1->deadline.tm_year == task2->deadline.tm_year) {
		if (task1->deadline.tm_mon < task2->deadline.tm_mon) {
			return true;
		}
		else if (task1->deadline.tm_mon == task2->deadline.tm_mon) {
			if (task1->deadline.tm_mday < task2->deadline.tm_mday) {
				return true;
			}
			else if (task1->deadline.tm_mday == task2->deadline.tm_mday) {
				if (task1->deadline.tm_hour < task2->deadline.tm_hour) {
					return true;
				}
				else if (task1->deadline.tm_hour == task2->deadline.tm_hour) {
					if (task1->deadline.tm_min < task2->deadline.tm_min) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

*/
