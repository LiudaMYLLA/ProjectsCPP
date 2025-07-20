#include "Node.h"
#include "myException.h"
#include <iostream>
#include <string>
#include <utility> // For std::move, std::pair, std::forward
#include <optional>
#include <algorithm> // For std::max(first, second);

namespace tags {
	struct manualMoveTag {};
}

template<typename T>
class [[nodiscard]] BTree {
private:
	Node<T>* root = nullptr;
public:
	// Rule of 5
	BTree() noexcept = default;

	BTree(const BTree& other) noexcept; //deep copy
	
	// Two move constructors are intentionally kept:
	// 1. Optimized version (used in practice)
	// 2. Deprecated manual version (kept for historical reference and learning)
	BTree(BTree&& other) noexcept;
	[[deprecated("Move constructor manual and not optimized")]] 
	BTree(BTree<T>&& other, [[maybe_unused]] tags::manualMoveTag) noexcept;

	BTree& operator=(const BTree& other) noexcept; //deep copy

	BTree& operator=(BTree&& other) noexcept; 

	~BTree() noexcept {
		clear();
	}

public:
	void insert(const T& data) noexcept;
	void insert(T&& data) noexcept;
	[[nodiscard]] bool isContain(const T& data) noexcept;
	void remove(const T& data);
	[[nodiscard]] bool empty() const noexcept;
	void clear() noexcept;
	[[nodiscard]] int size() const noexcept;
	[[nodiscard]] std::optional<std::pair<Node<T>*, Node<T>*>> min() noexcept;
	[[nodiscard]] std::optional<std::pair<Node<T>*, Node<T>*>> max() noexcept;
	[[nodiscard]] int getHeight() const noexcept;

private:
	void insertRecursive(const T& data, Node<T>* node) noexcept;
	void insertMoveRecursive(T&& data, Node<T>* node) noexcept;
	[[nodiscard]] bool searchRecursive(const T& data, Node<T>* node) noexcept;
	std::pair<Node<T>*, Node<T>*>& searchForDeletingRecursive(const T& data, Node<T>* node, Node<T>* parent) noexcept;
	std::pair<Node<T>*, Node<T>*> findMaxInSubTreeRecursive(Node<T>* node, Node<T>* parent) noexcept;
	void clearRecursive(Node<T>* node) noexcept;
	[[nodiscard]] int size(Node<T>* node) const noexcept;
	[[nodiscard]] std::pair<Node<T>*, Node<T>*> minRecursive(Node<T>* node, Node<T>* parent, Node<T>* minNode) noexcept;
	[[nodiscard]] std::pair<Node<T>*, Node<T>*> maxRecursive(Node<T>* node, Node<T>* parent, Node<T>* maxNode) noexcept;
	[[nodiscard]] int getHeightRecursive(Node<T>* node) const noexcept;
};

template<typename T>
BTree<T>::BTree(BTree&& other) noexcept : root(other.root) {
	other.root = nullptr;
}

template<typename T>
BTree<T>::BTree(const BTree<T>& other) noexcept {
	*this = other; // when l will write 13 func clone_subtree l will use here deep copy
}  //Tree tree2 = tree1; 

