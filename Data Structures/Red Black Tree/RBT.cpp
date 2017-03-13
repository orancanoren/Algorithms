#include "RBT.hpp"
#include <iostream>

// CLASS RBT PUBLIC MEMBER FUNCTION DEFINITIONS

RBT::RBT() {
#ifdef _DEBUG
	std::cout << "RBT constructor invoked" << std::endl;
#endif	
	nil = new node;
	root = nil;
}

RBT::~RBT() {
	makeEmpty();
	delete nil;
}

int RBT::minimum() const {
	return minimum(root) -> key;
}

int RBT::maximum() const {
	node * iter = root;
	while (iter -> right != nullptr) iter = iter -> right;
	return iter -> key;
}

void RBT::makeEmpty() { makeEmpty(root); }

void RBT::insert(int item) { 
	node * nn = new node(item);
	nn -> left = nil;
	nn -> right = nil;
	nn -> parent = nil;
	insert(nn); 
}

void RBT::remove(int item) {
	node * removal = BST_remove(item, root);
	if (removal == nullptr) return;
	recolor(removal);
}

int RBT::successor(int item) const {
	node * n = find(item);
	if (n == nil) throw "item not found";
	return successor(n) -> key;
}

int RBT::rank(int item) const {
	node * n = find(item);
	if (n == nil) throw "item not found";
	return rank(n);
}

// CLASS RBT PRIVATE MEMBER FUNCTION DEFINITIONS

void RBT::rotate_right(node *& around) {
	node * parent = around -> parent;

	around -> left -> parent = parent;
	if (parent -> left == around) parent -> left = around -> left;
	else parent -> right = around -> left;

	node * newSubRoot = around -> left;
	newSubRoot -> right = around;
	around -> parent = newSubRoot;
	around -> left = newSubRoot -> right;

	// fix the size fields
	around -> size--;
	around -> parent -> size++;
}

void RBT::rotate_left(node *& around) {
	node * parent = around -> parent;

	around -> right -> parent = parent;
	if (parent -> left == around) parent -> left = around -> right;
	else parent -> right = around -> right;

	node * newSubRoot = around -> right;
	newSubRoot -> left = around;
	around -> parent = newSubRoot;
	around -> right = newSubRoot -> left;

	// fix the size fields
	around -> size--;
	around -> parent -> size++;
}

void RBT::makeEmpty(node * n) {
	if (n != nullptr && n != nil) {
		makeEmpty(n -> left);
		makeEmpty(n -> right);
		delete n;
	}
}

void RBT::BST_insert(node * nn) {
	node * iter = root, * parent = nil;
	while (iter != nil) {
		parent = iter;
		if (iter -> key > nn -> key) iter = iter -> left;
		else iter = iter -> right;
	}
	nn -> parent = parent;

	if (parent == nil) root = nn; // inserted root
	else if (nn -> key < parent -> key) // inserted left child
		parent -> left = nn;
	else
		parent -> right = nn; // inserted right child
}

node * RBT::BST_remove(int item, node * n) {
	if (n == nullptr) return nil;

	node * iter = n;
	while (iter != nil) {
		if (iter -> key < item) iter = iter -> left;
		else iter = iter -> right;
	}
	if (iter == nil) return nil; // not found!

	node * max_of_rightSubtree = maximum(iter);
	iter -> key = max_of_rightSubtree -> key;
	BST_remove(iter -> key, max_of_rightSubtree);
	return iter;
}

node * RBT::maximum(node * startNode) const  {
	if (startNode == nil) return nil;
	node * iter = startNode;
	while (iter -> right != nil) iter = iter -> right;
	return iter;
}

node * RBT::minimum(node * startNode) const {
	node * iter = startNode;
	while (iter -> left != nil) iter = iter -> left;
	return iter;
}

void RBT::insert(node * nn) {
	nn -> red = true;
	BST_insert(nn);
	insertFixup(nn);

	// size fields of the nodes may need to be altered
	node * iter = nn -> parent;
	while (iter != nil) {
		iter -> size++;
		iter = iter -> parent;
	}
}

void RBT::insertFixup(node * around) {
	while (around -> parent -> red) {
		if (around -> parent -> parent -> left == around -> parent) { // parent is a left child
			node * uncle = around -> parent -> parent -> right;
			if (uncle -> red) { // uncle is red [case1]
				uncle -> red = false;
				around -> parent -> red = false;
				uncle -> parent -> red = true;
				
				around = uncle -> parent; // now, fix the grandparent if needed
			}
			else { // uncle is black
				if (around -> parent -> right == around) { // triangle configuration [case2.1]
					// transform the situation into case2.2
					around = around -> parent;
					rotate_left(around); // rotate the parent
				}
				// line configuration [case2.2]
				around -> parent -> red = false;
				uncle -> parent -> red = true;
				rotate_right(uncle -> parent);
			}
		}
		else { // parent is a right child
			node * uncle = around -> parent -> parent -> left;
			if (uncle -> red) { // uncle is red [case1]
				uncle -> red = false;
				around -> parent -> red = false;
				uncle -> parent -> red = true;

				around = uncle -> parent; // now, fix the grandparent if needed
			}
			else { // uncle is black
				if (around -> parent -> left == around) { // triangle configuration [case2.1]
					// transform the situation into case2.2
					around = around -> parent;
					rotate_right(around);
				}
				// line configuration [case2.2]
				around -> parent -> red = false;
				uncle -> parent -> red = true;
				rotate_left(uncle -> parent);
			}
		}
	}
	root -> red = false; // protect the loop invariant after loop termination
}

node * RBT::successor(node *& n) const {
	if (n -> right != nil) { // n has a right child
		return minimum(n -> right);
	}
	else { // n has no right child
		if (n -> parent -> left == n) return n -> parent; // n is a left child
		else {
			// n is a right child
			node * iter = n -> parent;
			while (iter != nil && iter != iter -> parent -> left) iter = iter -> parent;
			return iter;
		}
	}
}

node * RBT::predecessor(node *&n) const {
	if (n -> left != nil) return n -> left; // n has a left child
	else return n -> parent; // n doesn't have a left child
}

node * RBT::find(int item) const {
	node * iter = root;
	while(iter != nil && iter -> key != item) {
		if (item < iter -> key) iter = iter -> left;
		else iter = iter -> right;
	}
	return iter;
}

int RBT::rank(node * x) const { // returns the rank of a node
	int rank = x -> left -> size + 1;
	node * iter = x -> parent, * z = x; // z keeps track of the subtree that x is in
	while (iter != nil) { // until we reach to the root
		if (iter -> right == z) { // if x is in the right subtree of iter
			// all the keys in the left subtree of iter and iter itself are smaller than x
			rank += iter -> left -> size + 1;
		}
		z = iter;
		iter = z -> parent; // ascend one level in the tree
	}
	return rank;
}

int RBT::orderStatistic(node * x, int i) {
	if (i > x -> size) throw "out of range";

	int left_and_self = x -> left -> size + 1;
	if (i == left_and_self) return x -> key;
	else if (i < left_and_self) return orderStatistic(x -> left, i);
	else return orderStatistic(x -> right, i - left_and_self);
}
