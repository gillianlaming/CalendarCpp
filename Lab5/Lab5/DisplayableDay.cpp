#include "stdafx.h"
#include "DisplayableDay.h"
#include <iostream>
#include <algorithm>

using namespace std;

DisplayableDay::DisplayableDay(std::tm d, std::shared_ptr<DisplayableComponent> p) : CalendarComponent(d, p) { }



DisplayableEvent * operator<(shared_ptr<DisplayableComponent> e1, shared_ptr<DisplayableComponent> e2) {
	cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
	DisplayableEvent *event1 = dynamic_cast<DisplayableEvent*>(e1.get());
	DisplayableEvent *event2 = dynamic_cast<DisplayableEvent*>(e2.get());
	if (event1->when.tm_hour < event2->when.tm_hour) {
		return event1;
	}
	else if (event1->when.tm_hour == event2->when.tm_hour) {
		if (event1->when.tm_min < event2->when.tm_min) {
			return event1;
		}
	}
	return event2;
}

std::shared_ptr<DisplayableComponent> DisplayableDay::addComponent(std::shared_ptr<DisplayableComponent> e) {
	
	children.push_back(e);
	//not sure if we need to do more here
	return e;
}


void DisplayableDay::display(int depth) {
	//sort(children.begin(), children.end());
	if (depth == 3) {
		for (int i = 0; i < children.size(); ++i) {
			cout << '\t';
			children[i]->display(depth);

		}
	}
	else if (depth == 1) {
		cout << daysoftheweek[dateInfo.tm_wday] << " ";
		cout << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR << endl;
		for (int i = 0; i < children.size(); ++i) {

			children[i]->display(depth);

		}
	}
	else if (depth == 0) {
		cout << "hi";
		cout << daysoftheweek[dateInfo.tm_wday];
		
	}
	else {
		int spacing = 11;
		//cout <<left << setw(11) << dateInfo.tm_mday;
		for (unsigned int i = 0; i < children.size(); ++i) {
			cout << "*";
			spacing--;
			//cout << i << '\t';
			//children[i]->display(depth);
		}
		cout << left << setw(spacing) << dateInfo.tm_mday;
		if (dateInfo.tm_wday  == 6) {
			cout << endl << endl;
		}
		
	}
	//add to this to display events 
	//int i = children.size();
	
	
	
	




}

