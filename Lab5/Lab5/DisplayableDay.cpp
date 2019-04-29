#include "stdafx.h"
#include "DisplayableDay.h"
#include <iostream>
#include <algorithm>

using namespace std;

DisplayableDay::DisplayableDay(std::tm d, std::shared_ptr<DisplayableComponent> p) : CalendarComponent(d, p) { }



shared_ptr<DisplayableEvent> & operator<(shared_ptr<DisplayableEvent> e1, shared_ptr<DisplayableEvent> e2) {
	if (e1->when.tm_hour < e2->when.tm_hour) {
		return e2;
	}
	else if (e1->when.tm_hour == e2->when.tm_hour) {
		if (e1->when.tm_min < e2->when.tm_min) {
			return e2;
		}
	}
	return e1;
}

std::shared_ptr<DisplayableComponent> DisplayableDay::addComponent(std::shared_ptr<DisplayableComponent> e) {
	
	children.push_back(e);
	//not sure if we need to do more here
	return e;
}


void DisplayableDay::display(int depth) {
	cout << "\t\t\t" << daysoftheweek[dateInfo.tm_wday] << " ";
	cout << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR << endl;
	//add to this to display events 
	int i = children.size();
	for (unsigned int i = 0; i < children.size(); ++i) {
		children[i]->display(depth);
	}
	
	


}
