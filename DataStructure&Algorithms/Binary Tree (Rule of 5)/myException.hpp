#pragma once
#include <iostream>
#include <exception>

class myException : public std::exception {
	virtual const char* what() const noexcept override {
		return "This data not exist! Nothing was deleted";
	}
};
// Or } errorDataNotExist; Means it is a global variable of the class

const myException errorDataNotExist;
