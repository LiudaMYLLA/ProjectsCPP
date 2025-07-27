#pragma once
#include <iostream>
#include "BTree.hpp"
#include "Iterator.hpp"

int main() {
	std::cout << "Binary Tree" << "\n";
	BTree<int> my_tree;
	const int data = 7;
	my_tree.insert(3);
	my_tree.insert(data);
	my_tree.insert(100);

	Iterator<int> it = my_tree.begin();
	Iterator<int> it2 = my_tree.begin();

	Iterator<int> end = my_tree.end();

	while (it != end) {
		std::cout << *it << " ";
		++it;

		auto temp = it2++; // temp saves old from post-increment
		std::cout << *temp << " " << *it2 << " ";
	}
}
