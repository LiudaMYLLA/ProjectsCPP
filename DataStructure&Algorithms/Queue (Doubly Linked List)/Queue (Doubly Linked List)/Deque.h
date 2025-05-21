#pragma once
#include <iostream>

template<typename T>
struct Node {
public:
	T data;
	Node<T>* next = nullptr;
	Node<T>* prev = nullptr;
	Node(){}
	Node(T d): data(d), next(nullptr), prev(nullptr){}
};


template<typename T>
class Deque
{
private:
	Node<T>* head = nullptr;
	Node<T>* tail = nullptr;
public:
	Deque<T>() {};
	void addFront(T d);
	void addBack(T d);
	void removeFront();
	void removeBack();
	T peekFront();
	T peekBack();
	bool isEmpty();
	void display();
	~Deque<T>() {
		if (head != nullptr) {
			Node<T>* current = head;
			Node<T>* next = head;
			while (current != nullptr) {
				next = next->next;
				delete current;
				current = next;
			}
		}
	}
};

template<typename T>
void Deque<T>::addFront(T d) {
	if (head == nullptr && tail == nullptr) {
		Node<T>* newNode = new Node<T>();
		newNode->data = d;
		head = newNode;
		newNode->prev = nullptr;
		newNode->next = nullptr;
		tail = newNode;
	}
	else {
		Node<T>* newNode = new Node<T>();
		newNode->data = d;
		head->prev = newNode;
		newNode->next = head;
		newNode->prev = nullptr;
		head = newNode;
	}
}

template<typename T>
void Deque<T>::addBack(T d) {
	if (head == nullptr && tail == nullptr) {
		Node<T>* newNode = new Node<T>();
		newNode->data = d;
		head = newNode;
		tail = newNode;
		newNode->prev = nullptr;
		newNode->next = nullptr;
	}
	else {
		Node<T>* newNode = new Node<T>();
		newNode->data = d;
		tail->next = newNode;
		newNode->prev = tail;
		newNode->next = nullptr;
		tail = newNode;
	}
}

template<typename T>
void Deque<T>::removeFront() {
	if (head == nullptr && tail == nullptr) {
		std::cout << "Deque is empty!" << "\n";
		return;
	}
	if (head->next == nullptr) {
		delete head;
		head = nullptr;
		tail = nullptr;
		return;
	}
	Node<T>* next = head->next;
	next->prev = nullptr;
	delete head;
	head = next;
}

template<typename T>
void Deque<T>::removeBack() {
	if (head == nullptr) {
		std::cout << "Deque is empty!" << "\n";
		return;
	}
	if (tail->prev == nullptr) {
		delete tail;
		tail = nullptr;
		head = nullptr;
		return;
	}
	Node<T>* prev = tail->prev;
	prev->next = nullptr;
	delete tail;
	tail = prev;
}

template<typename T>
T Deque<T>::peekFront() {
	if (!head) {
		std::cout << "Deque is empty!" << "\n";
		return T();
	}
	return head->data;
}

template<typename T>
T Deque<T>::peekBack() {
	if (!tail) {
		std::cout << "Deque is empty!" << "\n";
		return T();
	}
	return tail->data;
}

template<typename T>
bool Deque<T>::isEmpty() {
	return head == nullptr;
}

template<typename T>
void Deque<T>::display() {
	if (head == nullptr) {
		std::cout << "Deque is empty!" << "\n";
		return;
	}
	Node<T>* temp = head;
	while(temp != nullptr){
		std::cout << temp->data << "\n";
		temp = temp->next;
	}
}