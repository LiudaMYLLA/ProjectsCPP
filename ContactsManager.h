#pragma once
#include <memory>
#include <vector>
#include "AbstractContact.h"
class ContactsManager
{
private:
	std::vector<std::unique_ptr<AbstractContact>> contacts;

public:

	ContactsManager();

	void addContact(std::unique_ptr<AbstractContact> contact);

	void searchByFName(const std::string& fname);

	void deleteContact(std::unique_ptr<AbstractContact> contact);

	void editContact();

	void displayAll();

};



//contacts = [
//	[unique_ptr]→ 🧍 AbstractContact(PersonalContact),
//	[unique_ptr] → 🧍 AbstractContact(BusinessContact),
//	[unique_ptr] → 🧍 AbstractContact(PersonalContact),
//]



// Goals are using smart pointers 
//			*There are*
//	 1. std::unique_ptr<someType>	&&	std::make_unique<sometype>()
//	 2. std::shared_ptr<someType>	&&	std::make_shared<T>()			&& use_count(), reset()
//	 3. std::weak_ptr<someType>

// syntax 
// std::unique_ptr<T>
// where T = AbstractContact
// a smart pointer that owns an object of type AbstractContact, and automatically deletes it when destroyed
// unique_ptr is a class template, and you must specify what type it owns