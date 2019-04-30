#include "stdafx.h"
#include "DisplayableTask.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;


Task::Task(string name, shared_ptr<DisplayableComponent> ptr, tm deadline) : DisplayableComponent(ptr) {
	Task::name = name;
	Task::deadline = deadline;
	Task::completed = false;

}

void Task::display(int depth) {
	cout << name << endl;
}
