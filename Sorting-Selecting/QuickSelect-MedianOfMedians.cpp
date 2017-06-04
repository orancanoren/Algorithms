#include <iostream>
#include <chrono>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

#define _DEBUG

using namespace std;

int quickSelect(vector<int> &, int , int, int);

int median5(vector<int> & arr, int low, int high) {
	// Post condition: returns the index of the median of the sub list [low..high]

	// insertionSort the chunk
	for (int i = low; i < high-1; i++) {
		for (int j = i+1; j < high; j++) {
			if (arr[i] > arr[j]) swap(arr[i], arr[j]);
		}
	}
	// return the median of the sub-list
	return (low+high)/2;
}

int medianOfMedians(vector<int> & arr, int low, int high) {
	for (int i = low; i < high; i += 5) {
		int medianIndex = median5(arr, i, i+4);
		// accumulate the medians of each sub-list to the beginning of the sub-list
		swap(arr[medianIndex], arr[(i-low)/5]);
	}
	// compute the median of the n/5 medians
	return quickSelect(arr, low, ceil((high-low)/5)-1, low+(high-low)/10);
}

int partition(vector<int> & arr, int low, int high) {
	int pivotIndex = medianOfMedians(arr, low, high), pivot = arr[pivotIndex];
	swap(arr[pivotIndex], arr[high]);
	int left = low, right = high;
	while (right > left) {
		bool leftStopped = false, rightStopped = false;
		if (arr[left] >= pivot) {
			left++;
		} else leftStopped = true;
		if (arr[right] <= pivot) {
			right--;
		} else rightStopped = true;
		
		if (leftStopped && rightStopped) {
			swap(arr[left], arr[right]);
			left++;
			right++;
			leftStopped = false;
			rightStopped = false;
		}
	}
	return pivotIndex;
}

int quickSelect(vector<int> & arr, int low, int high, int order) {
	// get pivot
	int pivotIndex = partition(arr, low, high), pivot = arr[pivotIndex];
	if (pivotIndex == order) return pivotIndex;

	if (order > pivotIndex) {
		quickSelect(arr, low, pivotIndex, order);
	}
	else {
		quickSelect(arr, pivotIndex+1, high, order);
	}
	return pivotIndex;
}

bool verifySelection(vector<int> & arr, int order, int foundNumber) {
	sort(arr.begin(), arr.end());
	return arr[order] == foundNumber;
}

vector<int> * generateRandArr(int size) {
#ifdef _DEBUG
	cout << "Allocating " << sizeof(int)*size << " bytes" << endl;
#endif
	vector<int> * arr = new vector<int>(size);
#ifdef _DEBUG
	cout << "Randomizing the array" << endl;
#endif
	auto iter = arr -> begin();
	auto begin = chrono::high_resolution_clock::now();
	for (int i = 0; i < size; i++, iter++) {
		*iter = rand();
	}
	auto end = chrono::high_resolution_clock::now();
	cout << "Randomization complete in " << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << " ms" << endl;
	return arr;
}

int main() {
	srand(17);
	cout << "------------" << endl
		 << "Quick Select" << endl
		 << "------------" << endl
		 << "Enter the size of the array" << endl
		 << ">> ";
	int size;
	cin >> size;
	vector<int> randArr = *generateRandArr(size);
	cout << "Which order statistic would you like to find?" << endl
		 << ">> ";
	int order;
	cin >> order;
	try {
		if (order >= randArr.size()) throw "Order out of range";
		auto begin = chrono::high_resolution_clock::now();
		int number = quickSelect(randArr, 0, randArr.size()-1, order);
		auto end = chrono::high_resolution_clock::now();
		cout << "The " << order << " order statistic has been found in"
			<< chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << endl
			<< "Verifying the statistic" << endl;
		cout << "Verification resulted in a " << (verifySelection(randArr, order, number) ? "success" : "failure") << endl;
	}
	catch (const char & msg) {
		cout << "Error: " << msg;
		exit(1);
	}
	return 0;
}
