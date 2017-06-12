#include <iostream>
#include <chrono>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <algorithm> // std::sort [for selection verification]
#include <random>

using namespace std;

#define _DEBUG

int partition(vector<int> & arr, int low, int high) {
	// Set up a uniformly distributed number generator
	random_device rd;
	mt19937 randomNumGenerator(rd());
	uniform_int_distribution<int> uni(low, high);
	int pivotIndex = uni(randomNumGenerator);
	int pivot = arr[pivotIndex];

	swap(arr[pivotIndex], arr[high]); // relocate the pivot to the right end
	int left = low, right = high; // set left & right iterators
	bool leftStopped = false, rightStopped = false;
	while (right > left) {
		if (!leftStopped && arr[left] <= pivot) { // we want left of the pivot to contain numbers smaller or equal to the pivot
			left++;
		} 
		else leftStopped = true;
		if (!rightStopped && arr[right] >= pivot) { // we want right of the pivot to contain numbers greater or equal to the pivot
			right--;
		} 
		else rightStopped = true;
		
		if (leftStopped && rightStopped) { // when both iterators stopped, this means that we can finally swap the two
			swap(arr[left], arr[right]);
			left++;
			right--;
			leftStopped = false;
			rightStopped = false;
		}
	}
	// relocate the pivot to where it should be
	if (leftStopped) {
		pivotIndex = left;
		swap(arr[high], arr[pivotIndex]);
	} 
	else if (rightStopped) {
		pivotIndex = right + 1;
		swap(arr[high], arr[pivotIndex]);
	}
	else { // neither of them has stopped
		if (arr[left] > pivot) {
			pivotIndex = left;
		}
		else {
			pivotIndex = (left + 1) > high ? left : (left + 1);
		}
		swap(arr[pivotIndex], arr[high]);
	}
	return pivotIndex;
}

int quickSelect(vector<int> & arr, int low, int high, int order) {
	// Parameters:  arr -> array to operate on
	//				low -> index of the left end of the subarray
	//				high -> index of the right end of the subarray
	//				order -> the rank of the item to be searched
	// Post-Condition: Returns the index of the requested order statistic

	int pivotIndex = partition(arr, low, high);
	int pivot = arr[pivotIndex];

	if (pivotIndex == order) return pivotIndex;
	else if (order > pivotIndex) {
		return quickSelect(arr, pivotIndex + 1, high, order);
	}
	else {
		return quickSelect(arr, low, pivotIndex - 1, order);
	}
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
	cout << "-------------------------" << endl
		 << "Quick Select (Randomized)" << endl
		 << "-------------------------" << endl
		 << "Fun fact: This is a Las Vegas algorithm" << endl
		 << "-------------------------" << endl
		 << "Enter the size of the array" << endl
		 << ">> ";
	int size;
	cin >> size;
	vector<int> randArr = *generateRandArr(size);
	cout << "Which order statistic would you like to find?" << endl
		 << ">> ";
	int order;
	cin >> order;
	order -= 1; // order is now 0-based
	try {
		if (order >= randArr.size()) throw "Order out of range";
		auto begin = chrono::high_resolution_clock::now();
		int number = randArr[quickSelect(randArr, 0, randArr.size()-1, order)];
		auto end = chrono::high_resolution_clock::now();
		cout << "The " << order + 1 << "th order statistic has been found in "
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
