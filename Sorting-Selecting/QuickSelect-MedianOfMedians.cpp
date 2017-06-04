#include <iostream>
#include <chrono>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <algorithm> // std::sort [for selection verification]

#define _DEBUG

using namespace std;

int partition5(vector<int> & arr, int low, int high) {
	// Post-condition: returns the index of the median of the subgroup
	/*
	for (int i = low; i <= high; i++) {
		int iter = i;
		while (iter >= low && arr[iter] > arr[iter + 1]) {
			swap(arr[iter], arr[iter + 1]);
			iter--;
		}
	} */
	sort(arr.begin() + low, arr.begin() + high);
	return (low + high) / 2;
}

int medianOfMedians(vector<int> & arr, int low, int high) {
	if (high - low < 5) { // if there are 5 or fewer elements, compute the median directly
		return partition5(arr, low, high);
	}
	else {
		int medianLocator = 0;
		for (int i = low; i < high; i += 5) { // take subgroups of at most 5 elements
			int subgroupRight = i + 4 > high ? (i + 4) : high;
			int median5 = partition5(arr, i, subgroupRight);
			// accumulate subgroup medians at the beginning of the array
			swap(arr[median5], arr[medianLocator]);
			medianLocator++;
		}
		// we have the subgroup medians accumulated at the first <medianLocator> indexes,
		// recursively obtain the true median by finding the median of the subgroup medians
		return medianOfMedians(arr, 0, medianLocator);
	}
}

int partition(vector<int> & arr, int low, int high) {
	// Set up a uniformly distributed number generator
	int pivotIndex = medianOfMedians(arr, low, high);
	int pivot = arr[pivotIndex];

	swap(arr[pivotIndex], arr[high]); // relocate the pivot to the right end
	int left = low, right = high; // set left & right iterators
	bool leftStopped = false, rightStopped = false;
	while (right > left) {
		if (!leftStopped && arr[left] <= pivot) { // we want left of the pivot to contain numbers smaller than the pivot
			left++;
		}
		else leftStopped = true;
		if (!rightStopped && arr[right] >= pivot) { // we want right of the pivot to contain numbers greater than the pivot
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
	else {
		pivotIndex = left;
		if (right + 1 <= high) swap(arr[high], arr[right + 1]);
	}
	return pivotIndex;
}

int quickSelect(vector<int> & arr, int low, int high, int order) {
	// Parameters:  arr -> array to operate on
	//				low -> index of the left end of the subarray
	//				high -> index of the right end of the subarray
	//				order -> the rank of the item to be searched
	// Post-Condition: Returns the index of the requested order statistic

	int pivotIndex = partition(arr, low, high), pivot = arr[pivotIndex];

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
	auto iter = arr->begin();
	auto begin = chrono::high_resolution_clock::now();
	for (int i = 0; i < size; i++, iter++) {
		*iter = rand();
	}
	auto end = chrono::high_resolution_clock::now();
	cout << "Randomization complete in " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << endl;
	return arr;
}

int main() {
	srand(17);
	cout << "-------------------------" << endl
		<< "Quick Select (Median of Medians)" << endl
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
	order -= 1;
	try {
		if (order >= randArr.size()) throw "Order out of range";
		auto begin = chrono::high_resolution_clock::now();
		int number = randArr[quickSelect(randArr, 0, randArr.size() - 1, order)];
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