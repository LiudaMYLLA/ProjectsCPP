#include <iostream>
#include <Tree.h>

int main() {
	std::cout << "Binary Tree" << "\n";
	Tree<int> my_tree;
	auto data = 7;
	my_tree.insert(3);
	my_tree.insert(data);
}