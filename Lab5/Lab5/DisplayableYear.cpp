#include "stdafx.h"
#include "DisplayableYear.h"
#include <iostream>
#include "DisplayableMonth.h"

using namespace std;

DisplayableYear::DisplayableYear(std::tm d, std::shared_ptr<DisplayableComponent> p, bool l) : CalendarComponent(d, p), leap(l) {
	for (size_t i = 0; i < CalendarComponent::MONTHS; ++i) {
		children.push_back(nullptr);
	}
}
//display events under corresponding months
void DisplayableYear::display(int depth) {
	cout << "\tYear " << dateInfo.tm_year + CalendarComponent::BASEYEAR << endl;
	if (depth == 3) { //year
		for (size_t i = 0; i < children.size(); ++i) { // forward request to all children
			if (children[i] != nullptr) {
				cout << i;
				//children[i]->children;
				children[i]->display(depth);
			}
			else {
				cout << i << setw(20);
				cout <<CalendarComponent::months[i] << endl;
				
			}
			

		}
	}
	
	
}

shared_ptr<DisplayableComponent> DisplayableYear::addComponent(shared_ptr<DisplayableComponent> comp) {
	// try to dynamically cast comp to a pointer to a DisplayableMonth
	DisplayableMonth * m = dynamic_cast<DisplayableMonth *>(comp.get());
	if (m == nullptr) { // if the cast fails, return nullptr
		return nullptr;
	}
	// otherwise, add the month to the correct location
	int monthOfYear = m->dateInfo.tm_mon;
	if (children[monthOfYear] == nullptr) { // month does not already exist
		children[monthOfYear] = comp;
		return comp;
	}
	else {  // month already exist, return existing month
		return children[monthOfYear];
	}
}
