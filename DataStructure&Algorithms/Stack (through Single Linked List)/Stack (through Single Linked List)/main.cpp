#include "stack.h"
#include <iostream>


int main() {
	Stack<int> s;
	s.push(6);
	s.push(7);
	s.push(1);
	s.push(0);
	s.display();
	s.displayMin();
	s.pop();
	s.display();
	s.displayMin();
	return 0;
}