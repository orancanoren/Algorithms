#ifndef _RBT_H
#define _RBT_H



// Red Black Tree

class RBT {
public:
	RBT();
	~RBT();

	void insert(int item);
	void remove(int item);

	int minimum();
	int maximum();
	void makeEmpty();
private:
	struct node {
	node * parent;
	bool red;
	node * left;
	node * right;
	int key;

	node() : red(false), left(nullptr), right(nullptr), parent(nullptr) { left = nil;} // dummy leaf node
	node(int item) : red(false), left(nullptr), right(nullptr), key(item), parent(nullptr) { }
}; 

	node * root;
	node * nil;

	void makeEmpty(node *);
	void insert(node *);
	void remove(node *);

	int minimum(node *);
	int maximum(node *);

	void rotate_right(node * around);
	void rotate_left(node * around);
	void BST_insert(node * nn);
	void recolor(node * around);
};

#endif
