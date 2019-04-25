#include "stdafx.h"
#include "DisplayableEvent.h"
#include <iostream>

using namespace std;

DisplayableEvent::DisplayableEvent(std::tm now, std::shared_ptr<DisplayableComponent> cal) : CalendarComponent(now, cal) {} // does this need more params?

void DisplayableEvent::display() {
	//change this it is copy and pasted from DisplayableDay
	cout << "\t\t\t" << daysoftheweek[dateInfo.tm_wday] << " ";
	cout << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR << endl;
}