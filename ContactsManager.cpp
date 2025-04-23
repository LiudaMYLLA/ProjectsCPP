#include "ContactsManager.h"
#include "PersonalContact.h"
#include "BusinessContact.h"
#include <iostream>
#include <algorithm>
#include <memory>
#include <utility>

ContactsManager::ContactsManager() {

}

//std::any_of(...) - checks if any element in a range satisfies a condition.
// any_of is always bool type

// using Lambda
//		Syntax
// [ capture ](parameters) -> return_type {
//		 body
//	}


void ContactsManager::addContact(std::unique_ptr<AbstractContact> contact){
	
	// we should check it exist or not
	bool exists = std::any_of(contacts.begin(), contacts.end(),
		[&contact](const std::unique_ptr<AbstractContact>& current) -> bool {  // const means: I promise not to modify this object inside the lambda. we are only reading not chaging it. const reference = more efficient and safer.
			return current->getFirstname() == contact->getFirstname() &&
				current->getSurname() == contact->getSurname();
		});

	if (!exists) {
		contacts.push_back(std::move(contact));
		std::cout << "Contact added successfully.\n";
	}
	else {
		std::cout << "Contact: " 
			<< contact->getFirstname() << " "
			<< contact->getSurname() << "already exist.\n";
	}

}

// The find pattern : STL pattern
// std::find_if(start, end, condition);
// where condition is lambda. The lambda always returns a bool

// find_if takes a range (start, end) and a predicate — a function or lambda that returns true or false.

void ContactsManager::searchByFName(const std::string& fname) {
	auto iterator = std::find_if(contacts.begin(), contacts.end(),
		[&fname](const std::unique_ptr<AbstractContact>& current) {
			return current->getFirstname() == fname;
		});
	if (iterator != contacts.end()) {
		(*iterator)->display();
	}
	else {
		std::cout << "Contact was not found with name: " << fname << "\n";
	}
}

// Erase–Remove idiom : STL pattern
// it all works togather
// remove_if(...):  Moves matched elements to the end
// returns new_end. new_end is an iterator.  It points to the first element that should be deleted.
// erase(begine, end)


void ContactsManager::deleteContact(std::unique_ptr<AbstractContact> contact) {

	auto new_end = std::remove_if(contacts.begin(), contacts.end(),
		[&contact](const std::unique_ptr<AbstractContact>& current) -> bool {
			return current->getFirstname() == contact->getFirstname() && current->getSurname() == contact->getSurname();
		});

	if (new_end != contacts.end()) {
		contacts.erase(new_end, contacts.end());
		std::cout << "Contact: " << contact->getFirstname() << " " << contact->getSurname() << " was deleted." << "\n";
	}
	else {
		std::cout << "No contact found with name: "
			<< contact->getFirstname() << " "
			<< contact->getSurname() << "\n";
	}	
}


// dynamic_cast
// dynamic_cast lets you safely convert a pointer/reference to a base class → into a pointer/reference to a derived class, at runtime.
// dynamic_cast позволяет безопасно преобразовать указатель/ссылку базового класса → в указатель/ссылку на дочерний класс, во время выполнения.
// Выполняет проверку во время выполнения. Если объект не того типа — возвращает nullptr. В базовом классе должен быть virtual метод.
//AbstractContact* c = new PersonalContact();
//if (auto* p = dynamic_cast<PersonalContact*>(c)) {
//	p->setPhoneNumber("12345");
//}
void ContactsManager::editContact() {

	std::string firstname, surname;
	std::cout << "What contact do u want to edit? Input firstname and surname: " << "\n";
	std::cin >> firstname;
	std::cout << " ";
	std::cin >> surname;

	auto iterator = std::find_if(contacts.begin(), contacts.end(),
		[&firstname, &surname](const std::unique_ptr<AbstractContact>& current) ->bool {
			return (firstname + " " + surname) == (current->getFirstname() + " " + current->getSurname());
		});

	if (iterator != contacts.end()) {
		AbstractContact* contact = iterator->get();
		(*iterator)->status();

		std::cout << "What field do u want to change? Enter a number: " << "\n";
		std::cout << "1. Phone Number;" << "\n"
			<< "2. Email;" << "\n"
			<< "3. Cancel." << "\n";

		int field;
		std::cin >> field;
		
		if (auto* personalContact = dynamic_cast<PersonalContact*>(contact)) {

			
			std::string pn;
			std::string e;

			switch (field) {
			case 1:
				std::cout << "Input a number: " << "\n";
				std::cin >> pn;
				personalContact->setPhoneNumber(pn);
				std::cout << "Number was set successfully\n";
				break;
			case 2:
				std::cout << "Input an email: " << "\n";
				std::cin >> e;
				personalContact->setEmail(e);
				std::cout << "Email was set successfully\n";
				break;
			case 3:

				break;
			default:
				std::cout << "Enter a valid number!" << "\n";
			}

		}
		else if(auto* businessContact = dynamic_cast<BusinessContact*>(contact)) {

			std::string wn;
			std::string we;

			switch (field) {
			case 1:
				std::cout << "Input a number: " << "\n";
				std::cin >> wn;
				businessContact->setWorkPhone(wn);
				std::cout << "Number was set successfally\n";
				break;
			case 2:
				std::cout << "Input an email: " << "\n";
				std::cin >> we;
				businessContact->setWorkEmail(we);
				std::cout << "Email was set successfully\n";
				break;
			case 3:

				break;
			default:
				std::cout << "Enter a valid number!" << "\n";
			}

		}

	}
	else {
		std::cout << "Contact with such firstname and surname was not found." << "\n";
	}
}

void ContactsManager::displayAll() {

	if (contacts.empty()) {
		std::cout << "No contacts to display.\n";
		return; // so we do not need the loop below
	}


	for (const auto& contact : contacts) {
		contact->display();
		std::cout << "---------------------------------\n";
	}
}