#pragma once
#include "Node.h"
#include "myException.h"
#include <iostream>
#include <string>
#include <utility> // For std::make, std::pair

template<typename T>
class BTree {
private:
	Node<T>* root = nullptr;
public:
	// Rule of 5
	BTree() noexcept = default;
	BTree(const BTree& other) noexcept; // copy constructor : deep copy,noexcept, RAII
	BTree(BTree&& other) : root(other.root) {
		(*this).root = nullptr;
	}// move constructor : std::move, noexcept, Rule of 5

	BTree& operator=(const BTree& other) noexcept; // copy assignment operator : deep copy,noexcept, RAII
	BTree& operator=(BTree&& other) noexcept; // move assignment operator : std::move, noexcept, Rule of 5

	~BTree() noexcept {
		clear();
	}
public:
	void insert(const T& data) noexcept;
	void insert(T&& data) noexcept;
	//void emplace(Args&&... args);  Write cool with C++17
	bool isContain(const T& data) noexcept;
	void remove(const T& data);
	auto empty() noexcept;
	void clear() noexcept;
private:
	void insertRecursive(const T& data, Node<T>* node) noexcept;
	void insertMoveRecursive(T&& data, Node<T>* node) noexcept;
	bool searchRecursive(const T& data, Node<T>* node) noexcept;
	std::pair<Node<T>*, Node<T>*> searchForDeletingRecursive(const T& data, Node<T>* node, Node<T>* parent) noexcept;
	std::pair<Node<T>*, Node<T>*> findMaxInSubTreeRecursive(Node<T>* node, Node<T>* parent) noexcept;
	void clearRecursive(Node<T>* node) noexcept;
};

template<typename T>
BTree<T>::BTree(const BTree<T>& other) noexcept {
	*this = other; // when l will write 13 func clone_subtree l will use here deep copy
}  //Tree tree2 = tree1; 

//template<typename T>						 Not optimal
//explicit Tree<T>::Tree(Tree&& other) noexcept{
//		*this = std::move(other);
//		other.root = nullptr;
//}


//template<typename T>						 Manual move constructor
//explicit Tree<T>::Tree(Tree&& other) noexcept {
//	this->root = other.root;
//	other.root = nullptr;
//}

//											 Manual move constructor
//template<typename T>
//explicit Tree<T>::Tree(Tree&& other) noexcept {
//	(*this).root = other.root;
//	other.root = nullptr;
//}


template<typename T>
BTree<T>& BTree<T>::operator=(const BTree& other) noexcept {
	if (this != &other) {
		(*this).root = other.root;  // when l will write 13 func clone_subtree l will use here deep copy
	}
	return *this;
} //tree2 = tree1;

template<typename T>
BTree<T>& BTree<T>::operator=(BTree&& other) noexcept {
	if (this != &other) {
		// add deleteSubtree()
		this->root = other.root;
		other.root = nullptr;
	}
	return *this;
}

template<typename T>
void BTree<T>::insertRecursive(const T& data, Node<T>* node) noexcept {
	if (data >= node->data) {
		if (node->right == nullptr) {
			Node<T>* newNode = new Node<T>(data); // calling parametarized constructor
			node->right = newNode;
			return;
		}
		insertRecursive(data, node->right);
	}
	else if (data < node->data) {
		if (node->left == nullptr) {
			Node<T>* newNode = new Node<T>(data);
			node->left = newNode;
			return;
		}
		insertRecursive(data, node->left);
	}
}

template<typename T>
void BTree<T>::insert(const T& data) noexcept {
	if (root == nullptr) {
		Node<T>* newNode = new Node<T>(data);
		root = newNode;
	}
	else {
		insertRecursive(data, root);
	}
}

// using universal reference
template<typename T>
void BTree<T>::insertMoveRecursive(T&& data, Node<T>* node) noexcept {
	if (data >= node->data) {
		if (node->right == nullptr) {
			Node<T>* newNode = new Node<T>(std::move(data)); // calling parametarized constructor
			node->right = newNode;
			return;
		}
		insertMoveRecursive(std::move(data), node->right);
	}
	else if (data < node->data) {
		if (node->left == nullptr) {
			Node<T>* newNode = new Node<T>(std::move(data));
			node->left = newNode;
			return;
		}
		insertMoveRecursive(std::move(data), node->left);
	}
}

template<typename T>
void BTree<T>::insert(T&& data) noexcept {
	if (root == nullptr) {
		Node<T>* newNode = new Node<T>(std::move(data));
		root = newNode;
	}
	else {
		insertMoveRecursive(std::move(data), root);
	}
}

template<typename T>
bool BTree<T>::searchRecursive(const T& data, Node<T>* node) noexcept {
	if (node->left == nullptr || node->right == nullptr) {
		if (node->data == data) {
			return true;
		}
		return false;
	}else {
		bool result = searchRecursive(data, node->left);
		if (result == true) return true;
	}

		if (node->data == data) {
			return true;
		}else if (node->right != nullptr) {
			bool result = searchRecursive(data, node->right);
			if (result == true) return true;
		}
	return false;
}

template<typename T>
bool BTree<T>::isContain(const T& data) noexcept{
	if (root == nullptr) {
		return false;
	}
	else if (root != nullptr
		&& root->left == nullptr
		&& root->right == nullptr
		&& data == root->data) {
		return true;
	}
	bool result = searchRecursive(data, root);
	return result;
}

