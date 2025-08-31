#pragma once
#include <string>

struct Person {
	int id;
	std::string name;
	int age;
public:
	Person() = default;
	Person(int ID, std::string NAME, int AGE): id(ID), name(NAME), age(AGE){}

	bool operator<(const Person& other) const {
		return id < other.id;
	}

	bool operator>=(const Person& other) const {
		return id >= other.id;
	}
};
