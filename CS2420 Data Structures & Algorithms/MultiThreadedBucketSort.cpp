// Copyright 2017, Bradley Peterson, Weber State University, all rights reserved.

#include <cstdio>
#include <random>
#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <chrono>

#ifndef __GNUC__
#include <conio.h>
#else
#include <stdio.h>
#endif

using std::cout;
using std::endl;
using std::mutex;
using std::thread;
using std::vector;

//*** Prototypes ***
void recQuickSort(unsigned long *arr, int first, int last);
void pressAnyKeyToContinue();
class BucketsCollection;

//*** GLOBAL VARIABLES ***
unsigned long *list;
int listSize;
int numBuckets;
int numThreads;
BucketsCollection *globalBuckets;
const unsigned long ULONGMAX = 4294967295; // Maximum value for unsigned long
mutex mtx; // Mutex for thread synchronization

//**********************************
// BucketsCollection Class
//**********************************
class BucketsCollection {
public:
    BucketsCollection(const unsigned int numBuckets);
    ~BucketsCollection();

    void addItem(unsigned long item);
    unsigned int getNumBuckets() const;
    unsigned int getNumItemsInABucket(const unsigned int bucket) const;
    unsigned long *getBucketArray(const unsigned int bucket);
    void copyOneBucketsIntoAnotherBuckets(BucketsCollection &smallBucket);
    void printAllBuckets() const;

private:
    vector<unsigned long> *arr; // Array of vectors to hold bucket data
    unsigned int numBuckets;
    unsigned long bucketRange;
};

// Constructor
BucketsCollection::BucketsCollection(const unsigned int numBuckets) {
    this->numBuckets = (numBuckets > 1) ? numBuckets : 1;
    this->bucketRange = (ULONGMAX / this->numBuckets) + 1;
    this->arr = new vector<unsigned long>[this->numBuckets];
}

// Destructor
BucketsCollection::~BucketsCollection() {
    delete[] arr;
}

// Add item to the appropriate bucket
void BucketsCollection::addItem(unsigned long item) {
    arr[item / bucketRange].push_back(item);
}

// Get number of buckets
unsigned int BucketsCollection::getNumBuckets() const {
    return numBuckets;
}

// Get number of items in a specific bucket
unsigned int BucketsCollection::getNumItemsInABucket(const unsigned int bucket) const {
    return arr[bucket].size();
}

// Print all bucket contents
void BucketsCollection::printAllBuckets() const {
    printf("******\n");
    for (unsigned int i = 0; i < numBuckets; i++) {
        printf("\nBucket number %d\n", i);
        for (unsigned int j = 0; j < arr[i].size(); j++) {
            if (j % 10 == 0) {
                printf("\n");
            }
            printf("%08X ", arr[i][j]);
        }
        printf("\n");
    }
}

// Get the array of a specific bucket
unsigned long *BucketsCollection::getBucketArray(const unsigned int bucket) {
    return arr[bucket].data();
}

// Copy items from one BucketsCollection to another
void BucketsCollection::copyOneBucketsIntoAnotherBuckets(BucketsCollection &smallBucket) {
    std::lock_guard<mutex> lock(mtx);
    for (unsigned int i = 0; i < numBuckets; i++) {
        arr[i].insert(arr[i].end(), smallBucket.arr[i].begin(), smallBucket.arr[i].end());
    }
}

//**********************************
// Supporting Functions
//**********************************

// Print the list
void printList() {
    for (int i = 0; i < listSize; i++) {
        if (i % 10 == 0) {
            printf("\n");
        }
        printf("%08X ", list[i]);
    }
    printf("\n");
}

// Create a random list
void createList() {
    list = new unsigned long[listSize];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned long> dis(0, ULONGMAX);
    for (int i = 0; i < listSize; ++i) {
        list[i] = dis(gen);
    }
}

// Place items into buckets (for multithreading)
void placeIntoBuckets(int threadNum) {
    int range = listSize / numThreads;
    int startIndex = range * threadNum;
    int endIndex = (threadNum == numThreads - 1) ? listSize : range * (threadNum + 1);

    BucketsCollection localBuckets(numBuckets);
    for (int i = startIndex; i < endIndex; i++) {
        localBuckets.addItem(list[i]);
    }
    globalBuckets->copyOneBucketsIntoAnotherBuckets(localBuckets);
}

