#include "stdafx.h"
#include "ToDoInterface.h"
#include <string>
#include <iostream>
#include <string>
#include<iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <iterator>

using namespace std;

//ToDoList::ToDoList(string name) {
//	ToDoList::name = name;
//}

shared_ptr<DisplayableComponent> ToDoList::addComponent(std::shared_ptr<DisplayableComponent> comp) {
	cout << "what would you like to name your task?" << endl;
	string line;
	cin >> line;
	//dynamically allocate new task w given name
	shared_ptr<DisplayableComponent> newTask = NULL; //fix 
	children.push_back(newTask);
	return newTask;
}

	//FROM CALINTERFACE
	/*
//cout << "zoom out: out" << endl << "zoom in: in" << endl << "add event: add" << endl << "search for an event by name: search" << endl << "jump to a specific day: jump" << endl << "Save calendar to a file: save " << endl << "Resore calendar from a file: restore" << endl << "Switch to Calendar: calendar" << endl << "quit : q" << endl;

	bool goodInput = true;
	while (goodInput) {
		cout << "Enter the deadline and the name of the task in the form: mm/dd/yyyy,hh:mm,name" << endl;
		string line;
		cin >> line;
		istringstream iss(line);
		string name;int month = 0;int day = 0;int year = 0;int hour = 0;char comma;char backslash;char colon;int minute = 0;
		if (iss >> month >> backslash >> day >> backslash >> year >> comma >> hour >> colon >> minute >> comma >> name) {
			//month = month - 1; //shift month over by 1 bc indexes run from 0-11, not 1-12
			addEvent(name, month, day, year, hour, minute);
			goodInput = false;
		}
		else {
			cout << "Incorrect input. Please note that you cannot include spaces in your input line" << endl;
		}
	}
		//END FROM CAL INTERFACE
*/

void ToDoList::display() {
	cout << ToDoList::name << endl;
	for (size_t i = 0; i < children.size(); ++i) { // forward request to all children
		if (children[i] != nullptr) {
		//	children[i]->display();
		}
	}
}