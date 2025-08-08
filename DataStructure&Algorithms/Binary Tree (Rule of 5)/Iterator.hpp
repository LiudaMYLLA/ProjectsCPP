#pragma once
#include <iostream>
#include <stack>
#include <iterator>
#include <cstddef>
#include "Node.hpp"

template<typename T>
class Iterator {
public:
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using difference_type = std::ptrdiff_t;
	using iterator_category = std::forward_iterator_tag;

	Iterator(Node<T>* _node) : node(_node) {
		while (node != nullptr) {
			stack.push(node); // For this stack std::stack <Node<T>*> stack; that belongs to obj it we are creating 
			if (node->left == nullptr) {
				break;
			}
			else {
				node = node->left; // node set up for Node<T>* node; this field of obj it Node 
			}
		}
		if (!stack.empty()) {
			stack.pop();
		}
	};

	T& operator*() const;
	T* operator->() const;

	void operator++();  // ++it; original moving -> pre-increment

	bool operator==(const Iterator& other) const;
	bool operator!=(const Iterator& other) const;

	Iterator<T> operator++(int); // it++ -> post-increment  // int here is 

private:
	Node<T>* node = nullptr;
	std::stack <Node<T>*> stack;
};

template<typename T>
Iterator<T> Iterator<T>::operator++(int) {
	Iterator<T> temp = *this;
	operator++();
	return temp;
}

template<typename T>
bool Iterator<T>::operator==(const Iterator<T>& other) const {
	return this->node == other.node;
}

template<typename T>
T& Iterator<T>::operator*() const {
	return this->node->data;  // we returned the data; T& pseudonym for this data
}

template<typename T>
T* Iterator<T>::operator->() const {
	return &(this->node->data);  // we returned an address for pointer; 
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator<T>& other) const {
	return this->node != other.node;
}


template<typename T>
void Iterator<T>::operator++() { // we will return reference on the current obj
	if (node == nullptr) {
		return;
	}
	if (node->right != nullptr) {
		node = node->right; // Node<T>* node; Exactly this field we are set up in new node
		while (node->left != nullptr) {
			stack.push(node);
			node = node->left;
		}
	}
	else {
		if (!stack.empty()) {
			node = stack.top();
			stack.pop();
		}
		else {
			node = nullptr;
		}
	}
}


