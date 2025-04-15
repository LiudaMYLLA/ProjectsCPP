#include "Task.h"
#include <iostream>

Task::Task() : name(""), description(""), completed(false) {}

Task::Task(const std::string& name, const std::string& description) :
	name(name), description(description), completed(false) {}

void Task::markAsDone() {
	completed = true;
}

bool Task::isDone() const {
	return completed;
}

std::string Task::getDescription() const {
	return description;
}

std::string Task::getName() const {
	return name;
}

std::string Task::toString() const {
	std::string status = completed ? "[X]" : "[ ]";
	return status + name + ": " + description;
}


Task::~Task(){

}