#include "stdafx.h"
#include "DisplayableTask.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;


Task::Task(string name, shared_ptr<DisplayableComponent> ptr, tm deadline, bool completed) : DisplayableComponent(ptr) {
	Task::name = name;
	Task::deadline = deadline;
	Task::completed = false;

}

void Task::display(int depth) {
	if (completed == false) {
		cout << name <<" TODO" << endl;
	}
	else {
		cout << name << " COMPLETED" << endl;
	}
}
