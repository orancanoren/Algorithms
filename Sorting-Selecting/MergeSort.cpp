#include <iostream>
#include <vector>
#include <stdlib.h> // srand(), rand()
#include <chrono>

using namespace std;

template <typename T>
bool isSorted(const vector<T> & arr) { 
	// Post condition: returns a boolean indicating whether the vector is sorted or not
	auto prev = arr.begin();
	auto cur = arr.begin(); cur++;

	for (;cur != arr.end(); cur++, prev++)
		if (*cur < *prev) return false;

	return true;
}

template <typename T>
vector<T> * generateVector() {
	int size;
	cout << "Please enter the size of the vector: " << endl
		 << ">> ";
	cin >> size;
	auto start_time = std::chrono::high_resolution_clock::now();
	vector<int> *randVector = new vector<int>(size);
	for (auto iter = randVector -> begin(); iter != randVector -> end(); iter++) {
		*iter = rand();
	}

	auto finish_time = std::chrono::high_resolution_clock::now();
	cout << "Vector of size " << randVector -> size() << " has been generated" << endl
		<< "Elapsed time for generating vector: " << chrono::duration_cast<chrono::milliseconds>(finish_time - start_time).count() << " ms" << endl;
	return randVector;
}

template <typename T>
void merge(vector<T> & arr, vector<T> & temp, int leftPos, int rightPos, int rightEnd) {
	// Post condition: merges appropriate positions of arr into temp in order to obtian a sorted vector
	// used iterators for efficiency

	// MARK: Set iterators to their positions
	// set position of the left iterator to leftPos
	auto iterLeft = arr.begin(); for (int i = 0; i < leftPos; i++) { iterLeft++; } 
	// set sentinel position of the left iterator to rightPos - 1
	auto iterLeftEnd = iterLeft; for (int i = 0; i < rightPos - leftPos - 1; i++) { iterLeftEnd++; } 
	// set position of the right iterator to rightPos
	auto iterRight = iterLeftEnd; iterRight++; 
	// set sentinel position of the right iterator to rightEnd
	auto iterRightEnd = iterRight; for (int i = 0; i < rightEnd - rightPos; i++) { iterRightEnd++; }
	auto iterTemp = temp.begin(); for (int i = 0; i < leftPos; i++) { iterTemp++; }

	// MARK: Merge operation begins

	while (iterLeft <= iterLeftEnd && iterRight <= iterRightEnd) {
		if (*iterLeft <= *iterRight) {
			*(iterTemp++) = *(iterLeft++);
		}
		else {
			*(iterTemp++) = *(iterRight++);
		}
	}
	
	// One of the vectors may contain remaining elements, merge them as well
	while (iterLeft <= iterLeftEnd) {
		*(iterTemp++) = *(iterLeft++);
	}
	while (iterRight <= iterRightEnd) {
		*(iterTemp++) = *(iterRight++);
	}
	
	// Copy temp back to arr
	int processedItemCount = rightEnd - leftPos + 1;
	for (int i = 0; i < processedItemCount; i++, rightEnd--) {
		arr[rightEnd] = temp[rightEnd];
	}
}

template <typename T>
void mergeSort(vector<T> & arr, vector<T> & temp, int left, int right) {
	if (left < right) {
		int center = (left + right) / 2;
		mergeSort(arr, temp, left, center);
		mergeSort(arr, temp, center + 1, right);
		merge(arr, temp, left, center + 1, right);
	}
}

template <typename T>
void sort(vector<T> & arr) {
	vector<T> temp(arr.size());
	mergeSort(arr, temp, 0, arr.size() - 1);
}


int main() {
	srand(17);
	cout << "--------------" << endl
		 << "Merge Sort" << endl
		 << "--------------" << endl;
	vector<int> randomVector = *generateVector<int>();
	auto start_time = chrono::high_resolution_clock::now();
	sort(randomVector);
	auto finish_time = chrono::high_resolution_clock::now();
	cout << endl << "Vector is " << (isSorted(randomVector) ? "sorted" : "not sorted") << endl
		 << "Elapsed time for sorting: " << chrono::duration_cast<chrono::milliseconds>(finish_time - start_time).count() << " ms" << endl;
	return 0;
}
