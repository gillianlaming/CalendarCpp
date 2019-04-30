/*
Author: Jon Shidal
Purpose: declare the user interface for our calendar
*/
#pragma once
#include "CalendarBuilder.h"
#include "CalendarComponent.h"
#include<memory>
#include <string>

using namespace std;

class CalendarInterface {
	std::shared_ptr<Calendar> cal; // the calendar
	std::shared_ptr<CalendarBuilder> builder; // builder for managing construction of the calendar
	std::shared_ptr<DisplayableComponent> currentDisplay; // which component the user is currently viewing
public:
	// constructor
	// arguments: 1 - what type of builder? 2 - how many years to hold? 
	CalendarInterface(std::string builderType, std::string calendarName, size_t years);
	CalendarInterface() {};
	int numCals = 0;
	// calendar traversal functions
	void zoomIn(unsigned int index); // zoom in on a child of the current_display
	void zoomOut(); // zoom out to the parent of the current_display
	void addEvent(string name, int& month,  int& day,  int& year,  int& hour,  int& minute ); //this is just a helper function dw
	void addEvent2(string name, int& month, int& day, int& year, int& hour, int& minute);
	void addEvent3(string name, int& month, int& day, int& year, int& hour, int& minute);
	void run(); // display the current view to the user and prompt for input
	bool mergeMeBb();
	//int depth;
};