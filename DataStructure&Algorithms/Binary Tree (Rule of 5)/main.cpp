#pragma once
#include <iostream>
#include "BTree.h"

int main() {
	std::cout << "Binary Tree" << "\n";
	BTree<int> my_tree;
	auto data = 7;
	my_tree.insert(3);
	my_tree.insert(data);
}
