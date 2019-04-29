#pragma once
#include "DisplayableComponent.h"

using namespace std;

class Task : public DisplayableComponent {
protected:
	std::string name;
public:
	virtual void display(int depth);
	Task(string name);
};
