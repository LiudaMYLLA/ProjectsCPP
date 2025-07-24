#pragma once

template<typename T>
struct [[nodiscard]] Node {
public:
	T data;
	Node* left = nullptr;
	Node* right = nullptr;

	Node(T data) noexcept : data(data), left(nullptr), right(nullptr) {}
};
