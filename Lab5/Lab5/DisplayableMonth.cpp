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

//TODO: put asterisk after days with events
void DisplayableMonth::display(int depth) {
	cout << "\t\t" << name  << endl;
		if (depth == 2) {
		cout << "Sunday     " << "Monday     " << "Tuesday    " << "Wednesday  " << "Thursday   " << "Friday     " << "Saturday   " << endl;
		//cout << "day: " << dateInfo.tm_mday << endl;
		
		/*
		for (size_t i = 0; i < children.size(); ++i) {

			if (children[i] != nullptr) { // forward request to all children
				//cout <<i<<"    ";

				cout << "wday: " << dateInfo.tm_wday << endl;
				//if (dateInfo.tm_wday == 0) {
			
				//}

				//eventually we want to delete this(?) bc we just want the number(i) not full display
				children[i]->display(depth);
				
			}
			
		}
		*/
		
		for (int i = 0; i < 7; ++i) {
			if (i < dateInfo.tm_wday) {
				//cout <<setw(11) << "";
				cout << "           ";
			}
		}
		
		for (int i = 0; i < children.size(); ++i) {
			
				children[i]->display(depth);
				
				}

			}
	//	if (depth == 3) {
			//for (int i = 0; i < children.size(); ++i) {

				//children[i]->display(depth);

			//}

	//	}
		
		

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