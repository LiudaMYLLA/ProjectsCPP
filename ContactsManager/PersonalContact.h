#pragma once
#include "AbstractContact.h"
#include <string>
#include <iostream>
class PersonalContact : public AbstractContact
{
private:
	std::string phoneNumber;
	std::string email;

public:
	PersonalContact(){}
	PersonalContact(std::string fn, std::string sn, std::string phn, std::string e)
		: AbstractContact(fn, sn), phoneNumber(phn), email(e){}

	void display() override {
		std::cout << "Name: " << getFirstname() << " " << getSurname() << "\n"
			<< "Phone Number: " << phoneNumber << "\n"
			<< "Email: " << email << "\n";
	}

	void status() override {
		std::cout << "Personal contact";
	}

	std::string getPhoneNumber() const { // the method will not change anything
		return phoneNumber;
	}

	std::string getEmail() const {
		return email;
	}

	void setPhoneNumber(const std::string& phn) {
		this->phoneNumber = phn;
	}

	void setEmail(const std::string& e) {
		this->email = e;
	}
};

