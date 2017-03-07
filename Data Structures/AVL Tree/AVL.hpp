#ifndef _BST_H
#define _BST_H

struct node {
	node * left;
	node * right;
	int key;
	int height;

	node(int item) : key(item), height(0), left(nullptr), right(nullptr) { }
};

// AVL tree

class BST {
public:
	BST();
	~BST();

	void insert(int item);
	void remove(int item);

	bool search(int item) const;
	int minimum() const;
	int maximum() const;
	void makeEmpty();
private:
	node * root;

	void rotateWithLeftChild(node *&);
	void rotateWithRightChild(node *&);
	void doubleWithLeftChild(node *&);
	void doubleWithRightChild(node *&);

	int height(node *) const; // returns the height of a node | returns -1 if nullptr
	void insert(int item, node *&);
	void remove(int item, node *&);
	void balance(node *& subroot);
	void makeEmpty(node *&);
	int minimum(node *) const;
	int maximum(node *) const;
};

#endif
