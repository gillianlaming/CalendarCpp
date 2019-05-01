#include "stdafx.h"
#include "CalendarInterface.h"
#include "FullCalendarBuilder.h"
#include "ToDoListBuilder.h"
#include "CalendarComponent.h"
#include "DisplayableTask.h"
#include "ToDoList.h"
#include "DisplayableComponent.h"
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
		todo->depth = 9;
	}
}

void ToDoInterface::run() {
	while (1) { 	// run until the user quits
		currentDisplay->display(depth);
		cout << endl; //make this ish more readable
		vector<shared_ptr<DisplayableComponent>> kids = currentDisplay->children;
		size_t numKids = kids.size();

		cout << "add task: add" << endl << "mark a task as complete: complete" << endl << "quit: q" << endl;

		string in;
		cin >> in;
		if (in == "add") {
			bool goodInput = true;
			while (goodInput) {
				cout << "enter task in the format deadline date, time, name in the format:mm/dd/yyyy,hh:mm,name" << endl;
				string line;
				cin >> line;
				istringstream iss(line);
				string name;int month = 0;int day = 0;int year = 0;int hour = 0;char comma;char backslash;char colon;int minute = 0;
				if (iss >> month >> backslash >> day >> backslash >> year >> comma >> hour >> colon >> minute >> comma >> name) {
					//month = month - 1; //shift month over by 1 bc indexes run from 0-11, not 1-12
						addTask(name, month, day, year, hour, minute);
					goodInput = false;
				}
				else {
					cout << "Incorrect input. Please note that you cannot include spaces in your input line" << endl;
				}
			}



		}
		else if (in == "complete") {
			cout << "enter the name of the task you would like to complete" << endl;
			string line;
			cin >> line;
			istringstream iss(line);
			string name;
			if (iss >> name) {
				completeTask(name);
			}
		}
		else if (in == "q") {
			break;
		}
	}
}

	void ToDoInterface::addTask(string name, int& month, int& day, int& year, int& hour, int& minute) {
		tm time;
		time.tm_hour = hour;
		time.tm_min = minute;
		time.tm_mday = day;
		time.tm_mon = month;
		time.tm_year = year;
		if (time.tm_year < 2019) {
			cout << "Task must be during or after 2019, not added" << endl;
		}
		else {
			builder->buildTasks(todo, name, time, false);
			//todo->myTasks.insert(pair<string, shared_ptr<DisplayableEvent>>(name, newTask)); //add to multimap
			cout << "task added" << endl;
		}
	}

	void ToDoInterface::completeTask(string name) {
		ToDoList* t1 = dynamic_cast<ToDoList*>(currentDisplay.get());
		//shared_ptr<DisplayableComponent> rent = t1->getParent().lock();
		vector < shared_ptr<DisplayableComponent>>  a = t1->children;
		int index = 0;
		bool exists = false;
		for (int i = 0; i < a.size(); ++i) {
			Task* t2 = dynamic_cast<Task*>(a[i].get());
			if (t2->name ==name) {
				exists = true;
				t2->completed = true;
			}
		}
		if (exists == false) {
			cout << "Task by that name not found" << endl;
		}
		
	}

