#include <iostream>
#include <vector>
#include <stdlib.h>
#include <chrono>
using namespace std;

void radix_sort(vector<int> & vec) {

}

vector<int> * generateRandArr(int size) {
	vector<int> * vec = new vector<int>(size);
#ifdef _DEBUG
	cout << "Allocating " << size * sizeof(int) << " bytes" << endl
		<< "Randomizing array" << endl;
#endif
	auto begin = chrono::high_resolution_clock::now();
	auto iter = vec->begin();
	for (int i = 0; i < size; i++, iter++) {
		*iter = rand();
	}
	auto end = chrono::high_resolution_clock::now();
#ifdef _DEBUG
	cout << "Array randomized in " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << endl;
#endif
	return vec;
}

bool isSorted(vector<int> & arr) {
	auto pre = arr.begin(), cur = arr.begin()++;
	for (int i = 0; i < arr.size() - 1; i++, pre++, cur++) {
		if (*pre > *cur) return false;
	}
	return true;
}

int main() {
	cout << "------------" << endl
		<< "Radix Sort" << endl
		<< "------------" << endl
		<< "Enter the size for the random array" << endl
		<< ">> ";
	int size;
	cin >> size;
	vector<int> randArr = *generateRandArr(size);
	
	auto begin = chrono::high_resolution_clock::now();
	radix_sort(randArr);
	auto end = chrono::high_resolution_clock::now();
	cout << "Verifying the sorting operation" << endl;
	cout << "The vector is " << (isSorted(randArr) ? "" : "not") << " sorted in " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << endl;
	return 0;
}
