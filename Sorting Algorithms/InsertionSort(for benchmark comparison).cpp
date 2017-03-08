#include <iostream>
#include <vector>
#include <chrono>
#include <stdlib.h>

using namespace std;

bool isSorted(const vector<int> & arr) { 
	// Post condition: returns a boolean indicating whether the vector is sorted or not
	auto prev = arr.begin();
	auto cur = arr.begin(); cur++;

	for (;cur != arr.end(); cur++, prev++)
		if (*cur < *prev) return false;

	return true;
}

vector<int> * generateVector() {
	int size;
	cout << "Please enter the size of the vector: " << endl
		 << ">> ";
	cin >> size;
	auto start_time = chrono::high_resolution_clock::now();

	vector<int> *randVector = new vector<int>(size);
	for (auto iter = randVector -> begin(); iter != randVector -> end(); iter++) {
		*iter = rand();
	}

	auto finish_time = chrono::high_resolution_clock::now();
	cout << "Vector of size " << randVector -> size() << " has been generated" << endl
		<< "Elapsed time for generating vector: " << chrono::duration_cast<chrono::milliseconds>(finish_time - start_time).count() << " ms" << endl;
	return randVector;
}

void insertionSort(vector<int> & vec) {
	// Post condition: Sorts the vector in increasing order
	int vecSize = vec.size();
	for (int i = 1; i < vecSize; i++) {
		int j = i;
		while (j > 0 && vec[j-1] > vec[j]) {
			swap(vec[j], vec[j-1]);
			j--;
		}
	}
}

int main() {
	srand(17);
	cout << "----------------" << endl
		 << "Insertion Sort" << endl
		 << "----------------" << endl;
	vector<int> randomizedVector = *generateVector();
	auto start_time = chrono::high_resolution_clock::now();
	insertionSort(randomizedVector);
	auto finish_time = chrono::high_resolution_clock::now();
	cout << endl << "Vector is " << (isSorted(randomizedVector) ? "sorted" : "not sorted") << endl
		 << "Elapsed time for sorting: " << chrono::duration_cast<chrono::milliseconds>(finish_time - start_time).count() << " ms" << endl;
	return 0;
}
