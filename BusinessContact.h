#pragma once
#include "AbstractContact.h"
#include <string>
#include <iostream>
class BusinessContact : public AbstractContact
{
private:
	std::string workPhone;
	std::string workEmail;

public:
	BusinessContact(){}
	BusinessContact(std::string fn, std::string sr, std::string wph, std::string we)
		: AbstractContact(fn, sr), workPhone(wph), workEmail(we){}

	void display() override {
		std::cout << "Firstname: " << getFirstname() << " "
			<< "Surname: " << getSurname() << " "
			<< "workPhone: " << workPhone << " "
			<< "workEmail: " << workEmail << "\n";
	}

	void status() override {
		std::cout << "Business contact";
	}



	void setWorkPhone(const std::string& wph) {  // the parameter will not changed in method
		this->workPhone = wph;
	}

	void setWorkEmail(const std::string& we) {
		this->workEmail = we;
	}

	std::string getWorkPhone() const { // this method will not change anything
		return workPhone;
	}

	std::string getWorkEmail() const {
		return workEmail;
	}

};




// diffrance const std::string getWorkPhone()  - Возвращается строка, но это бесполезно. The returned value is a const std::string. “Возвращается const std::string, которую нельзя менять… но так как это копия — ты всё равно можешь её изменить.”

// getWorkPhone() co2nst - Метод ничего не меняет. “Этот метод ничего не меняет в объекте.”Его можно вызывать даже у const объектов.


