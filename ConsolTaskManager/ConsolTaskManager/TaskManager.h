#pragma once

#include <vector>
#include "Task.h"

class TaskManager
{
private:
	std::vector<Task> tasks;

public:
	TaskManager();

	void addTask(const Task& task);
	void removeTask(size_t index);
	void markTaskDone(size_t index);
	void printAllTasks() const;

	void saveToFile(const std::string& filename) const;
	void loadFromFile(const std::string& filename);

	~TaskManager();
};

// size_t - much more then int and safe for index so its from 0 