template<typename T>
std::pair<Node<T>*, Node<T>*> BTree<T>::searchForDeletingRecursive(const T& data, Node<T>* node, Node<T>* parent) noexcept{

	if (node->left == nullptr && node->right == nullptr) { 
		if (node->data == data) {
			return { node, parent };
		}
		return { nullptr, nullptr };
	} // Or: return std::make_pair(node, parent); Or:  return { node, parent };


	if (node->left != nullptr) {
		std::pair<Node<T>*,Node<T>*> dNode_pNode = searchForDeletingRecursive(data, node->left, node);
		if (dNode_pNode.first != nullptr && dNode_pNode.first->data == data) { return dNode_pNode; }
	}

	if (node->right != nullptr) {
		std::pair<Node<T>*,Node<T>*> dNode_pNode = searchForDeletingRecursive(data, node->right, node);
		if (dNode_pNode.first != nullptr && dNode_pNode.first->data == data) { return dNode_pNode; }
	}

	return { nullptr, nullptr };
}

template<typename T>
std::pair<Node<T>*,Node<T>*> BTree<T>::findMaxInSubTreeRecursive(Node<T>* node, Node<T>* parent) noexcept{
	if (node->right == nullptr) {
		return { node, parent };
	}
	return findMaxInSubTreeRecursive(node->right, node);
}

template<typename T>
void BTree<T>::remove(const T& data) {
	if (root == nullptr) {
		return;
	}
	else if (root != nullptr 
		&& root->left == nullptr 
		&& root->right == nullptr 
		&& data == root->data) {
		delete root;
		root = nullptr;
	}
	else {
		// Type auto or:
		std::pair<Node<T>*,Node<T>*> dNode_pNode = searchForDeletingRecursive(data, root, root);

		if (dNode_pNode.first == nullptr || dNode_pNode.first->data != data) {
			try {
				throw errorDataNotExist;
			}
			catch(const std::exception& e){
				std::cout << e.what() << "\n";
			}
		}
		if (dNode_pNode.first->left == nullptr && dNode_pNode.first->right == nullptr) {
			if (dNode_pNode.second->left == dNode_pNode.first) {
				dNode_pNode.second->left = nullptr;
				delete dNode_pNode.first;
			}
			else if (dNode_pNode.second->right == dNode_pNode.first) {
				dNode_pNode.second->right = nullptr;
				delete dNode_pNode.first;
			}
		}
		else if (dNode_pNode.first->left == nullptr && dNode_pNode.first->right != nullptr) {
			if (dNode_pNode.second->right == dNode_pNode.first) {
				dNode_pNode.second->right = dNode_pNode.first->right;
				dNode_pNode.first->right = nullptr;
				delete dNode_pNode.first;
			}
			else if (dNode_pNode.second->left == dNode_pNode.first) {
				dNode_pNode.second->left = dNode_pNode.first->right;
				dNode_pNode.first->right = nullptr;
				delete dNode_pNode.first;
			}
		}
		else if (dNode_pNode.first->left != nullptr && dNode_pNode.first->right == nullptr) {
			if (dNode_pNode.second->right == dNode_pNode.first) {
				dNode_pNode.second->right = dNode_pNode.first->left;
				dNode_pNode.first->left = nullptr;
				delete dNode_pNode.first;
			}
			else if (dNode_pNode.second->left == dNode_pNode.first) {
				dNode_pNode.second->left = dNode_pNode.first->left;
				dNode_pNode.first->left = nullptr;
				delete dNode_pNode.first;
			}
		}
		else if (dNode_pNode.first->left != nullptr && dNode_pNode.first->right != nullptr) {
			// I can use min from right-subtree or max from left-subtree
			auto newData = findMaxInSubTreeRecursive(dNode_pNode.first->left, dNode_pNode.second);
			dNode_pNode.first->data = newData.first->data;
			newData.second->right = nullptr;
			delete newData.first;
		}
	}
}

template<typename T>
auto BTree<T>::empty() noexcept {
	if (root == nullptr) {
		return "Tree is empty";
	}
	else {
		return "Tree is not empty";
	}
}

template<typename T>
void BTree<T>::clearRecursive(Node<T>* node) noexcept {
	if (node->left == nullptr && node->right == nullptr) {
		delete node;
		return;
	}

	if (node->left != nullptr) {
		clearRecursive(node->left);
	}

	if (node->right != nullptr) {
		clearRecursive(node->right);
	}

	delete node;
}

template<typename T>
void BTree<T>::clear() noexcept {
	if (root == nullptr) {
		return;
	}else {
		clearRecursive(root);
		root = nullptr;
	}
}







// Complete list of methods:
//+  1. insert( const T& )	Вставка копированием
//+ 2. insert( T&& )			Вставка с перемещением
//+ 3. contains( const T& )  Поиск значения
//+ 4. remove( const T& )    Удаление узла (с балансировкой поддеревьев)
//+ 5. clear()				Очистка дерева
// 6. size() const			Количество элементов
//+ 7. empty() const			Проверка на пустоту

// 8. min(), max()			Вернуть минимальный/максимальный элемент
// 9. height()				Высота дерева
// 10.
// printInOrder(),
// printPreOrder()			Печать содержимого дерева
// 11.
// begin(), end()			Итераторы (range-for)
// emplace(args...)			Вставка по perfect forwarding
// operator==, operator!=	Сравнение двух деревьев

// 12.
// traverse(λ)				Обход дерева с пользовательской функцией (лямбдой)
// balance()				Перестроение дерева для баланса (если не AVL/Red-Black)
// 13.
// copy()					Глубокая копия дерева
// clone_subtree(Node*)		Клонирование поддерева
// 14.
// node_count(),
// leaf_count()				Статистика
// 15.
// is_balanced()			Проверка сбалансированности
// 16.
// to_vector()				Перевод в std::vector<T>
// 17.
// from_vector( const std::vector<T>& )
//							Построение дерева из отсортированного массива







// noexept means it will no runtime error (thow)

// keyword explicit used for avoiding implicity type assingment and it forbidden in signs construcrors like (=).
//So we  can do like myClass a(b); And forbidden like myClass a = b;
