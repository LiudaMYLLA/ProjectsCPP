#include <iostream>
#include "ContactsManager.h"
#include "PersonalContact.h"
#include "BusinessContact.h"


int main() {
	ContactsManager manager;
	int choice;

	while (true) {
		std::cout << "          CONTACT MANAGER          \n";
		std::cout << "0. Add Personal Contact\n";
		std::cout << "1. Add Business Contact\n";
		std::cout << "2. Display All Contacts\n";
		std::cout << "3. Search Contact by Firstname\n";
		std::cout << "4. Edit Contact\n";
		std::cout << "5. Delete Contact\n";
		std::cout << "6. Exit\n";
		std::cout << "Choose: ";
		std::cin >> choice;

		switch (choice) {
		case 0: {
			std::string fn, sn, pn, em;

			std::cout << "First name: "; std::cin >> fn;
			std::cout << "Surname: "; std::cin >> sn;
			std::cout << "Phone: "; std::cin >> pn;
			std::cout << "Email: "; std::cin >> em;

			auto contact = std::make_unique<PersonalContact>(fn, sn, pn, em);
			manager.addContact(std::move(contact));
			break;
		}
		case 1: {
			std::string fn, sn, wp, we;

			std::cout << "First name: "; std::cin >> fn;
			std::cout << "Surname: "; std::cin >> sn;
			std::cout << "Work Phone: "; std::cin >> wp;
			std::cout << "Work Email: "; std::cin >> we;

			auto contact = std::make_unique<BusinessContact>(fn, sn, wp, we);
			manager.addContact(std::move(contact));
			break;
		}
		case 2:
			manager.displayAll();
			break;

		case 3: {
			std::string fname;
			std::cout << "Enter first name to search: ";
			std::cin >> fname;
			manager.searchByFName(fname);
			break;
		}
		case 4:
			manager.editContact();
			break;

		case 5:
			std::cout << "Bye!\n";
			return 0;

		default:
			std::cout << "Invalid option. Try again.\n";
		}
	}
}