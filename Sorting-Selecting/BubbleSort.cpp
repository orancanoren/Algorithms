#include <iostream>
#include <stdlib.h>
#include <chrono>
#define _DEBUG

using namespace std;

template <typename T>
class BubbleSort {
public:
	BubbleSort(T * input_array, int size);
	~BubbleSort();

	void sort();
	bool isSorted();
private:
	T * arr;
	int size;
};

template <typename T>
BubbleSort<T>::BubbleSort(T * input_array, int size) : arr(input_array), size(size) {
#ifdef _DEBUG
	cout << "BubbleSort constructor invoked" << endl;
#endif
}

template <typename T>
BubbleSort<T>::~BubbleSort() {
#ifdef _DEBUG
	cout << "BubbleSort destructor invoked" << endl;
#endif
}

template <typename T>
bool BubbleSort<T>::isSorted() {
	T * iter = &arr[0];
	for (int i = 0; i < size - 1; i++) {
		if (*iter > *(iter + 1)) return false;
	}
	return true;
}

template <typename T>
void BubbleSort<T>::sort() {
	// The loop invariant is that the array's last i items are sorted where i is the iteration count
	for (int right = size - 1; right > 0; right--) {
		T * iter = &arr[0]; // this pointer will iterate over the array
		for (int i = 0; i < right - 1; i++) {
			if (*iter > *(iter + 1)) {
				swap(*iter, *(iter + 1));
			}
		}
	}
}

int * generateIntArray(const int size) {
	srand(17);
	cout << "Allocating space of size " << size*sizeof(int) << " bytes" << endl;
	int * randArr = new int[size];
	if (randArr == nullptr) {
		cout << "Unable to allocate memory, terminating" << endl;
		exit(1);
	}
	cout << "Memory allocation complete" << endl
		<< "Randomizing the data" << endl;
	auto begin = chrono::high_resolution_clock::now();
	int * iter = &randArr[0];
	for (int i = 0; i < size; i++) {
		*iter = rand();
	}
	auto end = chrono::high_resolution_clock::now();
	cout << "Randomization complete in "
		<< chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << endl
		<< "-------------------------" << endl << endl;
	return randArr;
}

int main() {
	int size;
	cout << "-----------" << endl
		<< "Bubble Sort" << endl
		<< "------------" << endl
		<< "Enter the size of the data: " << endl
		<< ">> ";
	cin >> size;
	int * randArr = generateIntArray(size);
	BubbleSort<int> sortObj(randArr, size);
	cout << "Sorting data " << endl;
	auto begin = chrono::high_resolution_clock::now();
	sortObj.sort();
	auto end = chrono::high_resolution_clock::now();
	cout << "Operation completed in in " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << endl
		<< "Verifying the sorting operation" << endl;
	
	begin = chrono::high_resolution_clock::now();
	bool sorted = sortObj.isSorted();
	end = chrono::high_resolution_clock::now();
	cout << "The data is " << (sorted ? "" : "not ") << "sorted" << endl;
	return 0;
}
