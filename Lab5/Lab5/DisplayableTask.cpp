#include "stdafx.h"
#include "DisplayableTask.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

//constructor, task has name, deadline, and whether or not it is completed
Task::Task(string name, shared_ptr<DisplayableComponent> ptr, tm deadline, bool completed) : CalendarComponent(deadline, ptr) {
	Task::name = name;
	Task::deadline = deadline;
	Task::completed = false;

}

void Task::display(int depth) {
	//for ease of cout
	int yr = deadline.tm_year;
	int mon = deadline.tm_mon;

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
