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
void BubbleSort<T>::sort() {
  for (int right = size-1; right > 0; right--) {
    T * i = &arr[0];
    for (int i_count = 0; i_count < right-1; i_count++) {
      if (*i > *(i+1)) {
	swap(*i, *(i+1));
      }
    }
  }
}

int * generateIntArray(const int size) {
  srand(17);
  cout << "Allocating space of size " << size*sizeof(int) << " bytes" << endl;
  int * randArr = new int [size];
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
  cout << "Randomization complete in " << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << " ms" << endl;
  return randArr;
}

int main() {
  int size;
  cout << "Enter the size of the data: " << endl
       << ">> ";
  cin >> size;
  int * randArr = generateIntArray(size);
  BubbleSort<int> sortObj(randArr, size);
  cout << "Sorting data " << endl;
  auto begin = chrono::high_resolution_clock::now();
  sortObj.sort();
  auto end = chrono::high_resolution_clock::now();
  cout << "Data has been sorted in " << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << " ms" << endl;
  return 0;
}
