#include <iostream>

struct Node {
public:
	int data;
	Node* next = nullptr;
	Node* prev = nullptr;

	Node() :data(0), next(nullptr), prev(nullptr){}

	Node(int value) {
		this->data = value;
		this->prev = nullptr;
		this->next = nullptr;
	}
};

class DoublyLinkedList {
private:
	Node* head = nullptr;
public:
	void createFirstNode(int value);
	void insertAtTheBeginning(int value);
	void insertAtTheEnd(int value);
	void insertAtThePosition(int value, int position);
	void deleteFirstNode();
	void deleteLastNode();
	void deleteNodeWithPosition(int position);
	void display();
};

void DoublyLinkedList::createFirstNode(int value) {
	if (head == nullptr) {
		Node* newNode = new Node();
		newNode->data = value;
		newNode->prev = nullptr;
		head = newNode;
		newNode->next = nullptr;
	}
	else {
		std::cout << "You has already created first node" << "\n";
		return;
	}
}

void DoublyLinkedList::insertAtTheBeginning(int value) {
	if (head == nullptr) {
		createFirstNode(value);
		return;
	}
	Node* newNode = new Node(value);
	newNode->prev = nullptr;
	head->prev = newNode;
	newNode->next = head;
	head = newNode;
}

void DoublyLinkedList::insertAtTheEnd(int value) {
	if (head == nullptr) {
		createFirstNode(value);
		return;
	}
	
	Node* temp = head;
	while (temp->next) {
		temp = temp->next;
	}
	// temp now is equal the last node
	Node* newNode = new Node(value);
	newNode->next = nullptr;
	newNode->prev = temp;
	temp->next = newNode;
}


void DoublyLinkedList::insertAtThePosition(int value, int position){
	if (!head) {
		if (position == 0) {
			createFirstNode(value);
		}
		else {
			std::cout << "Doubly Linked List is empty" << "\n";
			std::cout << "Position: " << position << "is not correct!" << "\n";
			return;
		}
	}

	if (position == 0) {
		insertAtTheBeginning(value);
		return;
	}

	Node* temp = head;
	for (int i = 1; i <= position - 1 && temp; ++i) {
		temp = temp->next;
	}

	if (!temp) {
		std::cout << "Position: " << position << " does not exist!" << "\n";
		return;
	}

	if (temp->next != nullptr) {
		Node* newNode = new Node();
		newNode->data = value;

		Node* prevNode = temp;
		Node* nextNode = temp->next;

		newNode->next = nextNode;
		nextNode->prev = newNode;

		prevNode->next = newNode;
		newNode->prev = prevNode;
		
	}
	else {
		std::cout << "The position you taped related to last node" << "\n";
		Node* newNode = new Node(); 
		newNode->data = value;
		temp->next = newNode;
		newNode->prev = temp;
		newNode->next = nullptr;
		return;
	}
}

void DoublyLinkedList::deleteFirstNode() {
	if (!head) {
		std::cout << "Doubly Linked List is not exist" << "\n";
		return;
	}
	Node* temp = head;
	if (temp->next) {
		head = temp->next;
		head->prev = nullptr;
		delete temp;
	}
	else {
		delete head;
		head = nullptr;
	}
}

void DoublyLinkedList::deleteLastNode() {
	if (!head) {
		std::cout << "Doubly Linked List is empty!" << "\n";
		return;
	}

	Node* temp = head;
	if (temp->next) {
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		Node* prev = temp->prev;
		prev->next = nullptr;
		delete temp;
	}
	else {
		delete temp;
		head = nullptr;
	}
}

void DoublyLinkedList::deleteNodeWithPosition(int position) {
	if (!head) {
		std::cout << "Doubly Linked List is empty" << "\n";
		return;
	}
	if (position == 0) {
		deleteFirstNode();
		return;
	}
	Node* temp = head;
	for (int i = 1; i <= position && temp; ++i) {
		temp = temp->next;
	}
	if (!temp) {
		std::cout << "Position is incorrect!" << "\n";
		return;
	}
	Node* prev = temp->prev;
	if (temp->next) {
		Node* next = temp->next;
		prev->next = next;
		next->prev = prev;
		delete temp;
	}
	else {
		prev->next = nullptr;
		delete temp;
	}
}

void DoublyLinkedList::display() {
	if (!head) {
		std::cout << "Doubly Linked List is empty" << "\n";
		return;
	}
	Node* temp = head;
	while (temp) {
		std::cout << " " << temp->data << "\n";
		temp = temp->next;
	}
}


int main() {

}