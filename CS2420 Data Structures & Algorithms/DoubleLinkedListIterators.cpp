// Copyright 2017, Bradley Peterson, Weber State University, All rights reserved.
#include <iostream>
#include <map>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator> // For iterator traits

#ifndef __GNUC__
#include <conio.h> // For Windows users
#else
#include <stdio.h>
#endif

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;

//************************************************************************
// ManageMemory Class: To track memory allocations
//************************************************************************
class ManageMemory {
public:
    static std::size_t getTotalSize() {
        std::size_t total = 0;
        for (auto& alloc : mapOfAllocations) {
            total += alloc.second;
        }
        return total;
    }

    void* operator new(std::size_t size) {
        void* ptr = ::operator new(size);
        mapOfAllocations[ptr] = size;
        return ptr;
    }

    void* operator new[](std::size_t size) {
        void* ptr = ::operator new[](size);
        mapOfAllocations[ptr] = size;
        return ptr;
    }

    void operator delete(void* ptr) {
        mapOfAllocations.erase(ptr);
        ::operator delete(ptr);
    }

    void operator delete[](void* ptr) {
        mapOfAllocations.erase(ptr);
        ::operator delete[](ptr);
    }

private:
    static std::map<void*, std::size_t> mapOfAllocations;
};

std::map<void*, std::size_t> ManageMemory::mapOfAllocations;

//******************
// NodeType Class
//******************
template <typename T>
class NodeType : public ManageMemory {
public:
    T info;
    NodeType* forward{nullptr};
    NodeType* backward{nullptr};

    bool operator==(const NodeType& rhs) const {
        return (info == rhs.info &&
                forward == rhs.forward &&
                backward == rhs.backward);
    }
};

//******************
// Iterator Class
//******************
template <typename T>
class Iterator : public ManageMemory {
    friend class DoublyLinkedList<T>;

public:
    Iterator& operator++() { // Prefix increment
        if (offTheRightCliff) return *this;
        if (ptr->forward == nullptr) {
            offTheRightCliff = true;
        } else {
            ptr = ptr->forward;
        }
        return *this;
    }

    Iterator operator++(int) { // Postfix increment
        Iterator temp = *this;
        ++(*this);
        return temp;
    }

    Iterator& operator--() { // Prefix decrement
        if (offTheRightCliff) {
            offTheRightCliff = false;
        } else if (ptr != nullptr) {
            ptr = ptr->backward;
        }
        return *this;
    }

    bool operator==(const Iterator& rhs) const {
        return ptr == rhs.ptr && offTheRightCliff == rhs.offTheRightCliff;
    }

    bool operator!=(const Iterator& rhs) const {
        return !(*this == rhs);
    }

    T& operator*() {
        if (ptr == nullptr) throw std::runtime_error("Dereferencing a null pointer!");
        return ptr->info;
    }

private:
    NodeType<T>* ptr{nullptr};
    bool offTheRightCliff{false};
};

//****************************
// DoublyLinkedList Class
//****************************
template <typename T>
class DoublyLinkedList : public ManageMemory {
public:
    DoublyLinkedList() = default;
    ~DoublyLinkedList();

    void insertFirst(const T& info);
    void insertLast(const T& info);
    string getStringFromList() const;

    Iterator<T> begin();
    Iterator<T> end();

private:
    NodeType<T>* first{nullptr};
    NodeType<T>* last{nullptr};
    int count{0};
};

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (first != nullptr) {
        NodeType<T>* temp = first;
        first = first->forward;
        delete temp;
    }
}

template <typename T>
void DoublyLinkedList<T>::insertFirst(const T& info) {
    NodeType<T>* temp = new NodeType<T>();
    temp->info = info;

    if (first == nullptr) {
        last = temp;
    } else {
        temp->forward = first;
        first->backward = temp;
    }
    first = temp;
    ++count;
}

template <typename T>
void DoublyLinkedList<T>::insertLast(const T& info) {
    NodeType<T>* temp = new NodeType<T>();
    temp->info = info;

    if (first == nullptr) {
        first = temp;
    } else {
        last->forward = temp;
        temp->backward = last;
    }
    last = temp;
    ++count;
}

template <typename T>
string DoublyLinkedList<T>::getStringFromList() const {
    stringstream ss;
    if (first == nullptr) {
        ss << "The list is empty.";
    } else {
        NodeType<T>* current = first;
        while (current != nullptr) {
            ss << current->info << " ";
            current = current->forward;
        }
    }
    return ss.str();
}

template <typename T>
Iterator<T> DoublyLinkedList<T>::begin() {
    Iterator<T> iter;
    iter.ptr = first;
    return iter;
}

template <typename T>
Iterator<T> DoublyLinkedList<T>::end() {
    Iterator<T> iter;
    iter.offTheRightCliff = true;
    return iter;
}

//***********************************
// Custom Reverse Function
//***********************************
template <typename T>
void ourReverse(T begin, T end) {
    if (begin == end) return;
    --end;
    while (begin != end) {
        std::iter_swap(begin, end);
        ++begin;
        if (begin == end) break;
        --end;
    }
}

//***********************************
// Main Function for Testing
//***********************************
int main() {
    DoublyLinkedList<int> list;
    for (int i = 1; i <= 5; ++i) {
        list.insertLast(i);
    }

    cout << "Original list: " << list.getStringFromList() << endl;

    auto beginIter = list.begin();
    auto endIter = list.end();

    cout << "Reversing the list..." << endl;
    ourReverse(beginIter, endIter);

    cout << "Reversed list: " << list.getStringFromList() << endl;

    return 0;
}
