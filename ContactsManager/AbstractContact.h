#pragma once
#include <string>
class AbstractContact
{
protected:
	std::string firstname;
	std::string surname;
public:
	virtual void display() = 0;
	virtual void status() = 0;

	AbstractContact(){}
	AbstractContact(const std::string n) : firstname(n){}
	AbstractContact(const std::string n, const std::string sn) : firstname(n), surname(sn){}

	std::string getFirstname() const { //this method will not change anything
		return firstname;
	}

	std::string getSurname() const {
		return surname;
	}

	void setFirstname(const std::string& fn) {  // const: method does not modify the object
		this->firstname = fn;
	}

	void setSurname(const std::string& sn) {
		this->surname = sn;
	}


	virtual ~AbstractContact(){}
};

