#include "BST.h"
#include <iostream>

using namespace std;

#define max(a, b) a >= b ? a : b

BST::BST() {
#ifdef _DEBUG
	cout << "BST constructor invoked" << endl;
#endif
	root = nullptr;
}

BST::~BST() {
#ifdef _DEBUG
	cout << "BST destructor invoked" << endl;
#endif
	makeEmpty();
}

int BST::height(node * n) const {
	return n == nullptr ? -1 : n -> height;
}

void BST::insert(int item) {
	insert(item, root);
}

void BST::remove(int item) {
	remove(item, root);
}

void BST::makeEmpty() { makeEmpty(root); }

int BST::maximum() const {
	return maximum(root);
}

// CLASS BST PRIVATE MEMBER FUNCTION DEFINITIONS

void BST::insert(int item, node *& n) {
	if (n == nullptr) n = new node(item);
	else if (item < n -> key) insert(item, n -> left);
	else insert(item, n -> right);

	balance(n);
}

void BST::remove(int item, node *& n) {
	if (n == nullptr) return;

	if (item < n -> key) remove(item, n -> left);
	else if (n -> key < item) remove(item, n -> right);
	
	// node found! 
	else if (n -> right != nullptr && n -> left != nullptr) { // two children
		n -> key = minimum(n -> right);
		remove(n -> key, n -> right); // remove the copied item
	}
	else {
		node * oldNode = n;
		n = (n -> left != nullptr) ? n -> left : n -> right;
		delete oldNode;
	}

	balance(n);
}

void BST::balance(node *& n) {
	if (n == nullptr) return;

	if (height(n -> left) - height(n -> right) > 1) {
		if (height(n -> left -> left) >= height(n -> left -> right)) rotateWithLeftChild(n);
		else doubleWithLeftChild(n);
	}
	else {
		if (height(n -> right) - height(n -> left) > 1) {
			if (height(n -> right -> right) >= height(n -> right -> left)) rotateWithRightChild(n);
			else doubleWithRightChild(n);
		}
		n -> height = max(height(n -> left), height(n->right)) + 1;
	}

	n -> height = max(height(n-> left), height(n -> right)) + 1;
}

void BST::rotateWithLeftChild(node *& n) {
	node * x = n -> left;
	n -> left = x -> right;
	x -> right = n;
	x -> height = max(height(x -> left), height(x -> right)) + 1;
	n = x;
}

void BST::rotateWithRightChild(node *& n) {
	node * x = n -> right;
	n -> right = x -> left;
	x -> left = n;
	x -> height = max(height(x -> left), height(x -> right)) + 1;
	n = x;
}

void BST::doubleWithLeftChild(node *& n) {
	rotateWithRightChild(n -> left);
	rotateWithLeftChild(n);
}

void BST::doubleWithRightChild(node *& n) {
	rotateWithLeftChild(n -> right);
	rotateWithRightChild(n);
}

int BST::minimum(node * n) const {
	if (n == nullptr) return -1;
	while (n -> left != nullptr) n = n -> left;
	return n -> key;
}

void BST::makeEmpty(node *& n) {
	if (n != nullptr) {
		makeEmpty(n -> left);
		makeEmpty(n -> right);
		delete n;
	}
}

int BST::maximum(node * n) const {
	if (n == nullptr) return -1;
	while (n -> right != nullptr) n = n -> right;
	return n -> key;
}
