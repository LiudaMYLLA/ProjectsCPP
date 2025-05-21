#pragma once
#include <iostream>
template<typename T> struct Block {
public:
	T data;
	Block<T>* next = nullptr;
	Block(T value) : data(value), next(nullptr) {}
};

template<typename T> class MinStack {
private:
	Block<T>* head = nullptr;
public:
	MinStack() : head(nullptr) {}
	void pushMin(T value);
	void deleteMin(T value);
	T getMin();
};

template<typename T> class Stack {
private:
	Block<T>* head = nullptr;
	MinStack<T> obj;
public:
	void push(T value);
	void pop();
	void display();
	void displayMin();
	T getMin();
};



template<typename T>
void MinStack<T>::pushMin(T value) {
	if (head == nullptr) {
		Block<T>* newBlock = new Block<T>(value);
		head = newBlock;
	}
	else {
		if (value <= head->data) {
			Block<T>* newBlock = new Block<T>(value);
			newBlock->next = head;
			head = newBlock;
		}
	}
}

template<typename T>
void MinStack<T>::deleteMin(T value) {
	if (head == nullptr) return;
	if (value == head->data) {
		Block<T>* next = head->next;
		delete head;
		head = next;
	}
}

template<typename T>
T MinStack<T>::getMin() {
	if (head == nullptr) { std::cout << "Stack is empty!"; return T(); }
	return head->data;
}

template<typename T>
void Stack<T>::push(T value) {
	if (head == nullptr) {
		Block<T>* newBlock = new Block<T>(value);
		head = newBlock;
		obj.pushMin(value);
	}
	else {
		Block<T>* newBlock = new Block<T>(value);
		newBlock->next = head;
		head = newBlock;
		obj.pushMin(value);
	}
}

template<typename T>
void Stack<T>::pop() {
	if (head == nullptr) {
		std::cout << "Stack is empty" << "\n";
		return;
	}
	else {
		T value = head->data;
		Block<T>* next = head->next;
		obj.deleteMin(value);
		delete head;
		head = next;
	}
}

template<typename T>
void Stack<T>::display() {
	if (!head) {
		std::cout << "Stack is empty\n";
		return;
	}
	Block<T>* temp = head;
	std::cout << "Data: " << "\n";
	while (temp) {
		std::cout << temp->data << "\n";
		temp = temp->next;
	}
}

template<typename T>
void Stack<T>::displayMin() {
	std::cout << obj.getMin() << "\n";
}

template<typename T>
T Stack<T>::getMin() {
	if (head == nullptr) {
		std::cout << "Stack is empty!";
		return T();
	}
	return obj.getMin();
}