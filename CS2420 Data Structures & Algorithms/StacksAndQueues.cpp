// Copyright 2017, Bradley Peterson, Weber State University, All rights reserved.

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

#ifndef __GNUC__
#include <conio.h>
#else
#include <cstdio>
#endif

using std::cout;
using std::endl;
using std::string;

//**********************************
// CourseStack Class
//**********************************
template <typename T>
class CourseStack {
private:
    T *arr{nullptr};         // Pointer to hold stack data
    unsigned int capacity{0}; // Maximum stack size
    unsigned int currentSize{0}; // Current number of elements

public:
    CourseStack(const unsigned int capacity);
    ~CourseStack();
    void push(const T &data);
    T pop();
    unsigned int size() const;
};

// CourseStack Constructor
template <typename T>
CourseStack<T>::CourseStack(const unsigned int capacity) {
    arr = new T[capacity];
    this->capacity = capacity;
}

// CourseStack Destructor
template <typename T>
CourseStack<T>::~CourseStack() {
    delete[] arr;
}

// Push an element onto the stack
template <typename T>
void CourseStack<T>::push(const T &data) {
    if (currentSize >= capacity) {
        throw std::overflow_error("Stack overflow: cannot push onto a full stack.");
    }
    arr[currentSize++] = data;
}

// Pop an element from the stack
template <typename T>
T CourseStack<T>::pop() {
    if (currentSize == 0) {
        throw std::underflow_error("Stack underflow: cannot pop from an empty stack.");
    }
    return arr[--currentSize];
}

// Get the current size of the stack
template <typename T>
unsigned int CourseStack<T>::size() const {
    return currentSize;
}

//**********************************
// CourseQueue Class
//**********************************
template <typename T>
class CourseQueue {
private:
    T *arr{nullptr};         // Pointer to hold queue data
    unsigned int front{0};   // Index of front element
    unsigned int back{0};    // Index of next empty position
    unsigned int capacity{0}; // Maximum queue size
    unsigned int currentSize{0}; // Current number of elements

public:
    CourseQueue(const unsigned int capacity);
    ~CourseQueue();
    void push_back(const T &data);
    T pop_front();
    unsigned int size() const;
};

// CourseQueue Constructor
template <typename T>
CourseQueue<T>::CourseQueue(const unsigned int capacity) {
    arr = new T[capacity];
    this->capacity = capacity;
}

// CourseQueue Destructor
template <typename T>
CourseQueue<T>::~CourseQueue() {
    delete[] arr;
}

// Push an element to the back of the queue
template <typename T>
void CourseQueue<T>::push_back(const T &data) {
    if (currentSize == capacity) {
        throw std::overflow_error("Queue overflow: cannot push onto a full queue.");
    }
    arr[back] = data;
    back = (back + 1) % capacity; // Wrap around
    currentSize++;
}

// Pop an element from the front of the queue
template <typename T>
T CourseQueue<T>::pop_front() {
    if (currentSize == 0) {
        throw std::underflow_error("Queue underflow: cannot pop from an empty queue.");
    }
    T value = arr[front];
    front = (front + 1) % capacity; // Wrap around
    currentSize--;
    return value;
}

// Get the current size of the queue
template <typename T>
unsigned int CourseQueue<T>::size() const {
    return currentSize;
}

//**********************************
// Testing and Main Function
//**********************************

// This helps with testing, do not modify.
bool checkTest(string testName, int whatItShouldBe, int whatItIs) {
    if (whatItShouldBe == whatItIs) {
        cout << "Passed " << testName << endl;
        return true;
    } else {
        cout << "***Failed test " << testName << " *** " << endl
             << "    Output was " << whatItIs << endl
             << "    Output should have been " << whatItShouldBe << endl;
        return false;
    }
}

// This helps with testing, do not modify.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {
    if (whatItShouldBe == whatItIs) {
        cout << "Passed " << testName << endl;
        return true;
    } else {
        cout << "***Failed test " << testName << " *** " << endl
             << "    Output was " << whatItIs << endl
             << "    Output should have been " << whatItShouldBe << endl;
        return false;
    }
}

// Test CourseStack
void testCourseStack() {
    CourseStack<int> stack(5);
    stack.push(1);
    checkTest("testCourseStack #1", 1, stack.pop());
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    checkTest("testCourseStack #2", 5, stack.pop());
    checkTest("testCourseStack #3", 4, stack.pop());
    checkTest("testCourseStack #4", 3, stack.pop());
    checkTest("testCourseStack #5", 2, stack.pop());
    checkTest("testCourseStack #6", 1, stack.pop());

    // Test error handling
    try {
        stack.pop();
    } catch (const std::underflow_error &) {
        checkTest("testCourseStack #7", "caught", "caught");
    }

    stack.push(12);
    stack.push(32);
    checkTest("testCourseStack #9", 2, stack.size());
}

// Test CourseQueue
void testCourseQueue() {
    CourseQueue<string> queue(5);
    queue.push_back("penny");
    queue.push_back("nickel");
    queue.push_back("dime");
    queue.push_back("quarter");
    checkTest("testCourseQueue #1", 4, queue.size());
    checkTest("testCourseQueue #2", "penny", queue.pop_front());
    checkTest("testCourseQueue #3", 3, queue.size());
    checkTest("testCourseQueue #4", "nickel", queue.pop_front());
}

// Wait for user input
void pressAnyKeyToContinue() {
    cout << "Press any key to continue...";
#ifndef __GNUC__
    _getch();
#else
    int c;
    fflush(stdout);
    do
        c = getchar();
    while ((c != '\n') && (c != EOF));
#endif
    cout << endl;
}

int main() {
    testCourseStack();
    pressAnyKeyToContinue();
    testCourseQueue();
    pressAnyKeyToContinue();
    return 0;
}
