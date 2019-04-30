#include "stdafx.h"
#include "ToDoList.h"
#include "DisplayableComponent.h"
#include <iostream>
#include <string>
using namespace std;


//why isn't this working?

//ToDoList::ToDoList(string name) {
//	ToDoList::name = name;
//}

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


//std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent> apple) {
	
//}