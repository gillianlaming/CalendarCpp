#include "stdafx.h"
#include "DisplayableDay.h"
#include "DisplayableTask.h"
#include <iostream>
#include <algorithm>

using namespace std;

DisplayableDay::DisplayableDay(std::tm d, std::shared_ptr<DisplayableComponent> p) : CalendarComponent(d, p) { }


//sorts for both events, and tasks on todo list. checks which dynamic cast is possible, which tells us if we're in a todolist or day
//compare 2 at a time
bool operator<(shared_ptr<DisplayableComponent> e1, shared_ptr<DisplayableComponent> e2) {
	//if events on day
	if (DisplayableEvent *event1 = dynamic_cast<DisplayableEvent*>(e1.get())) {
		DisplayableEvent *event2 = dynamic_cast<DisplayableEvent*>(e2.get());
		if (event1->when.tm_hour < event2->when.tm_hour) {
			return true;
		}
		else if (event1->when.tm_hour == event2->when.tm_hour) {
			if (event1->when.tm_min < event2->when.tm_min) {
				return true;
			}
		}
		return false;
	}
	//else if tasks in todo list
	else if (Task *task1 = dynamic_cast<Task*>(e1.get())) {
		Task *task2 = dynamic_cast<Task*>(e2.get());
		if (task1->deadline.tm_year < task2->deadline.tm_year) {
			return true;
		}
		else if (task1->deadline.tm_year == task2->deadline.tm_year) {
			if (task1->deadline.tm_mon < task2->deadline.tm_mon) {
				return true;
			}
			else if (task1->deadline.tm_mon == task2->deadline.tm_mon) {
				if (task1->deadline.tm_mday < task2->deadline.tm_mday) {
					return true;
				}
				else if (task1->deadline.tm_mday == task2->deadline.tm_mday) {
					if (task1->deadline.tm_hour < task2->deadline.tm_hour) {
						return true;
					}
					else if (task1->deadline.tm_hour == task2->deadline.tm_hour) {
						if (task1->deadline.tm_min < task2->deadline.tm_min) {
							return true;
						}
					}
				}
			}
		}
		return false;
	}
	return false;
}

std::shared_ptr<DisplayableComponent> DisplayableDay::addComponent(std::shared_ptr<DisplayableComponent> e) {

	children.push_back(e);
	return e;
}


void DisplayableDay::display(int depth) {
	//year
	if (depth == 3) {
		for (int i = 0; i < children.size(); ++i) {
			cout << '\t';
			children[i]->display(depth);
		}
	}
	else if (depth == 1) {//day
		cout << daysoftheweek[dateInfo.tm_wday] << " ";
		cout << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR << endl;
		for (int i = 0; i < children.size(); ++i) {

			children[i]->display(depth);

		}
	}
	else if (depth == 0) {//event
		cout << daysoftheweek[dateInfo.tm_wday];
		
	}
	else {
		int spacing = 11;
		string stars = "";
		for (unsigned int i = 0; i < children.size(); ++i) {
			stars = stars + "*";
			
		}
		string daze = std::to_string(dateInfo.tm_mday) + stars;
		cout << setw(spacing) << left  << daze;
		if (dateInfo.tm_wday  == 6) {
			cout << endl << endl;
		}
		
	}

	
	
	
	




}

