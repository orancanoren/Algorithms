#include <iostream>
#include <chrono>
#include <vector>
#include <stdlib.h>

#define _DEBUG

using namespace std;

int medianOfThree(vector<int> & arr, int low, int high) {
    int mid = (low + high)/2;
    if (arr[high] > arr[low]) swap(arr[low], arr[high]);
    if (arr[mid] < arr[low]) swap(arr[mid], arr[high]);
    if (arr[high] < arr[mid]) swap(arr[high], arr[mid]);
    return mid;
}

int partition(vector<int> & arr, int low, int high) {
    // get pivot
    int pivotIndex = medianOfThree(arr, 0, high), pivot = arr[pivotIndex];
    swap(arr[pivotIndex], arr[high]);
    // partition the array
    int lowIter = low, highIter = high-1; // do not iterate over pivot (highIndex)
    while (highIter > lowIter) {
		bool lowStopped = false, highStopped = false;
        if (arr[lowIter] <= pivot) {
            lowIter++;
        }
		else lowStopped = true;
        if (arr[highIter] >= pivot) {
            highIter--;
        }
		else highStopped = true;
        if (lowStopped && highStopped) {
            swap(arr[lowIter], arr[highIter]);
			lowIter++;
			highIter++;
			lowStopped = false;
			highStopped = false;
        }
    }
    swap(arr[lowIter], arr[high-1]);
    return lowIter;
}

void qsort(vector<int> & arr, int low, int high) {
    if (high > low) {
        int mid = (low+high)/2;
        // partiton
        partition(arr, low, high);
        // recursive call to lower half
        qsort(arr, low, mid);
        // recuresive call to greater half
        qsort(arr, mid+1, high);
    }
}

vector<int> * generateRandArr(int size) {
    vector<int> * vec = new vector<int>(size);
#ifdef _DEBUG
    cout << "Allocating " << size*sizeof(int) << " bytes" << endl
         << "Randomizing array" << endl;
#endif
    auto begin = chrono::high_resolution_clock::now();
    auto iter = vec -> begin();
    for (int i = 0; i < size; i++, iter++) {
        *iter = rand();
    }
    auto end = chrono::high_resolution_clock::now();
#ifdef _DEBUG
    cout << "Array randomized in " << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << " ms" << endl;
#endif
    return vec;
}

bool isSorted(vector<int> & arr) {
    auto pre = arr.begin(), cur = arr.begin()++;
    for (int i = 0; i < arr.size()-1; i++, pre++, cur++) {
        if (*pre > *cur) return false;
    }
    return true;
}

int main() {
    srand(17);
    cout << "----------" << endl
         << "QuickSort" << endl
         << "----------" << endl
         << "Enter the size for array" << endl
         << ">> ";
    int size;
    cin >> size;
    vector<int> randArr = *generateRandArr(size);
    
    auto begin = chrono::high_resolution_clock::now();
    cout << "Sorting the array" << endl;
    qsort(randArr, 0, randArr.size()-1);
    auto end = chrono::high_resolution_clock::now();
    cout << "Array is " << (isSorted(randArr) ? "" : "not ") << "sorted in " << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << " ms" << endl;
    return 0;
}
