#include "stdafx.h"
#include "DisplayableEvent.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

DisplayableEvent::DisplayableEvent(std::tm now, std::shared_ptr<DisplayableComponent> cal, string name) : CalendarComponent(now, cal), name(name), when(now) {} // does this need more params?

void DisplayableEvent::display(int depth) {
	int yr = when.tm_year + 1900;
	int mon = when.tm_mon + 1;
	
	if (depth == 3) {
		if (calNum == "") {
			if (when.tm_min == 0) {
				cout << mon << "/" << when.tm_mday << "/" << yr << " " << when.tm_hour << ":" << "00" << " "  << name << endl;
			}
			else {
				cout << mon << "/" << when.tm_mday << "/" << yr << " " << when.tm_hour << ":" << when.tm_min << " "<< name << endl;
			}
		}
		else {
			if (when.tm_min == 0) {
				cout << mon << "/" << when.tm_mday << "/" << yr << " " << when.tm_hour << ":" << "00" << " " << calNum << "::" << name << endl;
			}
			else {
				cout << mon << "/" << when.tm_mday << "/" << yr << " " << when.tm_hour << ":" << when.tm_min << " " << calNum << "::" << name << endl;
			}
		}
		
	}
	if (depth == 1) {
		if (calNum == "") {
			if (when.tm_min == 0) {
				cout << when.tm_hour << ":" << "00" << " "  << name << endl;
			}
			else {
				cout << when.tm_hour << ":" << when.tm_min << " " << name << endl;
			}
		}
		else {
			if (when.tm_min == 0) {
				cout << when.tm_hour << ":" << "00" << " " << calNum << "::" << name << endl;
			}
			else {
				cout << when.tm_hour << ":" << when.tm_min << " " << calNum << "::" << name << endl;
			}
		}
		
	}
	if (depth == 0) {
		if (calNum == "") {
			if (when.tm_min == 0) {
				cout << mon << "/" << when.tm_mday << "/" << yr << endl;
				cout << when.tm_hour << ":" << "00" << " " << name << endl;
			}
			else {
				cout << mon << "/" << when.tm_mday << "/" << yr << endl;
				cout << when.tm_hour << ":" << when.tm_min << " " << name << endl;
			}
		}
		else {
			if (when.tm_min == 0) {
				cout << mon << "/" << when.tm_mday << "/" << yr << endl;
				cout << when.tm_hour << ":" << "00" << " " << calNum << "::" << name << endl;
			}
			else {
				cout << mon << "/" << when.tm_mday << "/" << yr << endl;
				cout << when.tm_hour << ":" << when.tm_min << " " << calNum << "::" << name << endl;
			}
		}
	}	
}


