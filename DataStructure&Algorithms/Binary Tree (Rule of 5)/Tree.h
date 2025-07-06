#include "Node.h"
#include <iostream>
#include <string>
#include <utility>

template<typename T>
class Tree {
private:
	Node<T>* root = nullptr;
public:
	// Rule of 5
	Tree() noexcept = default;		
	explicit Tree(const Tree& other) noexcept; // copy constructor : deep copy,noexcept, RAII
	explicit Tree(Tree&& other) : root(other.root)  noexcept;	   // move constructor : std::move, noexcept, Rule of 5

	Tree& operator=(const Tree& other) noexcept; // copy assignment operator : deep copy,noexcept, RAII
	Tree& operator=(Tree&& other) noexcept; // move assignment operator : std::move, noexcept, Rule of 5

	~Tree() noexcept = default;
public:
	void insert(const T& data) noexcept;
	void insert(T&& data) noexcept;
	//void emplace(Args&&... args);  Write cool with C++17
private:
	void insertRecursive(const T& data, Node<T>* node) noexcept;
	void insertMoveRecursive(T&& data, Node<T>* node) noexcept;
};

template<typename T>				
explicit Tree<T>::Tree(const Tree<T>& other) noexcept{
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
explicit Tree<T>::Tree(Tree&& other): root(other.root) noexcept {
	other.root = nullptr;
}

template<typename T>
Tree<T>& Tree<T>::operator=(const Tree& other) noexcept {
	if (this != &other) {
		(*this).root = other.root;  // when l will write 13 func clone_subtree l will use here deep copy
	}
	return *this;
} //tree2 = tree1;

template<typename T>
Tree<T>& Tree<T>::operator=(Tree&& other) noexcept {
	if (this != &other) {
		// add deleteSubtree()
		this->root = other.root;
		other.root = nullptr;
	}
	return *this;
}

template<typename T>
void Tree<T>::insertRecursive(const T& data, Node<T>* node) noexcept{
	if (data >= node->data) {
		if (node->right == nullptr) {
			Node<T>* newNode = new Node(data); // calling parametarized constructor
			node->right = newNode;
			return;
		}
		insertRecursive(data, node->right);
	}
	else if (data < node->data) {
		if (node->left == nullptr) {
			Node<T>* newNode = new Node(data); 
			node->left = newNode;
			return;
		}
		insertRecursive(data, node->left);
	}
}

template<typename T>
void Tree<T>::insert(const T& data) noexcept {
	if (root == nullptr) {
		Node<T>* newNode = new Node(data); 
		root = newNode;
	}
	else {
		insertRecursive(data, root);
	}
}

// using universal reference
template<typename T>
void Tree<T>::insertMoveRecursive(T&& data, Node<T>* node) noexcept {
	if (data >= node->data) {
		if (node->right == nullptr) {
			Node<T>* newNode = new Node(std::move(data)); // calling parametarized constructor
			node->right = newNode;
			return;
		}
		insertMoveRecursive(std::move(data), node->right);
	}
	else if (data < node->data) {
		if (node->left == nullptr) {
			Node<T>* newNode = new Node(std::move(data));
			node->left = newNode;
			return;
		}
		insertMoveRecursive(std::move(data), node->left);
	}
}

template<typename T>
void Tree<T>::insert(T&& data) noexcept {
	if (root == nullptr) {
		Node<T>* newNode = new Node(std::move(data));
		root = newNode;
	}
	else {
		insertMoveRecursive(std::move(data), root);
	}
}








// Complete list of methods:
//+  1. insert( const T& )	Вставка копированием
//+ 2. insert( T&& )			Вставка с перемещением
// 3. contains( const T& )  Поиск значения
// 4. remove( const T& )    Удаление узла (с балансировкой поддеревьев)
// 5. clear()				Очистка дерева
// 6. size() const			Количество элементов
// 7. empty() const			Проверка на пустоту

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