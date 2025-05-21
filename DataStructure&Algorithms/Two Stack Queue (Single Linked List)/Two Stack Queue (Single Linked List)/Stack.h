#pragma once
#include <iostream>
#include <vector>
#include <new> // Describes std::bad_alloc

template<typename T>
struct Node {
public:
	T data;
	Node<T>* next = nullptr;

	Node() {}
	Node(T d): data(d), next(nullptr){}
	~Node(){}
};

template<typename T> class StackOut;

template<typename T>
class StackAdd
{
private:
	Node<T>* head = nullptr;
public:
	StackAdd(){}
	bool addNode(T data);
	~StackAdd(){}

	template<typename T> friend void StackOut<T>::pushInFrontForDelete(StackAdd& h);
	template<typename T> friend void StackOut<T>::deleteLastOne(StackAdd<T>& h);
};

template<typename T>
class StackOut
{
private:
	Node<T>* head = nullptr;
public:
	StackOut(){}
	void pushInFrontForDelete(StackAdd& h);
	void deleteLastOne(StackAdd<T>& h);
	~StackOut(){}
};

template<typename T>
bool StackAdd<T>::addNode(T d) {
	try {
		if (head == nullptr) {
			Node<T>* newNode = new Node<T>();
			newNode->data = d;
			head = newNode;
			newNode->next = nullptr;
			return true;
		}
		else {
			Node<T>* newNode = new Node<T>();
			newNode->data = d;
			newNode->next = head;
			head = newNode;
			return true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << "Memory allocation failed: " << e.what() << "\n";
		return false;
	}
}

template<typename T>
void StackOut<T>::pushInFrontForDelete(StackAdd<T>& h) {
	if (h.head == nullptr) { return; }
	try{
		Node<T>* temp = h.head;

		std::vector<T> dataStorage;

		Node<T>* prevtemp = temp;
		while (temp) {
			dataStorage.push_back(temp->data);
			temp = temp->next;
			delete prevtemp;
			prevtemp = temp;
		}
		h.head = nullptr;

		int size = dataStorage.size();
		for (int i = 0; i <= size - 1; ++i) {

			Node<T>* newNode = new Node<T>();
			newNode->data = dataStorage[i];

			newNode->next = head;
			head = newNode;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what() << "\n";
	}

}


template<typename T>
void StackOut<T>::deleteLastOne(StackAdd<T>& h) {
	if (h.head == nullptr) { return; }
	if (head == nullptr) {
		pushInFrontForDelete(h);
	}
	if (head != nullptr) {
		Node<T>* temp = head->next;
		delete head;
		head = temp;
	}
}


