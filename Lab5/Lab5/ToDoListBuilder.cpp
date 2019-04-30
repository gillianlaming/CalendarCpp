#include "stdafx.h"
#include "ToDoList.h"
#include "ToDoListBuilder.h"
using namespace std;

std::shared_ptr<ToDoList> ToDoListBuilder::buildToDoList() {
	currenttodo = make_shared<ToDoList>();
	return currenttodo;
}