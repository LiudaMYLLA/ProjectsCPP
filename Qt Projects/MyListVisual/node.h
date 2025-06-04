#pragma once

template<typename T>
struct Node {
public:
    T data;
    Node<T>* prev = nullptr;
    Node<T>* next = nullptr;

    Node(){}
    ~Node(){}
    Node(T d) : data(d), prev(nullptr), next(nullptr){}
};
