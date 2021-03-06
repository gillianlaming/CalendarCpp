#include "stdafx.h"
#include "DisplayableMonth.h"
#include "DisplayableDay.h"
#include <iostream>
#include <iomanip>

using namespace std;

DisplayableMonth::DisplayableMonth(std::tm d, std::shared_ptr<DisplayableComponent> p, string monthname, unsigned int numdays) : CalendarComponent(d, p), name(monthname), numberOfDays(numdays) {
	// initialize children vector, one spot for each day
	for (size_t i = 0; i < numberOfDays; ++i) {
		children.push_back(nullptr);
	}
}
//use setw here
void DisplayableMonth::display(int depth) {
	cout << "\t\t" << name  << endl;
		if (depth == 2) {
		cout << "Sunday     " << "Monday     " << "Tuesday    " << "Wednesday  " << "Thursday   " << "Friday     " << "Saturday   " << endl;
			//add space for first week depending on what day of the week the first of the month is
			for (int i = 0; i < 7; ++i) {
				if (i < dateInfo.tm_wday) {
					cout << "           ";
				}
			}
		
			for (int i = 0; i < children.size(); ++i) {
					children[i]->display(depth);
			}
	}
		if (depth == 3) { //year

			for (int i = 0; i < children.size(); ++i) {
				children[i]->display(depth);
			}
		}
		
		
}
	
	


shared_ptr<DisplayableComponent> DisplayableMonth::addComponent(shared_ptr<DisplayableComponent> comp) {
	// try to dynamically cast comp to a pointer to a DisplayableDay, will fail if the DisplayableComponent is not a day
	DisplayableDay* d = dynamic_cast<DisplayableDay *>(comp.get()); // can only cast regular pointers, not shared_ptrs
	if (d == nullptr) { // the cast failed
		return nullptr;
	}
	// otherwise, add the day to the correct location
	int dayOfMonth = d->dateInfo.tm_mday - 1;
	if (children[dayOfMonth] == nullptr) { // day does not already exist
		children[dayOfMonth] = comp;
		return comp;
	}
	else {  // day already exist, return existing day
		return children[dayOfMonth];
	}
}