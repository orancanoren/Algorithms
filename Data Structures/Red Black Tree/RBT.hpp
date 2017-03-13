#ifndef _RBT_H
#define _RBT_H

struct node {
	node * parent;
	bool red;
	node * left;
	node * right;
	int key;
	int size; // augmented field

	node() : red(false), left(nullptr), right(nullptr), parent(nullptr), size(0) { } // dummy leaf node
	node(int item) : red(false), left(nullptr), right(nullptr), key(item), parent(nullptr), size(1) { }
}; 

// Dynamic Set using an augmented Red Black Tree

class RBT {
public:
	RBT();
	~RBT();

	void insert(int item);
	void remove(int item);

	int minimum() const;
	int maximum() const;
	int successor(int item) const;
	int predecessor(int item) const;
	int rank(int item) const; // gets the i'th order statistics in the set

	void makeEmpty();
private:
	node * root;
	node * nil;

	void makeEmpty(node *);
	void insert(node *);

	// Utility Functions
	void rotate_right(node *& around);
	void rotate_left(node *& around);
	void BST_insert(node * nn);
	node * BST_remove(int item, node * n);
	void insertFixup(node * around);

	// Dynamic Set operations
	node * maximum(node * subRoot) const;
	node * minimum(node * subRoot) const;
	node * successor(node *& subRoot) const;
	node * predecessor(node *& subRoot) const;
	node * find(int key) const;
	int rank(node * of) const; // returns the rank of a node
	int orderStatistic(node * subRoot, int i); // returns the i'th order statistic
};

#endif
