// Copyright 2017, Bradley Peterson, Weber State University, all rights reserved.
#include <cstdio>
#include <random>
#include <thread>
#include <mutex>
#include <iostream>
#include <vector>

#ifndef __GNUC__
#include <conio.h>
#else
#include <stdio.h>
#endif

using std::cout;
using std::endl;
using std::vector;

// Prototypes
void recQuickSort(unsigned long *arr, int first, int last);
void pressAnyKeyToContinue();
class BucketsCollection;

// Global variables
unsigned long *list;
int listSize;
int numBuckets;
int numThreads;
BucketsCollection *globalBuckets;
const unsigned long ULONGMAX = 4294967295;

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
    vector<vector<unsigned long>> arr;  // Array of vectors to represent buckets
    unsigned int numBuckets;           // Number of buckets
    unsigned long bucketRange;         // Range of values per bucket
};

// Implementation of BucketsCollection methods
BucketsCollection::BucketsCollection(const unsigned int numBuckets) 
    : numBuckets(numBuckets), arr(numBuckets), bucketRange(ULONGMAX / numBuckets) {}

BucketsCollection::~BucketsCollection() {}

void BucketsCollection::addItem(unsigned long item) {
    unsigned int bucketIndex = item / bucketRange;
    if (bucketIndex >= numBuckets) {
        bucketIndex = numBuckets - 1; // Handle edge case for ULONGMAX
    }
    arr[bucketIndex].push_back(item);
}

unsigned int BucketsCollection::getNumBuckets() const {
    return numBuckets;
}

unsigned int BucketsCollection::getNumItemsInABucket(const unsigned int bucket) const {
    if (bucket >= numBuckets) {
        throw std::out_of_range("Bucket index out of range");
    }
    return arr[bucket].size();
}

unsigned long *BucketsCollection::getBucketArray(const unsigned int bucket) {
    if (bucket >= numBuckets) {
        throw std::out_of_range("Bucket index out of range");
    }
    return arr[bucket].data();
}

void BucketsCollection::copyOneBucketsIntoAnotherBuckets(BucketsCollection &smallBucket) {
    for (unsigned int i = 0; i < numBuckets; ++i) {
        for (const auto &item : smallBucket.arr[i]) {
            arr[i].push_back(item);
        }
    }
}

void BucketsCollection::printAllBuckets() const {
    printf("******\n");
    for (unsigned int i = 0; i < numBuckets; ++i) {
        printf("Bucket number %d\n", i);
        for (const auto &item : arr[i]) {
            printf("%08X ", item);
        }
        printf("\n");
    }
    printf("\n");
}

// Functions for bucket sort
void placeIntoBuckets() {
    for (int i = 0; i < listSize; ++i) {
        globalBuckets->addItem(list[i]);
    }
}

void sortEachBucket() {
    for (unsigned int i = 0; i < globalBuckets->getNumBuckets(); ++i) {
        unsigned long *bucketArray = globalBuckets->getBucketArray(i);
        unsigned int size = globalBuckets->getNumItemsInABucket(i);
        recQuickSort(bucketArray, 0, size);
    }
}

void combineBuckets() {
    int index = 0;
    for (unsigned int i = 0; i < globalBuckets->getNumBuckets(); ++i) {
        unsigned long *bucketArray = globalBuckets->getBucketArray(i);
        unsigned int size = globalBuckets->getNumItemsInABucket(i);
        for (unsigned int j = 0; j < size; ++j) {
            list[index++] = bucketArray[j];
        }
    }
}

void bucketSort(bool displayOutput) {
    placeIntoBuckets();

    if (displayOutput) {
        printf("Displaying each bucket's contents before sorting:\n");
        globalBuckets->printAllBuckets();
    }

    sortEachBucket();

    if (displayOutput) {
        printf("Displaying each bucket's contents after sorting:\n");
        globalBuckets->printAllBuckets();
    }

    combineBuckets();

    if (displayOutput) {
        printf("Displaying what is hopefully a sorted array:\n");
        for (int i = 0; i < listSize; ++i) {
            printf("%08X ", list[i]);
        }
        printf("\n");
    }
}

// Other helper functions
void printList() {
    for (int i = 0; i < listSize; ++i) {
        printf("%08X ", list[i]);
    }
    printf("\n");
}

void createList() {
    list = new unsigned long[listSize];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned long> dis(0, ULONGMAX);

    for (int i = 0; i < listSize; ++i) {
        list[i] = dis(gen);
    }
}

void swap(unsigned long *arr, int first, int second) {
    unsigned long temp = arr[first];
    arr[first] = arr[second];
    arr[second] = temp;
}

int partition(unsigned long *arr, int first, int last) {
    unsigned long pivot = arr[first];
    int smallIndex = first;
    for (int index = first + 1; index < last; ++index) {
        if (arr[index] < pivot) {
            ++smallIndex;
            swap(arr, smallIndex, index);
        }
    }
    swap(arr, first, smallIndex);
    return smallIndex;
}

void recQuickSort(unsigned long *arr, int first, int last) {
    if (first < last) {
        int pivotLocation = partition(arr, first, last);
        recQuickSort(arr, first, pivotLocation);
        recQuickSort(arr, pivotLocation + 1, last);
    }
}

void verifySort(unsigned long *arr, unsigned int arraySize) {
    for (unsigned int i = 1; i < arraySize; ++i) {
        if (arr[i] < arr[i - 1]) {
            printf("ERROR, this list was not sorted correctly at index %d\n", i - 1);
            return;
        }
    }
    printf("PASSED SORT TEST - The list was sorted correctly\n");
}

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

// Main function
int main() {
    listSize = 100;
    numBuckets = 4;
    numThreads = 2;

    createList();
    globalBuckets = new BucketsCollection(numBuckets);
    printf("Starting bucket sort...\n");
    bucketSort(true);
    verifySort(list, listSize);
    delete globalBuckets;
    delete[] list;

    return 0;
}
