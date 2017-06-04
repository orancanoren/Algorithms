#include "AVL.hpp"
#include <iostream>

using namespace std;

#define max(a, b) a >= b ? a : b

AVL::AVL() {
#ifdef _DEBUG
	cout << "AVL constructor invoked" << endl;
#endif
	root = nullptr;
}

AVL::~AVL() {
#ifdef _DEBUG
	cout << "AVL destructor invoked" << endl;
#endif
	makeEmpty();
}

void AVL::insert(int item) {
	insert(root, item);
}

void AVL::remove(int item) {
	remove(root, item);
}

void AVL::makeEmpty() { 
	makeEmpty(root); 
}

int AVL::maximum() const {
	return maximum(root);
}

int AVL::minimum() const {
	return minimum(root);
}

bool AVL::contains(int item) const {
	return contains(root, item);
}

bool AVL::isEmpty() const {
	return root == nullptr;
}

// CLASS AVL PRIVATE MEMBER FUNCTION DEFINITIONS

void AVL::rotateWithLeftChild(node *& n) {
	node * x = n->left;
	n->left = x->right;
	x->right = n;
	x->height = max(height(x->left), height(x->right)) + 1;
	n = x;
}

void AVL::rotateWithRightChild(node *& n) {
	node * x = n->right;
	n->right = x->left;
	x->left = n;
	x->height = max(height(x->left), height(x->right)) + 1;
	n = x;
}

void AVL::doubleWithLeftChild(node *& n) {
	rotateWithRightChild(n->left);
	rotateWithLeftChild(n);
}

void AVL::doubleWithRightChild(node *& n) {
	rotateWithLeftChild(n->right);
	rotateWithRightChild(n);
}

int AVL::height(node * n) const {
	return n == nullptr ? -1 : n->height;
}

void AVL::insert(node *& n, int item) {
	if (n == nullptr) n = new node(item);
	else if (item < n -> key) insert(n -> left,item);
	else insert(n -> right, item);

	balance(n);
}

void AVL::remove(node *& n, int item) {
	if (n == nullptr) return;

	if (item < n -> key) remove(n->left, item);
	else if (n -> key < item) remove(n->right, item);
	
	// node found! 
	else if (n -> right != nullptr && n -> left != nullptr) { // two children
		n -> key = minimum(n -> right);
		remove(n->right, n -> key); // remove the copied item
	}
	else {
		node * oldNode = n;
		n = (n -> left != nullptr) ? n -> left : n -> right;
		delete oldNode;
	}

	balance(n);
}

void AVL::makeEmpty(node *& n) {
	// TODO: Recursive execution will create unnecessary call stack, write this iterative
	if (n != nullptr) {
		makeEmpty(n->left);
		makeEmpty(n->right);
		delete n;
	}
}

void AVL::balance(node *& n) {
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

int AVL::maximum(node * n) const {
	if (n == nullptr) return -1;
	while (n->right != nullptr) n = n->right;
	return n->key;
}

int AVL::minimum(node * n) const {
	if (n == nullptr) return -1;
	while (n -> left != nullptr) n = n -> left;
	return n -> key;
}

bool AVL::contains(node * n, int item) const {
	if (n == nullptr) { // item is not present in the tree
		return false;
	}
	else if (item < n->key) {
		return contains(n->left, item);
	}
	else {
		return contains(n->right, item);
	}
}
