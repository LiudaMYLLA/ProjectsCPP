#include <iostream>
#include <string>

#include "TaskManager.h"

int main() {
	TaskManager manager;
	std::string name, description;
	size_t index;
	int choice;

	manager.loadFromFile("storage.txt");

	do {
		std::cout << "\n========== Task Manager ==========\n";
		std::cout << "1. Add task\n";
		std::cout << "2. Show all tasks\n";
		std::cout << "3. Do a task completed\n";
		std::cout << "4. Delete a task\n";
		std::cout << "5. Save in file\n";
		std::cout << "0. Exit\n";
		std::cout << "Choice: ";
		std::cin >> choice;
		std::cin.ignore(); //clean input

		switch (choice) {
		case 1:
			std::cout << "Input name of task: ";
			std::getline(std::cin, name);
			std::cout << "Input description: ";
			std::getline(std::cin, description);
			manager.addTask(Task(name, description));
			break;

		case 2:
			manager.printAllTasks();
			break;

		case 3:
			std::cout << "Input number of task: ";
			std::cin >> index;
			manager.markTaskDone(index - 1);
			break;

		case 4:
			std::cout << "Input number of task for delete: ";
			std::cin >> index;
			manager.removeTask(index - 1);
			break;

		case 5:
			manager.saveToFile("storage.txt");
			std::cout << "Saved in storage.txt\n";
			break;

		case 0:
			std::cout << "Exit...\n";
			manager.saveToFile("storage.txt");
			break;

		default:
			std::cout << "The choice is incorrect. Please try again.\n";
		}
		
	} while (choice != 0);
	return 0;
}