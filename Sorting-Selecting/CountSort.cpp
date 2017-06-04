#include <iostream>
#include <chrono>
#include <vector>
#include <stdlib.h>
using namespace std;

#define _DEBUG

void CountSort(vector<int> & arr, int range) {
	vector<int> sortArr(range, 0);
	auto iter = arr.begin();
	for (int i = 0; i < arr.size(); i++, iter++) {
		sortArr[*iter]++;
	}
	iter = arr.begin();
	for (int i = 0; i < sortArr.size(); i++) {
		for (int j = 0; j < sortArr[i]; j++) {
			*iter = i;
			iter++;
		}
	}
}

vector<int> * generateRandArr(int size, int range) {
#ifdef _DEBUG
	cout << "Allocating " << size*sizeof(int) << " bytes" << endl;
#endif
	vector<int> * arr = new vector<int>(size);
	cout << "Memory has been allocated" << endl;
	auto iter = arr -> begin();
	auto begin = chrono::high_resolution_clock::now();
	for (int count = 0; count < size; count++, iter++) {
		*iter = rand() % range;
	}
	auto end = chrono::high_resolution_clock::now();
	cout << "Array has been randomized in " << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << " ms" << endl;
	return arr;
}

bool isSorted(vector<int> & arr) {
	auto cur = arr.begin()++, pre = arr.begin();
	for (int i = 0; i < arr.size(); i++) {
		if (*pre > *cur) return false;
	}
	return true;
}

int main() {
	srand(17);
	cout << "------------" << endl
		 << "Count Sort" << endl
		 << "-------------" << endl
		 << "Enter the size of the array" << endl
		 << ">> ";
	int size;
	cin >> size;
	int range;
	cout << "Enter the upper limit for the numbers in the array" << endl
		 << ">> ";
	cin >> range;
	vector<int> randArr = *generateRandArr(size, range);
#ifdef _DEBUG
	auto begin = chrono::high_resolution_clock::now();
	CountSort(randArr, range);
	auto end = chrono::high_resolution_clock::now();
	cout << "The array is" << (isSorted(randArr) ? " " : " not") << " sorted in " << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << " ms" << endl;
#endif
	return 0;
}
