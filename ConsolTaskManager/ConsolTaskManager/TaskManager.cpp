#include "TaskManager.h"
#include <iostream>
#include <fstream>

TaskManager::TaskManager() {}

TaskManager::~TaskManager() {}

void TaskManager::addTask(const Task& task) {
	tasks.push_back(task);
}

void TaskManager::removeTask(size_t index) {
	if (index < tasks.size()) {
		tasks.erase(tasks.begin() + index);
	}
	else {
		std::cout << "your index is incorrect";
	}
}

void TaskManager::markTaskDone(size_t index) {
	if (index < tasks.size()) {
		tasks[index].markAsDone();
	}
	else {
		std::cout << "incorrect index of task";
	}
}

void TaskManager::printAllTasks() const {
	if (tasks.empty()) {
		std::cout << "No tasks\n";
	}
	for (size_t i = 0; i < tasks.size(); ++i) {
		std::cout << i + 1 << ". " << tasks[i].toString() << "\n";
 	}
}

void TaskManager::saveToFile(const std::string& filename) const {
	std::ofstream outFile(filename);
	for (const auto& task : tasks) {
		outFile << task.getName() << '\n'
				<< task.getDescription() << '\n'
				<< task.isDone() << '\n';
	}
	outFile.close();
}

void TaskManager::loadFromFile(const std::string& filename) {
	std::ifstream inFile(filename); //open tha file and read every row
	
	std::string name, description; //creating temporary storage while is not Task
	bool completed;

	tasks.clear(); // if l had tasks then clear

	while (std::getline(inFile, name) && // first row l read as name
		std::getline(inFile, description) &&//second row l read as description
		inFile >> completed) { //third row l read as 0 or 1
		// with "&&" is a garantie that read is stoped if something will be wrong
		inFile.ignore(); // with fn ignore we will spend " " row
		
		Task task(name, description); //creating task and add to the list
		if (completed) {
			task.markAsDone();
		}
		tasks.push_back(task);
	}
	inFile.close(); // close fn for closing file


}