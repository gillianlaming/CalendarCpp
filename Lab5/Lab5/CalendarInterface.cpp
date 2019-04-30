#include "stdafx.h"
#include "CalendarInterface.h"
#include "FullCalendarBuilder.h"
#include "CalendarComponent.h"
#include "DisplayableYear.h"
#include "Calendar.h"
#include <string>
#include<iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <iterator>


using namespace std;

CalendarInterface::CalendarInterface(std::string builderType, std::string calendarName, size_t years) : builder(nullptr),cal(nullptr),currentDisplay(nullptr) {
	if (builderType == "full") {
		builder = make_shared<FullCalendarBuilder>();
		cal = builder->buildCalendar(calendarName, years);
		currentDisplay = cal;
		cal->depth = 4;
		cal->numCals = 0;
		
		
	}
}

void CalendarInterface::run() {
	while (1) { 	// run until the user quits
		cout << "depth " << cal->depth << endl;
		currentDisplay->display(cal->depth); //UNCOMMENT THIS LATER i just commented out so full cal doesn't print every time
		int yr = CalendarComponent::BASEYEAR;
		//this part needs to be before all the other options are displayed so we dont have to wrap another cin (i think this should work but it may not)----------------------------------------------------------------------------
		cout << endl; //make this ish more readable
		vector<shared_ptr<DisplayableComponent>> kids = currentDisplay->children;
		int numKids = kids.size();
		
		//TODO: change this. right now it displays edit & delete on days which dont have any events.
		//if (currentDisplay->children.size() == 0) { //current display is an event
		if (cal->depth == 0){ //hopefully now this will only display if it is an event
			cout << "edit this event: edit" << endl << "delete this event: delete " << endl;
		}
		//-----------------------------------------------------------------------------------------------------------------

		// display options to the user and respond to user input accordingly
		cout << "zoom out: out" << endl << "zoom in: in" << endl << "add event: add" << endl << "search for an event by name: search" << endl << "jump to a specific day: jump" << endl << "Save calendar to a file: save " << endl << "Resore calendar from a file: restore" << endl <<"Merge a calendar with another calendar: merge" << endl <<"Switch to ToDo List: todo" << endl << "quit : q" << endl;
		string in;
		cin >> in;
		if (in == "in") {
			if (currentDisplay->children.size() > 0) {
				cout << "index? (0-" << currentDisplay->children.size() - 1 << ")" << endl;
				int index = 0;
				cin >> index;
				zoomIn(index);
				
			}
			else {
				cout << "Nothing to zoom in on" << endl;
			}
		}
		else if (in == "out") {
			zoomOut();
			
		}
		else if (in == "add") {
			bool goodInput = true;
			while (goodInput) {
			    cout << "mm/dd/yyyy,hh:mm,name" << endl;
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
			
		}
		else if (in == "merge") {
			cout << "What is the name of the calendar you would like to merge with: ";
			cal->numCals = cal->numCals + 1;
			//cout << "the number of calendars is changing " << cal->numCals << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			
			if (mergeMeBb()) {
				cout << "mergemebb worked" << endl;
			}
			else {
				cal->numCals = cal->numCals - 1;
				//cout << "Error merging calendars." << endl;
			}
		}
		else if (in == "search") {//searching for an event by name
			string name;
			cout << "What is the name of the event you would like to search for: ";
			cin >> name;
			cal->it = cal->myEvents.find(name);
			if (cal->it == cal->myEvents.end()) {
				cout << "There was no event by this name in your calendar" << endl << endl;
			}
			else { //code structure from http://www.cplusplus.com/forum/general/102485/
				typedef multimap <string, shared_ptr<DisplayableEvent>> temp; 
				pair<temp::iterator, temp::iterator> range;
				range = cal->myEvents.equal_range(name); //equal_range returns pair of iterators
				int i = 0;
				vector<shared_ptr<DisplayableEvent>> sameName;
				for (temp::iterator it1 = range.first; it1 != range.second; ++it1) { //iterate across all the events with the same name
					cout << "Index " << i << ": ";
					shared_ptr<DisplayableEvent> event = it1->second;
					sameName.push_back(event);
					i++;
					event->display(cal->depth);
				}
				cout << endl;
				if (i > 1) {
					int index;
					cout << "Of the above events, which one would you like to display? Type in the index: ";
					cin >> index;
					//TODO: fix this display
					//TODO this now
					sameName[index]->display(cal->depth); //this is not the proper way to be displaying, but works for the time being.
				}
			}	
		}
		else if (in == "jump"){ //jump to a specific day
			string granularity;
			cout << "Please enter a date(mm/dd/yyyy): "  << endl;;
			//wrap date stuff
			string line;
			cin >> line;
			istringstream iss(line);
			int month = 0;int day = 0;int year = 0;char backslash;
			if (iss >> month >> backslash >> day >> backslash >> year) {
				cout << "Please enter a granularity: ";
				cin >> granularity;
				if (granularity == "day") {
					cal->depth = 1;
				}
				if (granularity == "month") {
					cal->depth = 2;
				}
				if (granularity == "year") {
					cal->depth = 3;
				}
				//need to build a struct tm
				tm time;
				time.tm_mday = day;
				time.tm_mon = month-1;
				time.tm_year = year-CalendarComponent::BASEYEAR;
				shared_ptr<DisplayableComponent> a = builder->getComponentByDate(currentDisplay, time, granularity);
				currentDisplay = a;
			}
			else {
				cout << "Bad input" << endl;
			}
			

		}
		else if (in == "save") {
			ofstream myfile;
			cout << "What would you like to name this calendar: ";
			string calName;
			cin >> calName;
			string fileName = calName + ".txt";
			myfile.open(fileName, ios::out);
			if (myfile) {
				for (std::multimap<string, shared_ptr<DisplayableEvent>>::iterator it = cal->myEvents.begin(); it != cal->myEvents.end(); ++it) {
					//string will be formatted the same way it is when user inputs event. not readable to user but ok for computer
					char backslash = '/';
					char colon = ':';
					char comma = ',';
					myfile << (*it).second->when.tm_mon << backslash << (*it).second->when.tm_mday << backslash << (*it).second->when.tm_year << comma << (*it).second->when.tm_hour << colon << (*it).second->when.tm_min << comma << (*it).second->name << endl;
				}
				myfile.close();
				cout << "Calendar succcessfully saved to " << fileName << endl << endl;
			}
		}
		else if (in == "restore") {
			cout << "What is the name of the calendar you would like to restore: ";
			string calName;
			cin >> calName;
			string fileName = calName + ".txt";
			ifstream restoreCal;
			restoreCal.open(fileName);
			string line;
			if (restoreCal.is_open()) {
				while (!restoreCal.eof()) { //while it's not the end of the file
					getline(restoreCal, line);
					istringstream iss(line);
					string name;int month = 0;int day = 0;int year = 0;int hour = 0;char comma;char backslash;char colon;int minute = 0;
					while (iss >> month >> backslash >> day >> backslash >> year >> comma >> hour >> colon >> minute >> comma >> name) { //while there are still strings to be extracted
						addEvent2(name, month, day, year, hour, minute);
					}
				}
			}
			else {
				cout << "Unable to read info from file" << endl << endl;
			}
			restoreCal.close();
		}
		//TODO: todoLIst
		else if (in == "todo") {
			cout << "todo view" << endl;
		}
		else if (in == "edit") {
			//TODO: edit an event
			DisplayableEvent* event1 = dynamic_cast<DisplayableEvent*>(currentDisplay.get());
			cout << "enter the new info for your event ";
			bool goodInput = true;
			while (goodInput) {
				cout << "mm/dd/yyyy,hh:mm,name" << endl;
				string line;
				cin >> line;
				istringstream iss(line);
				string name;int month = 0;int day = 0;int year = 0;int hour = 0;char comma;char backslash;char colon;int minute = 0;
				if (iss >> month >> backslash >> day >> backslash >> year >> comma >> hour >> colon >> minute >> comma >> name) {
					//month = month - 1; //shift month over by 1 bc indexes run from 0-11, not 1-12
					event1->when.tm_hour = hour;
					event1->when.tm_min = minute;
					event1->when.tm_mday = day;
					event1->when.tm_mon = month - 1;
					event1->when.tm_year = year - CalendarComponent::BASEYEAR;
					event1->name = name;
					goodInput = false;
				}
				else {
					cout << "Incorrect input. Please note that you cannot include spaces in your input line" << endl;
				}
			}
			
		}
		else if (in == "delete") {

			DisplayableEvent* event1 = dynamic_cast<DisplayableEvent*>(currentDisplay.get());
			shared_ptr<DisplayableComponent> rent = event1->getParent().lock();
			vector < shared_ptr<DisplayableComponent>>  a = rent->children;
			int index;
			for (int i = 0; i < a.size(); ++i) {
				DisplayableEvent* event2 = dynamic_cast<DisplayableEvent*>(a[i].get());
				if (event2->name == event1->name && event1->when.tm_mon == event2->when.tm_mon) {
					cout << "got here yay" << endl;
					index = 1;
				}
			}
			DisplayableEvent* event2 = dynamic_cast<DisplayableEvent*>(a[index].get());
			string key = event2->name;
			cal->myEvents.erase(key);
			rent->children.erase(rent->children.begin() + index);
		
		}
		else if (in == "q") {
			break;
		}
		
		
	}

}

bool CalendarInterface::mergeMeBb() {
	
	string calName;
	cin >> calName;
	string fileName = calName + ".txt";
	ifstream restoreCal;
	restoreCal.open(fileName);
	string line;
	if (restoreCal.is_open()) {
		while (!restoreCal.eof()) { //while it's not the end of the file
			getline(restoreCal, line);
			istringstream iss(line);
			string name;int month = 0;int day = 0;int year = 0;int hour = 0;char comma;char backslash;char colon;int minute = 0;
			while (iss >> month >> backslash >> day >> backslash >> year >> comma >> hour >> colon >> minute >> comma >> name) { //while there are still strings to be extracted
				addEvent3(name, month, day, year, hour, minute);
				
			}
		}
		return true;
	}
	else {
		cout << "Unable to read info from file" << endl << endl;
	}
	
	restoreCal.close();
	return false;
}

void CalendarInterface::zoomIn(unsigned int index) {
	shared_ptr<DisplayableComponent> temp = currentDisplay->getChild(index);
	// if the child exists, update the current display to the child. Otherwise, the current view remains the same
	if (temp != nullptr) {
		currentDisplay = temp;
	}
	cal->depth--;
}

void CalendarInterface::zoomOut() {
    // if the current display has a parent, update current display to the parent
	if (currentDisplay->getParent().lock() != nullptr) {
		// create a shared_ptr from a weak_ptr, contributing to the objects reference count
		currentDisplay = currentDisplay->getParent().lock();
	}
	cal->depth++;
}
void CalendarInterface::addEvent(string name,  int& month,  int& day,  int& year,  int& hour,  int& minute ) { //helper function
	int recurrFor;
	int recurrEvery;
	bool runLoop = true;
	while (runLoop) {
		cout << "Is this a recurring event? (Y or N)" << endl;
		string line;
		cin >> line;
		
		if (line == "Y") {
			cout << "Recur every how many days? " << endl;
			cin >> recurrEvery;
			cout << "Recur for how many times?" << endl;
			cin >> recurrFor;
			runLoop = false;
		}
		else if (line == "N"){
			recurrFor = 0;
			recurrEvery = 0;
			runLoop = false;
		}
		else {
			cout << "Bad input. Please enter Y for a reccurring event and N for a one time event." << endl;
		}
	}
	//need to make new struct tm object
	tm time;
	time.tm_hour = hour;
	time.tm_min = minute;
	time.tm_mday = day;
	time.tm_mon = month - 1;
	time.tm_year = year - CalendarComponent::BASEYEAR;
//	currentDisplay->display;
	builder->buildEvent(cal, name, time, recurrEvery, recurrFor, false);
	
}

//restore
void CalendarInterface::addEvent2(string name, int& month, int& day, int& year, int& hour, int& minute) {
	int recurrFor = 0;
	int recurrEvery = 0;

	
	//need to make new struct tm object
	tm time;
	time.tm_hour = hour;
	time.tm_min = minute;
	time.tm_mday = day;
	time.tm_mon = month;
	time.tm_year = year;
	builder->buildEvent(cal, name, time, recurrEvery, recurrFor, false);
}
//merge
void CalendarInterface::addEvent3(string name, int& month, int& day, int& year, int& hour, int& minute) {
	int recurrFor = 0;
	int recurrEvery = 0;
	//need to make new struct tm object
	tm time;
	time.tm_hour = hour;
	time.tm_min = minute;
	time.tm_mday = day;
	time.tm_mon = month;
	time.tm_year = year;
	shared_ptr<DisplayableEvent> mergedEvent = builder->buildEvent(cal, name, time, recurrEvery, recurrFor, true);
	//need to put this in full calendar builder
	//mergedEvent->calNum = "C" + cal->numCals;
	//mergedEvent->numberCalendars = cal->numCals;

}
