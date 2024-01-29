#include "sort.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>


sortAlg::sortAlg() {
    arr_size = 0;
    arr = new int[100]; // Each test case will be less than 100 values
    temp = new int[100]; // Each test case will be less than 100 values
}

using namespace std;

void sortAlg::printArray(ofstream &fout) {
    string answer;
    for (int i = 0; i < arr_size - 1; i++)
        answer += to_string(arr[i]) + " ";
    answer += to_string(arr[arr_size - 1]);
    fout << answer << endl;
}

void sortAlg::insertionSort(ofstream &fout) {
    static int start_index = 1;

    for (int i = start_index; i < arr_size; i++) {
        int curr = arr[i];
        int j = i - 1;

        while(j >= 0 && arr[j] > curr) {
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = curr;

        // always print the array after each inserted element is sorted
        printArray(fout);
    }
    start_index = arr_size; // update the start_index
}
// 고쳐야돼


void sortAlg::merge(int left, int right, int &count) {
    int mid = (left + right) / 2;
    int i = left;
    int j = mid + 1;
    int k = left;
    while (i <= mid && j <= right) {
        if (arr[j] < arr[i]) {
            temp[k] = arr[j];
            count ++; // count the number of drop
            j++;
        } 
        else {
            temp[k] = arr[i];
            i++;
        }
        k++;
    }
    while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }
    while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
    }
    for (int i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}



void sortAlg::mergeSort(ofstream &fout, int left, int right, int &count) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(fout, left, mid, count);
        mergeSort(fout, mid + 1, right, count);
        merge(left, right, count);
        
        printArray(fout);
    }
}
