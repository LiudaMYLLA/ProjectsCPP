#include "Deque.h"
#include <iostream>

int main() {
	Deque<int> q;
	q.addBack(5);
	q.addFront(0);
	q.addFront(1);
	q.addBack(9);
	q.isEmpty();
	q.peekBack();
	q.display();
}