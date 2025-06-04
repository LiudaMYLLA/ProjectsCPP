#include <string>
#include "node.h"
#include "iterator.h"
#include <QDebug>

using Integer = int;
using String = std::string;

template<typename T>
class cdll {
private:
    friend class Iterator<T>;
private:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
public:
    cdll(){}
    cdll(cdll<T>&& other);
    void addAtTheBeginning(T data);
    void addAtTheEnd(T data);
    void addAtThePosition(T data, Integer pos);

    void deleteFromPosition(Integer pos); // l want to use recursion here in learning goals
    void deleteAll();

    void printAllInBackOrder() const;
    bool IsContainsValue(T data) const;
    ~cdll();

    cdll<T>& operator=(cdll<T>&& other);
    Node<T>* getHead() const;
    Node<T>* getTail() const;
    Iterator<T> begin() const;
    Iterator<T> end() const;
private:
    bool IsContainsValueRecursive(T data, Node<T>* ptr, Integer i) const;
    void deleteAllRecursive(Node<T>* ptr, Integer i);
    void addAtThePositionRecursive(T data, Integer pos, Node<T>* ptr, Integer i); // l want to use recursion here in learning goals
    void deleteFromPositionRecursive(Integer pos, Node<T>* ptr, Integer i);
    void printAllRecursive(Node<T>* ptr, Integer i) const;
};

template<typename T>
cdll<T>& cdll<T>::operator=(cdll<T>&& other) {
    if (this != other) {
        deleteAll();
        this->head = other.head;
        this->tail = other.tail;
        other.head = nullptr;
        other.tail = nullptr;
    }
    return *this;
}

template<typename T>
cdll<T>::cdll(cdll<T>&& other) { // move-constructor we are creating during creating an object
    this->head = other.head;
    this->tail = other.tail;

    other.head = nullptr;
    other.tail = nullptr;
}

template<typename T>
void cdll<T>::addAtTheBeginning(T data) {
    static_assert(
        std::is_same<T, Integer>::value ||
            std::is_same<T, double>::value ||
            std::is_same<T, String>::value,
        "Type is incorrect! Try again!!"
        );
    Node<T>* newNode = new Node<T>(data);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        newNode->prev = newNode;
        newNode->next = newNode;
        return;
    }

    newNode->next = head;
    newNode->prev = tail;
    tail->next = newNode;
    head->prev = newNode;

    head = newNode;
}

template<typename T>
void cdll<T>::addAtTheEnd(T data) {
    static_assert(
        std::is_same<T, Integer>::value ||
            std::is_same<T, double>::value ||
            std::is_same<T, String>::value,
        "The type is incorrect!"
        );
    Node<T>* newNode = new Node<T>(data);
    if (tail == nullptr) {
        head = newNode;
        tail = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
        return;
    }
    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = head;
    head->prev = newNode;
    tail = newNode;
}


template<typename T>
void cdll<T>::addAtThePosition(T data, Integer pos) {
    if (!head) {
        Node<T>* newNode = new Node<T>(data);
        head = tail = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
        return;
    }

    addAtThePositionRecursive(data, pos, head, 0);
}

template<typename T>
void cdll<T>::addAtThePositionRecursive(T data, Integer pos, Node<T>* ptr, Integer i) {
    static_assert(
        std::is_same<T, Integer>::value ||
            std::is_same<T, double>::value ||
            std::is_same<T, String>::value,
        "The type is incorrect!"
        );

    if (ptr == head && i != 0) {
        qDebug() << "Position out of bounds!\n";
        return;
    }

    if (pos == i) { // definition for ending recursion
        Node<T>* newNode = new Node<T>(data);

        if (head == ptr) { // insertion at the beginning
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;

            head = newNode;
            return;
        }
        if (tail == ptr) { // insertion at the end
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
            tail = newNode;
            return;
        }

        Node<T>* prevNode = ptr->prev;

        ptr->prev = newNode;
        newNode->next = ptr;

        newNode->prev = prevNode;
        prevNode->next = newNode;
        return;
    }
    addAtThePositionRecursive(data, pos, ptr->next, i + 1);
}


template<typename T>
void cdll<T>::deleteFromPosition(Integer pos) {
    if (!head) {
        return;
    }

    deleteFromPositionRecursive(pos, head, 0);
}

template<typename T>
void cdll<T>::deleteFromPositionRecursive(Integer pos, Node<T>* ptr, Integer i) {

    if (ptr == head && i != 0) {
        qDebug() << "Position is invalid!" << "\n";
        return;
    }

    if (pos == i) {
        if (head == tail) {
            head->next = nullptr;
            head->prev = nullptr;
            delete head;
            head = tail = nullptr;
            return;
        }

        if (ptr == head) {
            Node<T>* nextNode = nullptr;
            nextNode = head->next;
            nextNode->prev = tail;
            tail->next = nextNode;
            delete head;
            head = nextNode;
            return;
        }

        if (ptr == tail) {
            Node<T>* prevNode = nullptr;
            prevNode = tail->prev;
            prevNode->next = head;
            head->prev = prevNode;
            delete tail;
            tail = prevNode;
            return;
        }

        Node<T>* next = nullptr;
        Node<T>* prev = nullptr;
        next = ptr->next;
        prev = ptr->prev;
        prev->next = next;
        next->prev = prev;
        delete ptr;
    }
    deleteFromPositionRecursive(pos, ptr->next, i + 1);
}

template<typename T>
void cdll<T>::deleteAll() {
    if (head == nullptr) { return; }

    deleteAllRecursive(head, 0);
}

template<typename T>
void cdll<T>::deleteAllRecursive(Node<T>* ptr, Integer i) {

    if (ptr == head && i > 0) {
        return;
    }

    if (ptr == tail) {
        delete ptr;
        head = tail = nullptr;
        qDebug() << i + 1 << "  elements were deleted!" << "\n";
        return;
    }

    deleteAllRecursive(ptr->next, i + 1);

    delete ptr;
}

template<typename T>
void cdll<T>::printAllInBackOrder() const  {
    if (head == nullptr) { return; }

    printAllRecursive(head, 0);
}

template<typename T>
void cdll<T>::printAllRecursive(Node<T>* ptr, Integer i) const {

    if (ptr == head && i > 0) {
        return;
    }
    if (ptr == tail) {
        qDebug() << ptr->data << "\n";
        return;
    }

    printAllRecursive(ptr->next, i + 1);

    qDebug() << ptr->data << "\n";
}


template<typename T>
bool cdll<T>::IsContainsValue(T data) const {
    if (head == nullptr) { return false; }
    return IsContainsValueRecursive(data, head, 0);
}

template<typename T>
bool cdll<T>::IsContainsValueRecursive(T data, Node<T>* ptr, Integer i) const {
    if (ptr == head && i > 0) { return false; }
    if (ptr->data == data) {
        return true;
    }
    return IsContainsValueRecursive(data, ptr->next, i + 1);
}

template<typename T>
Node<T>* cdll<T>::getHead() const { return head; }

template<typename T>
Node<T>* cdll<T>::getTail() const { return tail; }

template<typename T>
Iterator<T> cdll<T>::begin()const { return Iterator<T>(head, head); }

template<typename T>
Iterator<T> cdll<T>::end()const { return Iterator<T>(nullptr, head); }

template<typename T>
cdll<T>::~cdll() { deleteAll(); }

