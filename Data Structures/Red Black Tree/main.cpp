#include "RBT.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

void insert(RBT & t) {
	cout << "Enter the number to insert: ";
	int item; 
	cin >> item;
	t.insert(item);
}

void remove(RBT & t) {
	cout << "Enter the item to remove: ";
	int item;
	cin >> item;
	try { t.remove(item); }
	catch(const char & msg) { cerr << msg; }
}

void getRank(RBT & t) {
	cout << "Enter the item: ";
	int item;
	cin >> item;
	cout << "Order: " << t.rank(item) << endl;
}

int getOption() {
	int option;
	cout << "1. Insert an item" << endl
		 << "2. Remove an item" << endl
		 << "3. Rank of an item" << endl
		 << "4. Search for an item" << endl
		 << "5. Predecessor of an item" << endl
		 << "6. Successor of an item" << endl
		 << "7. Get max item in the set" << endl
		 << "8. Get min item in the set" << endl
		 << "9. Exit" << endl
		 << ">> " << endl;
	cin >> option;
	if (option > 9 || option < 1) {
		cout << "Invalid input" << endl;
		return getOption();
	}
}

int main() {
	RBT tree;
	srand(17);
	cout << "------------" << endl
		 << "DYNAMIC SET | RED BLACK TREE" << endl
		 << "-----------------------------" << endl;
	int option;
	do {
		option = getOption();
		switch(option) {
		case 1: // insert
			insert(tree);
			break;
		case 2: // remove
			remove(tree);
			break;
		case 3: // rank
			getRank(tree);
			break;
		case 4: // search
			break;
		case 5: // predecessor
			break;
		case 6: //successor
			break;
		case 7: // maximum
			break;
		case 8: // minimum
			break;
		}
	} while (option != 9);
	return 0;
}
