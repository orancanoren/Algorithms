#ifndef _AVL_H
#define _AVL_H

struct node {
	node * left;
	node * right;
	int key;
	int height;

	node(int item) : key(item), height(0), left(nullptr), right(nullptr) { }
};

// AVL tree

class AVL {
public:
	AVL();
	~AVL();

	void insert(int item);
	void remove(int item);

	bool contains(int item) const;
	int minimum() const;
	int maximum() const;
	void makeEmpty();
	bool isEmpty() const;
private:
	node * root;

	void rotateWithLeftChild(node *&);
	void rotateWithRightChild(node *&);
	void doubleWithLeftChild(node *&);
	void doubleWithRightChild(node *&);

	int height(node *) const; // returns the height of a node | returns -1 if nullptr
	void insert(node *&, int item);
	void remove(node *&, int item);
	void balance(node *& subroot);
	void makeEmpty(node *&);
	int minimum(node *) const;
	int maximum(node *) const;
	bool contains(node *, int item) const;
};

#endif
