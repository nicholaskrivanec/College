#ifndef __GNUC__
#include <conio.h> // For Windows systems
#else
#include <cstdio>  // For Linux/Mac systems
#endif

#include <sstream>
#include <map>
#include <chrono>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

//************************************************************************
// ManageMemory Class: To track memory allocations
//************************************************************************
class manageMemory {
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

std::map<void*, std::size_t> manageMemory::mapOfAllocations;

//******************
// NodeType Class
//******************
template <typename T>
class nodeType : public manageMemory {
public:
    T info;
    nodeType* link{nullptr};
};

//******************
// SinglyLinkedList Class
//******************
template <typename T>
class singlyLinkedList : public manageMemory {
public:
    singlyLinkedList();
    ~singlyLinkedList();

    void insertFirst(const T& value);
    void insertLast(const T& value);
    string getStringFromList() const;

    nodeType<T>* pointTo(unsigned int index);
    T getAtIndex(unsigned int index) const;
    T& operator[](unsigned int index);
    void insertAtIndex(unsigned int index, const T& value);
    void deleteAtIndex(unsigned int index);
    void deleteAllInstances(const T& value);

private:
    nodeType<T>* first{nullptr};
    nodeType<T>* last{nullptr};
    int count{0};
};

// Constructor
template <typename T>
singlyLinkedList<T>::singlyLinkedList() = default;

// Destructor
template <typename T>
singlyLinkedList<T>::~singlyLinkedList() {
    while (first) {
        nodeType<T>* temp = first;
        first = first->link;
        delete temp;
    }
}

// Insert value at the beginning of the list
template <typename T>
void singlyLinkedList<T>::insertFirst(const T& value) {
    nodeType<T>* temp = new nodeType<T>();
    temp->info = value;
    temp->link = first;
    first = temp;
    if (last == nullptr) {
        last = temp;
    }
    ++count;
}

// Insert value at the end of the list
template <typename T>
void singlyLinkedList<T>::insertLast(const T& value) {
    nodeType<T>* temp = new nodeType<T>();
    temp->info = value;
    if (last) {
        last->link = temp;
    } else {
        first = temp;
    }
    last = temp;
    ++count;
}

// Return string representation of the list
template <typename T>
string singlyLinkedList<T>::getStringFromList() const {
    stringstream ss;
    if (!first) {
        ss << "The list is empty.";
    } else {
        nodeType<T>* current = first;
        while (current) {
            ss << current->info << " ";
            current = current->link;
        }
    }
    return ss.str();
}

// Return a pointer to the node at the specified index
template <typename T>
nodeType<T>* singlyLinkedList<T>::pointTo(unsigned int index) {
    if (index >= count) {
        throw std::out_of_range("Index out of bounds");
    }

    nodeType<T>* ptr = first;
    for (unsigned int i = 0; i < index; ++i) {
        ptr = ptr->link;
    }
    return ptr;
}

// Get value at the specified index
template <typename T>
T singlyLinkedList<T>::getAtIndex(unsigned int index) const {
    return pointTo(index)->info;
}

// Overload operator[] to access value at the specified index
template <typename T>
T& singlyLinkedList<T>::operator[](unsigned int index) {
    return pointTo(index)->info;
}

// Insert value at the specified index
template <typename T>
void singlyLinkedList<T>::insertAtIndex(unsigned int index, const T& value) {
    if (index > count) {
        throw std::out_of_range("Index out of bounds");
    }

    if (index == 0) {
        insertFirst(value);
    } else if (index == count) {
        insertLast(value);
    } else {
        nodeType<T>* temp = new nodeType<T>();
        temp->info = value;
        temp->link = pointTo(index);
        pointTo(index - 1)->link = temp;
        ++count;
    }
}

// Delete the node at the specified index
template <typename T>
void singlyLinkedList<T>::deleteAtIndex(unsigned int index) {
    if (index >= count) {
        throw std::out_of_range("Index out of bounds");
    }

    nodeType<T>* temp = first;

    if (index == 0) {
        first = first->link;
        if (!first) {
            last = nullptr;
        }
    } else {
        nodeType<T>* prev = pointTo(index - 1);
        temp = prev->link;
        prev->link = temp->link;
        if (index == count - 1) {
            last = prev;
        }
    }

    delete temp;
    --count;
}

// Delete all nodes with the specified value
template <typename T>
void singlyLinkedList<T>::deleteAllInstances(const T& value) {
    while (first && first->info == value) {
        deleteAtIndex(0);
    }

    nodeType<T>* current = first;
    nodeType<T>* prev = nullptr;

    while (current) {
        if (current->info == value) {
            nodeType<T>* toDelete = current;
            prev->link = current->link;
            current = current->link;
            delete toDelete;
            --count;
        } else {
            prev = current;
            current = current->link;
        }
    }
}

//****************************
// Test Functions
//****************************

// Implement test functions here, similar to the original code...

//****************************
// Main Function
//****************************
int main() {
    singlyLinkedList<int> list;
    list.insertLast(1);
    list.insertLast(2);
    list.insertLast(3);
    list.insertLast(4);

    cout << "List before deleting all instances of 3: " << list.getStringFromList() << endl;

    list.deleteAllInstances(3);

    cout << "List after deleting all instances of 3: " << list.getStringFromList() << endl;

    return 0;
}
