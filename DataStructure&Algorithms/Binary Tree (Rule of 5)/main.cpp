#pragma once

#include "BTree.hpp"
#include "Iterator.hpp"
#include "Person.h"

#include <iostream>
#include <iterator> // For std::iterator_traits , std::move_iterator
#include <typeinfo> // For typeid(...)
#include <algorithm> // For std::copy , std::copy_if, std::transform, std::unique_copy
#include <vector>

using Traits = std::iterator_traits<Iterator<int>>;

int main() {
	std::cout << "Binary Tree" << "\n";

	BTree<int> my_tree;
	BTree<int> my_tree2;
	BTree<int> my_tree3;
	BTree<Person> people;

	Person p1;
	Person p2(2,"Myla", 28);

	p1.age = 20;
	p1.id = 1;
	p1.name = "Alisa";

	const int data = 7;

	my_tree.insert(3);
	my_tree.insert(data);
	my_tree.insert(100);
	my_tree.insert(59);
	my_tree.insert(5);
	my_tree.insert(19);
	my_tree.insert(0);	
	my_tree.insert(-199);
	my_tree.insert(23);

	people.insert(p1);
	// WIth variadic templates and fold exprasions possible becomes
	people.emplace(3, "Liuda", 20);
	

	Iterator<int> it = my_tree.begin();
	Iterator<int> it2 = my_tree.begin();

	Iterator<int> end = my_tree.end();

	while (it != end) {
		std::cout << *it << " ";
		++it;

		auto temp = it2++; // temp saves old from post-increment
		std::cout << *temp << " " << *it2 << " ";
	}

	// std::iterator_traits : all that has are aliases no other functions no at least one
	std::cout << typeid(Traits::value_type).name() << "\n";
	std::cout << typeid(Traits::reference).name() << "\n";
	std::cout << typeid(Traits::pointer).name() << "\n";
	std::cout << typeid(Traits::difference_type).name() << "\n";
	std::cout << typeid(Traits::iterator_category).name() << "\n";
	// typeid(type): accept parameter(type) and returns std::type_info
	// .name(): is a method of class std::type_info and returns a string with name of the type

	if (typeid(Traits::reference) == typeid(Traits::pointer)) {
		std::cout << "False: it should be different!" << "\n";
	}

	// std::move_iterator
	std::copy(my_tree.begin(), my_tree.end(), std::back_inserter(my_tree2)); // data just copied

	std::cout << "After copy: my_tree[0]" << *my_tree.begin() << "\n";

	std::copy(std::make_move_iterator(it),
		std::make_move_iterator(end),
		std::back_inserter(my_tree3));

	std::cout << "After move: my_tree[0] = " << my_tree.begin() << "\n";


	std::vector<int> positives;
	std::copy_if(
		my_tree.begin(),
		my_tree.end(),
		std::back_inserter(positives),
		[](int x) { return x > 0; }
	);
	std::cout << "Positives: ";
	for (int x : positives) {
		std::cout << x << " ";
	}
	std::cout << "\n";


	std::vector<int> fourx;
	std::transform(
		my_tree.begin(),
		my_tree.end(),
		std::back_inserter(fourx),
		[](int x) {return x * 4; }
	);
	std::cout << "4x: ";
	for (int x : fourx) {
		std::cout << x << " ";
	}
	std::cout << "\n";


	std::vector<int> unique_values;
	std::unique_copy(
		my_tree.begin(),
		my_tree.end(),
		std::back_inserter(unique_values)
	);
	std::cout << "Unique values: ";
	for (int x : unique_values) {
		std::cout << x << " ";
	}
	std::cout << "\n";
}


