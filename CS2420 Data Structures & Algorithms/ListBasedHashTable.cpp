// Copyright 2017, Bradley Peterson, Weber State University, all rights reserved.
#include <iostream>
#include <map>
#include <list>
#include <string>
#include <sstream>

#ifndef __GNUC__
#include <conio.h>
#else
#include <cstdio>
#endif

using std::cout;
using std::endl;
using std::list;
using std::move;
using std::string;
using std::stringstream;

//************************************************************************
// A class to track memory allocation for testing purposes.
//************************************************************************
class ManageMemory {
public:
    static std::size_t getTotalSize() {
        std::size_t total = 0;
        for (auto &pair : mapOfAllocations) {
            total += pair.second;
        }
        return total;
    }

    void *operator new(std::size_t size) {
        void *ptr = ::operator new(size);
        mapOfAllocations[ptr] = size;
        return ptr;
    }

    void *operator new[](std::size_t size) {
        void *ptr = ::operator new[](size);
        mapOfAllocations[ptr] = size;
        return ptr;
    }

    void operator delete(void *ptr) {
        mapOfAllocations.erase(ptr);
        ::operator delete(ptr);
    }

    void operator delete[](void *ptr) {
        mapOfAllocations.erase(ptr);
        ::operator delete[](ptr);
    }

private:
    static std::map<void *, std::size_t> mapOfAllocations;
};

std::map<void *, std::size_t> ManageMemory::mapOfAllocations;

//************************************************************************
// A simple product class for demonstration.
//************************************************************************
class Product {
public:
    void setCost(int cost) { this->cost = cost; }
    void setName(const string &name) { this->name = name; }
    string getName() const { return name; }
    int getCost() const { return cost; }
    string getAllInfo() const {
        stringstream ss;
        ss << "Name: " << name << ", Cost: " << cost;
        return ss.str();
    }

private:
    string name;
    int cost;
};

//************************************************************************
// KeyValuePair class template
//************************************************************************
template <typename T>
class KeyValuePair {
public:
    KeyValuePair() = default;
    KeyValuePair(const string &key, const T &value) : key(key), value(value) {}
    KeyValuePair(const string &key, T &&value) : key(key), value(move(value)) {}

    string key;
    T value;
};

//************************************************************************
// HashTable class template
//************************************************************************
template <typename T>
class HashTable : public ManageMemory {
public:
    static const unsigned int NUM_BUCKETS = 100000;

    HashTable() { arr = new list<KeyValuePair<T>>[NUM_BUCKETS]; }
    ~HashTable() { delete[] arr; }

    // Move assignment operator
    HashTable &operator=(HashTable &&obj) {
        if (this != &obj) {
            delete[] arr;
            arr = obj.arr;
            obj.arr = nullptr;
        }
        return *this;
    }

    void create(const string &key, const T &item) {
        arr[hash(key)].emplace_back(key, item);
    }

    void create(const string &key, T &&item) {
        arr[hash(key)].emplace_back(key, move(item));
    }

    T retrieve(const string &key) const {
        for (const auto &pair : arr[hash(key)]) {
            if (pair.key == key) {
                return pair.value;
            }
        }
        throw std::out_of_range("Key not found");
    }

    T &operator[](const string &key) {
        for (auto &pair : arr[hash(key)]) {
            if (pair.key == key) {
                return pair.value;
            }
        }
        throw std::out_of_range("Key not found");
    }

    bool exists(const string &key) const {
        for (const auto &pair : arr[hash(key)]) {
            if (pair.key == key) {
                return true;
            }
        }
        return false;
    }

    void remove(const string &key) {
        auto &bucket = arr[hash(key)];
        for (auto iter = bucket.begin(); iter != bucket.end(); ++iter) {
            if (iter->key == key) {
                bucket.erase(iter);
                return;
            }
        }
    }

    unsigned int getTotalCount() const {
        unsigned int count = 0;
        for (unsigned int i = 0; i < NUM_BUCKETS; ++i) {
            count += arr[i].size();
        }
        return count;
    }

    unsigned int getWorstClump() const {
        unsigned int worst = 0;
        for (unsigned int i = 0; i < NUM_BUCKETS; ++i) {
            if (arr[i].size() > worst) {
                worst = arr[i].size();
            }
        }
        return worst;
    }

private:
    int hash(const string &key) const {
        int hashValue = 0;
        for (char ch : key) {
            hashValue = (13 * hashValue + ch) % NUM_BUCKETS;
        }
        return hashValue;
    }

    list<KeyValuePair<T>> *arr;
};

//************************************************************************
// Helper functions for testing
//************************************************************************
template <typename T>
string NumberToString(T number) {
    stringstream ss;
    ss << number;
    return ss.str();
}

bool checkTest(string testName, string expected, string actual) {
    if (expected == actual) {
        cout << "Passed " << testName << endl;
        return true;
    } else {
        cout << "***Failed test " << testName << " ***\n"
             << "Expected: " << expected << "\nActual: " << actual << endl;
        return false;
    }
}

bool checkTest(string testName, int expected, int actual) {
    if (expected == actual) {
        cout << "Passed " << testName << endl;
        return true;
    } else {
        cout << "***Failed test " << testName << " ***\n"
             << "Expected: " << expected << "\nActual: " << actual << endl;
        return false;
    }
}

bool checkEmpty(string testName, string value) {
    if (!value.empty()) {
        cout << "Passed " << testName << ", value: " << value << endl;
        return true;
    } else {
        cout << "***Failed test " << testName << ", value is empty!" << endl;
        return false;
    }
}

//************************************************************************
// Test functions
//************************************************************************
void testSimpleIntHash() {
    HashTable<string> myHash;
    myHash.create("6", "Jazz");
    checkTest("testSimpleIntHash #1", "Jazz", myHash.retrieve("6"));
    myHash["6"] = "Nuggets";
    checkTest("testSimpleIntHash #3", "Nuggets", myHash["6"]);
    checkTest("testSimpleIntHash #4", 1, myHash.exists("6"));
    myHash.remove("6");
    checkTest("testSimpleIntHash #6", 0, myHash.exists("6"));
}

void pressAnyKeyToContinue() {
    cout << "Press any key to continue...";
#ifndef __GNUC__
    _getch();
#else
    int c;
    fflush(stdout);
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
#endif
    cout << endl;
}

//************************************************************************
// Main
//************************************************************************
int main() {
    testSimpleIntHash();
    checkTest("Memory Leak Test", 0, ManageMemory::getTotalSize());
    pressAnyKeyToContinue();
    return 0;
}
