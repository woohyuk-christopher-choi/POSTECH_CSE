#include "heap.h"
#include <iostream>
#include <string>

using namespace std;


MaxHeap::MaxHeap() {
    capacity = 1000;
    heap_size = 0;
}

string MaxHeap::printHeap(){
    string answer;
    for (int i = 1 ; i <= heap_size; i++){
        answer += heap[i];
        answer += " ";
    }
    return answer;
}

void MaxHeap::insertKey(string sen) {
    heap_size ++;
    int i = heap_size - 1;
    while (i != 0 && heap[(i-1)/2] < heap[i]){
        swap(heap[i] , heap[(i-1)/2]);
        i = (i-1)/2;
    }
    heap[i] = sen;
}


void MaxHeap::deleteMax() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////


    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void MaxHeap::maxHeapProp(/*your heap array*/) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here   /////////////

    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}