// Sort each bucket using quicksort
void sortEachBucket(int threadNum) {
    unsigned long *tempArr = globalBuckets->getBucketArray(threadNum);
    unsigned int size = globalBuckets->getNumItemsInABucket(threadNum);
    recQuickSort(tempArr, 0, size);
}

// Combine buckets back into the main list
void combineBuckets(int threadNum) {
    int startIndex = 0;
    for (int i = 0; i < threadNum; i++) {
        startIndex += globalBuckets->getNumItemsInABucket(i);
    }
    unsigned long *tempArr = globalBuckets->getBucketArray(threadNum);
    for (unsigned int i = 0; i < globalBuckets->getNumItemsInABucket(threadNum); i++) {
        list[startIndex + i] = tempArr[i];
    }
}

// Perform the bucket sort
void bucketSort(bool displayOutput) {
    vector<thread> threads;

    // Place items into buckets
    for (int i = 0; i < numThreads; i++) {
        threads.emplace_back(placeIntoBuckets, i);
    }
    for (auto &t : threads) t.join();
    threads.clear();

    if (displayOutput) {
        printf("Displaying each bucket's contents before sorting:\n");
        globalBuckets->printAllBuckets();
    }

    // Sort each bucket
    for (int i = 0; i < numThreads; i++) {
        threads.emplace_back(sortEachBucket, i);
    }
    for (auto &t : threads) t.join();
    threads.clear();

    // Combine buckets
    for (int i = 0; i < numThreads; i++) {
        threads.emplace_back(combineBuckets, i);
    }
    for (auto &t : threads) t.join();

    if (displayOutput) {
        printf("Displaying each bucket's contents after sorting:\n");
        globalBuckets->printAllBuckets();
        pressAnyKeyToContinue();
        printf("Displaying what is hopefully a sorted array:\n");
        printList();
    }
}

// Swap two elements
void swap(unsigned long *arr, int first, int second) {
    unsigned long temp = arr[first];
    arr[first] = arr[second];
    arr[second] = temp;
}

// Partition the array for quicksort
int partition(unsigned long *arr, int first, int last) {
    unsigned long pivot = arr[first];
    int smallIndex = first;
    for (int index = first + 1; index < last; index++) {
        if (arr[index] < pivot) {
            smallIndex++;
            swap(arr, smallIndex, index);
        }
    }
    swap(arr, first, smallIndex);
    return smallIndex;
}

// Recursive quicksort
void recQuickSort(unsigned long *arr, int first, int last) {
    if (first < last) {
        int pivotLocation = partition(arr, first, last);
        recQuickSort(arr, first, pivotLocation);
        recQuickSort(arr, pivotLocation + 1, last);
    }
}

// Verify if the list is sorted
void verifySort(unsigned long *arr, unsigned int arraySize) {
    for (unsigned int i = 1; i < arraySize; i++) {
        if (arr[i] < arr[i - 1]) {
            printf("ERROR: List not sorted at index %d\n", i);
            return;
        }
    }
    printf("PASSED SORT TEST - List is sorted correctly.\n");
}

// Wait for user input
void pressAnyKeyToContinue() {
    printf("Press any key to continue...\n");
#ifndef __GNUC__
    _getch();
#else
    int c;
    fflush(stdout);
    do {
        c = getchar();
    } while ((c != '\n') && (c != EOF));
#endif
}

// Main Function
int main() {
    listSize = 100;
    numBuckets = 2;
    numThreads = 2;
    createList();
    globalBuckets = new BucketsCollection(numBuckets);

    printf("Starting bucket sort (listSize = %d, numBuckets = %d, numThreads = %d)\n", listSize, numBuckets, numThreads);
    printList();
    pressAnyKeyToContinue();

    bucketSort(true);
    verifySort(list, listSize);
    delete globalBuckets;
    delete[] list;

    return 0;
}
