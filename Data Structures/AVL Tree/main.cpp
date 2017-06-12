#include "AVL.hpp"
#include <iostream>
#include <stdlib.h>
#include <chrono>

using namespace std;

void generateTree(AVL & tree) {/*
	srand(17);
	tree.insert(rand());*/
	srand(17);
	for (int i = 0; i < 5000; i++) {
		tree.insert(rand());
	}
}

void emptyTree(AVL & tree) {
	tree.makeEmpty();
}

int main() {
	AVL tree;

	auto begin = chrono::high_resolution_clock::now();
	generateTree(tree);
	auto end = chrono::high_resolution_clock::now();
	cout << "5 million random numbers have been inserted in "
		<< chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << endl;

	begin = chrono::high_resolution_clock::now();
	emptyTree(tree);
	end = chrono::high_resolution_clock::now();
	cout << "All items have been deleted in "
		<< chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << endl
		<< "Program terminating." << endl;

	return 0;
}