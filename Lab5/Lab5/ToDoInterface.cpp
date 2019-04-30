#include "stdafx.h"
#include "CalendarInterface.h"
#include "FullCalendarBuilder.h"
#include "ToDoListBuilder.h"
#include "CalendarComponent.h"
#include "DisplayableYear.h"
#include "Calendar.h"
#include "ToDoListBuilder.h"
#include "ToDoInterface.h"
#include <string>
#include<iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <map>
#include <fstream>
#include <iterator>
#include <algorithm>


using namespace std;


ToDoInterface::ToDoInterface(std::string builderType) : builder(nullptr), todo(nullptr), currentDisplay(nullptr) {
	if (builderType == "todo") {
		builder = make_shared<ToDoListBuilder>();
		todo = builder->buildToDoList();
		currentDisplay = todo;
		//todo->depth = 9;

	}
}

void ToDoInterface::run() {
	while (1) { 	// run until the user quits
		//currentDisplay->display(todo->depth);
		cout << endl; //make this ish more readable
	//	vector<shared_ptr<DisplayableComponent>> kids = currentDisplay->children;
	//	int numKids = kids.size();

	

	}
}

void addTask(string name, int& month, int& day, int& year, int& hour, int& minute) {

	//need to make new struct tm object
	tm time;
	time.tm_hour = hour;
	time.tm_min = minute;
	time.tm_mday = day;
	time.tm_mon = month;
	time.tm_year = year;
	//builder->buildTasks(todo, name, time, false);
	cout << "task added" << endl;

}
