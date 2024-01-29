#pragma once
#include <iostream>
#include <string>
using namespace std;

class MaxHeap {

public:
    MaxHeap();

    int heap_size;
    int capacity;
    
    void maxHeapProp(/*your heap array*/);
    void insertKey(string sen);
    void deleteMax();
    string printHeap();
    /////////////////////////////////////////////////////////
    //////  TODO: Add Public members if required ///////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

private:
    string heap[1000];
    void maxHeapify(int i){
        int left = 2*i;
    int right = 2*i + 1;
    int largest = i;

    if (left <= heap_size && heap[left] > heap[largest]) {
        largest = left;
    }

    if (right <= heap_size && heap[right] > heap[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(heap[i], heap[largest]);
        maxHeapify(largest);
    }
    }

};