template<typename T>						 
[[deprecated("Move constructor manual and not optimized")]] 
BTree<T>::BTree(BTree<T>&& other, [[maybe_unused]] tags::manualMoveTag) noexcept {
		*this = std::move(other); 
		// or this->root = other.root;
		// or (*this).root = other.root;
		other.root = nullptr;
}

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
[[nodiscard]] bool BTree<T>::searchRecursive(const T& data, Node<T>* node) noexcept {
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
[[nodiscard]] bool BTree<T>::isContain(const T& data) noexcept{
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
std::pair<Node<T>*, Node<T>*>& BTree<T>::searchForDeletingRecursive(const T& data, Node<T>* node, Node<T>* parent) noexcept{

	if (node->left == nullptr && node->right == nullptr) { 
		if (node->data == data) {
			return { node, parent };
		}
		return { nullptr, nullptr };
	} // Or: return std::make_pair(node, parent); Or:  return { node, parent };


	if (node->left != nullptr) {
		decltype(auto) dNode_pNode = searchForDeletingRecursive(data, node->left, node);
		if (dNode_pNode.first != nullptr && dNode_pNode.first->data == data) { return dNode_pNode; }
	}

	if (node->right != nullptr) {
		std::pair<Node<T>*,Node<T>*>& dNode_pNode = searchForDeletingRecursive(data, node->right, node);
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
[[nodiscard]] bool BTree<T>::empty() const noexcept {
	if (root == nullptr) {
		return true;
	}
	else {
		return false;
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

template<typename T>
[[nodiscard]] int BTree<T>::size(Node<T>* node) const noexcept {
	int size = 0;

	if (node->left == nullptr && node->right == nullptr) {
		size += 1;
		return size;
	}

	if (node->left != nullptr) {
		size += size(node->left);
	}

	if (node->right != nullptr) {
		size += size(node->right);
	}

	size += 1;
	return size;
}

template<typename T>
[[nodiscard]] int BTree<T>::size() const noexcept{
	if (empty()) return 0;
	if (root->left == nullptr && root->right == nullptr) return 1;

	int result = size(root);
	return result;
}

template<typename T>
[[nodiscard]] std::pair<Node<T>*, Node<T>*> BTree<T>::minRecursive(Node<T>* node, Node<T>* parent, Node<T>* minNode) noexcept{
	if (node->left == nullptr && node->right == nullptr) {
		if (node->data < minNode->data) {
			minNode = node;
		}
		return std::make_pair(minNode, parent);
	}

	if (node->left != nullptr) {
		auto result = minRecursive(node->left, node, minNode);
		if (result.first->data < minNode->data) {
			minNode = result.first;
			parent = result.second;
		}
	}

	if (node->right != nullptr) {
		auto result = minRecursive(node->right, node, minNode);
		if (result.first->data < minNode->data) {
			minNode = result.first;
			parent = result.second;
		}
	}

	if (node->data < minNode->data) {
		minNode = node;
	}
	return std::make_pair(minNode, parent);
}

template<typename T>
[[nodiscard]] std::optional<std::pair<Node<T>*, Node<T>*>> BTree<T>::min() noexcept {
	if (empty()) return std::nullopt;
	if (!empty() && root->left == nullptr && root->right == nullptr) {
		return std::make_optional(std::make_pair(root, nullptr));
	}
	auto [minNode, parent] = minRecursive(root, nullptr, root); // I am using here structured bindings
	return std::make_optional(std::make_pair(minNode, parent));
}

template<typename T>
[[nodiscard]] std::pair<Node<T>*, Node<T>*> BTree<T>::maxRecursive(Node<T>* node, Node<T>* parent, Node<T>* maxNode) noexcept{
	if (node->left == nullptr && node->right == nullptr) {
		if (node->data > maxNode->data) {
			maxNode = node;
		}
		return std::make_pair(maxNode, parent);
	}

	if (node->left != nullptr) {
		auto result = maxRecursive(node->left, node, maxNode);
		if (result.first->data > maxNode->data && node->data < result.first->data ) {
			maxNode = result.first;
			parent = node;
		}
	}
	
	if (node->right != nullptr) {
		auto result = maxRecursive(node->right, node, maxNode);
		if (result.first->data > maxNode->data && node->data < result.first->data) {
			maxNode = result.first;
			parent = node;
		}
	}

	if (node->data > maxNode->data) {
		maxNode = node;
	}
	return std::make_pair(maxNode, parent);
}

template<typename T>
[[nodiscard]] std::optional<std::pair<Node<T>*, Node<T>*>> BTree<T>::max() noexcept {
	if (empty()) return std::nullopt;
	if (!empty() && root->left == nullptr && root->right == nullptr) {
		return std::make_optional(std::make_pair(root, nullptr));
	}
	auto [maxNode, parent] = maxRecursive(root, nullptr, root); // I am using here structured bindings
	return std::make_optional(std::make_pair(maxNode, parent));
}

template<typename T>
[[nodiscard]] int BTree<T>::getHeightRecursive(Node<T>* node) const noexcept {
	if (node == nullptr) return 0;
	return 1 + std::max(getHeightRecursive(node->left), getHeightRecursive(node->right));
	// Key for deep understanding:
	// Firstly we diving into the last level 
	// For calculating D we calculated 2 nullptr nodes, we have got 0
	// Let's add that 1; Result D is 1, for E would be absolutely the same 
	// Important thing in B we are decading what biggest left or right sub-tree add + B, so B returns 2
}

//       A
//     /   \
//    B     C
//   / \     \
//  D   E     F
//            /
//           G

template<typename T>
[[nodiscard]] int BTree<T>::getHeight() const noexcept {
	if (empty()) return 0;
	if (!empty() && root->left == nullptr && root->right == nullptr) return 1;
	return result = getHeightRecursive(root);
}



// Complete list of methods:

//++ 1. insert( const T& )		
// noexcept, RAII, deep copy
// 
//++ 2. insert( T&& )	
// 	T&&, std::move, perfect forwarding, noexcept
// 
//+ 3. contains( const T& )  
// [[nodiscard]], structure bindings, auto, std::optional<Node*>
// 
//+ 4. remove( const T& )   
// std::pair, structured bindings, RAII, noexcept
// 
//++ 5. clear()		
// 	RAII	
// 
//++ 6. size() const
// 	[[nodiscard]]
// 		
//++ 7. empty() const
//	[[nodiscard]], noexcept	



//++ 8. min()
// std::optional<T>, structured bindings
// 
// 9.++ max()	
// std::optional<T>, structured bindings
// 		
// 10.
// ++height()		
// 11.
// printInOrder()
// lambda, std::function, traverse(lambda)
// 
// 12.
// printPreOrder()
// lambda, std::function, traverse(lambda)
// 			
// 13.
// begin()
// range-for, custom iterator, std::iterator_traits, std::move_iterator
// 
// 14.
// end()
// range-for, custom iterator, std::iterator_traits, std::move_iterator
// 
// 15.			
// emplace(args...)
// variadic templates, std::forward, T&&, emplace
// 			
// 16.
// operator==
// SFINAE, constexpr, std::tie
// 
// 17.
// operator!=
// SFINAE, constexpr, std::tie	




// 18.
// traverse(λ)	
// std::function, lambda, std::bind, concepts(C++20)
// 
// 19.			
// balance()
// to_vector + from_sorted_vector, std::sort, constexpr
// 				
// 20.
// copy()	
// deep copy, clone_subtree
// 
// 21.				
// clone_subtree(Node*)	
// RAII, move	
// 
// 22.
// node_count()
// constexpr, fold expressions
// 
// 23.
// leaf_count()	
// constexpr, fold expressions
// 			
// 24.
// is_balanced()
// std::pair, structured bindings	
// 		
// 25.
// to_vector()	
// std::vector<T>, inorder traversal, emplace_back
// 			
// 26.
// from_vector( const std::vector<T>& )
//	recursive mid-point, std::vector::at, constexpr						
