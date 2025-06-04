#pragma once
#include "node.h"


template<typename T>
class Iterator
{
public:
    Iterator(Node<T>* node, Node<T>* head) : ptr(node), headptr(head) {}
    ~Iterator() {}

    void operator++();
    void operator--();

    bool operator!=(const Iterator<T>& other) const;
    bool operator==(const Iterator<T>& other) const;

    T& operator*();		 // we are returning the address of that type of data we want to change

private:
    Node<T>* ptr;
    Node<T>* headptr;
};

template<typename T>
void Iterator<T>::operator++() {
    if (ptr == nullptr || ptr->next == headptr) {
        ptr = nullptr;
    }else {
        ptr = ptr->next;
    }
}

template<typename T>
void Iterator<T>::operator--() {
    if (ptr != nullptr) {
        ptr = ptr->prev;
    }
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator<T>& other) const{ // When i write it1 != it2 So m compiler see it like it1.operator!=(it2)
    return this->ptr != other.ptr;
}

template<typename T>
bool Iterator<T>::operator==(const Iterator<T>& other) const{
    return this->ptr == other.ptr;
}

template<typename T>
T& Iterator<T>::operator*() {
    return ptr->data;
}


