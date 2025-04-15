#pragma once

#include <string>

class Task 
{
private:
	std::string name;
	std::string description;
	bool completed = false;

public:
	Task();
	Task(const std::string& name, const std::string& description);

	void markAsDone();
	bool isDone() const;

	std::string getName() const;
	std::string getDescription() const;
	std::string toString () const;

	~Task(); 
};

