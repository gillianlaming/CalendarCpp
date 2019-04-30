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

	int yr = deadline.tm_year + 1900;
	int mon = deadline.tm_mon + 1;

	if (completed == false) {
		if (deadline.tm_min == 0) {
			cout <<name<<": " << mon<<"/"<<deadline.tm_mday<<"/"<<yr<<" "<< deadline.tm_hour << ":" << "00" << " TODO" << endl;
		}
		else {
			cout << name << ": " << mon << "/" << deadline.tm_mday << "/" << yr << " " << deadline.tm_hour << ":" << deadline.tm_min << " TODO" << endl;
		}
	
	}
	else {
		if (deadline.tm_min == 0) {
			cout << name << ": " << mon << "/" << deadline.tm_mday << "/" << yr << " " << deadline.tm_hour << ":" << "00" << " COMPLETED" << endl;
		}
		else {
			cout << name << ": " << mon << "/" << deadline.tm_mday << "/" << yr << " " << deadline.tm_hour << ":" << deadline.tm_min << " COMPLETED" << endl;
		}

	}
}
