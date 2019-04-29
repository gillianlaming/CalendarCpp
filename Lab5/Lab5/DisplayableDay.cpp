#include "stdafx.h"
#include "DisplayableDay.h"
#include <iostream>
#include <algorithm>

using namespace std;

DisplayableDay::DisplayableDay(std::tm d, std::shared_ptr<DisplayableComponent> p) : CalendarComponent(d, p) { }



bool DisplayableDay::sortHelper(shared_ptr<DisplayableEvent> e1, shared_ptr<DisplayableEvent> e2) {

	if (e1->when.tm_hour < e2->when.tm_hour) {
		return true;
	}
	else if (e1->when.tm_hour == e2->when.tm_hour) {
		if (e1->when.tm_min < e2->when.tm_min) {
			return true;
		}

	}
	
		return false;
	
}



void DisplayableDay::display() {
	cout << "\t\t\t" << daysoftheweek[dateInfo.tm_wday] << " ";
	cout << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR << endl;
	//add to this to display events 
	//int i = children.size();
	sort(children.begin(), children.end(), DisplayableDay::sortHelper);
	for (unsigned int i = 0; i < children.size(); ++i) {
		//USE SORTING Algorthm
		//look at studio 9
		//TODO
		
	
		
	}


}
