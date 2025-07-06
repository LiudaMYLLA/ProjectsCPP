#pragma once
 
template<typename T>
struct Node {
public:
	T data;
	Node* left = nullptr;
	Node* right = nullptr;

	Node(T data): data(data), left(nullptr), right(nullptr){}
};