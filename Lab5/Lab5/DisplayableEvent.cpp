#include "stdafx.h"
#include "DisplayableEvent.h"
#include <iostream>
#include <string>

using namespace std;

DisplayableEvent::DisplayableEvent(std::tm now, std::shared_ptr<DisplayableComponent> cal) : CalendarComponent(now, cal) {} // does this need more params?

void DisplayableEvent::display() {

	cout << name << " " << when.tm_hour << endl;
}

//shared_ptr<DisplayableComponent> DisplayableEvent::setName(string a) {}
void DisplayableEvent::setName(char *a) {
	string nameA(a);

	DisplayableEvent::name = nameA; //set this equal to the name
}
