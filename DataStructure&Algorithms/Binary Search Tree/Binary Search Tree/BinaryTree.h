#pragma once
#include <iostream>
#include <type_traits>
#include <string>

using Integer = int;

template<typename T>
struct Node {
public:
	T data;
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;

	Node() = default;
	~Node() = default;
};


template<typename T> class BinaryTree {
private:
	Node<T>* root = nullptr;
public:
	BinaryTree() = default;
	void insertion(Node<T>*& root, T data);
	void remove(Node<T>*& root, T data);
	~BinaryTree() = default;
};


template<typename T> 
void BinaryTree<T>::insertion(
	Node<T>*& root, T data
) {
	static_assert(
		std::is_same<T, std::string>::value ||
		std::is_same<T, Integer>::value ||
		std::is_same<T , float>::value,
		"Incorrect type!");

	if (root == nullptr) {
		Node<T>* newNode = new Node<T>();  // creating heap object. So rn newNode just contains an address to this obj.
		newNode->data = data;
		newNode->left = nullptr;
		newNode->right = nullptr;
		root = newNode;
	}else if (data < root->data) {
		insertion(root->left, data);
	}else if (data > root->data) {
		insertion(root->right, data);
	}else
	{
		std::cout << "There is a copy!" << "\n";
		return;
	}
}

template<typename T>
void BinaryTree<T>::remove(Node<T>*& root ,T data) { // ref to the root if new param(and this is root->left) ref to the field root->left that in root So if we have this ref we have stright acces to the node with this addree in memory because we know this address so if next root->right What we do we have address 1x100 that is root->left whatch in this address root->right and we cuurently in that root->right! And if i change root i change field from parance
	if (!root) {					// root = 1xA0; points to main node that is called root with data 10
		std::cout << "Binary Tree is empty" << "\n";
		return;
	}
	  
	if (root->data == data) {
		if (root->left != nullptr && root->right == nullptr) {
			Node<T>* temp = root;   
			root = root->left;
			delete temp;
		}
		else if (root->right != nullptr && root->left == nullptr) {
			Node<T>* temp = root; // creating temp that containce the same that current root 1xB0
			root = root->right;	  	 
			delete temp;
		}
		else if (root->left != nullptr && root->right != nullptr) {
			// searching min in right sub-tree
			Node<T>* minNode = root->right;
			while (minNode->left != nullptr) {
				minNode = minNode->left;
			}
			root->data = minNode->data;
			remove(root->right, minNode->data);
		}
	}
	if (root->left == nullptr && root->right == nullptr) {

		if (root->data == data) {
			delete root;
			root = nullptr;
			return;
		}
		else {
			std::cout << "There is no exiting node with such data!"
				<< "\n";
			return;
		}
	}else if (root->left != nullptr) {
		if (data < root->data) {
			remove(root->left, data);  // now we put in param field of root and we cuurently in that field and can change its (now 1xB0)
		}
	}
	else if (root->right != nullptr) {
		if (data > root->data) {
			remove(root->right, data);
		}
	}
}