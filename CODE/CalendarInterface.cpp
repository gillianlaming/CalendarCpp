#include "stdafx.h"
#include "CalendarInterface.h"
#include<iostream>

using namespace std;

CalendarInterface::CalendarInterface(std::string builderType, size_t years) : builder(nullptr),cal(nullptr),currentDisplay(nullptr) {
	if (builderType == "full") {
		builder = make_shared<FullCalendarBuilder>();
		cal = builder->buildCalendar("test", years);
		currentDisplay = cal;
	}
}

void CalendarInterface::display() {
	currentDisplay->display();
	cout << "zoom out: out, zoom in: in, quit: q" << endl;
	string in;
	cin >> in;
	if (in == "in") {
		cout << "index? (0-" << currentDisplay->children.size() - 1 << ")" << endl;
		int index = 0;
		cin >> index;
		zoomIn(index);
	}
	else if (in == "out") {
		zoomOut();
	}
	else if (in == "q") {
		return;
	}
}

void CalendarInterface::zoomIn(unsigned int index) {
	shared_ptr<DisplayableComponent> temp = currentDisplay->getChild(index);
	if (temp != nullptr) {
		currentDisplay = temp;
	}
	display();
}
void CalendarInterface::zoomOut() {
	if (currentDisplay->getParent().lock() != nullptr) {
		currentDisplay = currentDisplay->getParent().lock();
	}
	display();
}