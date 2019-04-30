#include "stdafx.h"
#include "DisplayableTask.h"
#include <iostream>
#include <string>

using namespace std;


Task::Task(string name, std::shared_ptr<DisplayableComponent> p) : DisplayableComponent(p) {
	Task::name = name;
}

void Task::display(int depth) {
	cout << name << endl;
}
