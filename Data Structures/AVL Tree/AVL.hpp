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

	void makeEmpty();
	int maximum() const;
	int minimum() const;
	bool contains(int item) const;
	bool isEmpty() const;
private:
	node * root;

	void rotateWithLeftChild(node *&);
	void rotateWithRightChild(node *&);
	void doubleWithLeftChild(node *&);
	void doubleWithRightChild(node *&);

	int height(node *) const;
	void insert(node *&, int item);
	void remove(node *&, int item);
	void makeEmpty(node *&);
	void balance(node *& subroot);
	int minimum(node *) const;
	int maximum(node *) const;
	bool contains(node *, int item) const;
};

#endif
