/*
Author: Natalie Stollman and Gillian Laming
Purpose: declare the user interface for our calendar
*/
#pragma once
#include "CalendarBuilder.h"
#include "CalendarComponent.h"
#include "ToDoListBuilder.h"
#include<memory>
#include <string>

using namespace std;

class ToDoInterface {
	
	std::shared_ptr<ToDoListBuilder> builder; // builder for managing construction of the calendar
	std::shared_ptr<DisplayableComponent> currentDisplay; // which component the user is currently viewing
	std::shared_ptr<ToDoListBuilder> tdbuilder;
	std::shared_ptr<ToDoList> todo;

public:
	// constructor
	// arguments: 1 - what type of builder? 2 - how many years to hold? 
	
	ToDoInterface() {};
	ToDoInterface(std::string builderType);
	void addTask(string name, int& month, int& day, int& year, int& hour, int& minute);
	void completeTask(string name);
	void run(); // display the current view to the user and prompt for input
	int depth = 9;
};
