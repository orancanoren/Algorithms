#ifndef _LINKEDLIST_HPP
#define _LINKEDLIST_HPP

#include <exception>

// Oran Can Oren
// LinkedList class
// Provides iterator & exception classes as well

template <typename T>
class LinkedList {
private:
	struct Node {
		Node() { }
		Node(const T & data)
			: data(data), next(nullptr), prev(nullptr) { }

		T data;
		Node * next;
		Node * prev;
	};
	unsigned int list_size;
	Node * dummy;
	Node * tail;

	void makeEmpty();
public:
	struct iterator {
	public:
		iterator(Node * initial_node) : current(initial_node) { }

		// OPERATOR OVERLOADS
		T & operator*(); // dereference
		T * operator->();

		iterator & operator++(); // prefix increment
		iterator & operator++(int); // postfix increment
		iterator & operator--(); // prefix decrement
		iterator & operator--(int); // postfix decrement
		bool operator==(const iterator & rhs) const;
		bool operator!=(const iterator & rhs) const;
	private:
		Node * current;
	};

	LinkedList();
	LinkedList(const LinkedList &&); // move constructor
	~LinkedList();

	// Mutators
	void push_back(const T & data);
	void push_front(const T & data);
	void pop_back();
	void pop_front();

	// Accessors
	T & find(const T & data) const;
	bool isEmpty() const;
	unsigned int size() const;

	// Operators
	void operator=(const LinkedList & rhs);
	T operator[](const unsigned int index) const;

	// Iterator-related
	iterator begin() const {
		return iterator(dummy->next);
	}
	iterator end() const {
		return iterator(nullptr);
	}
};

// =================
// Exception classes
// =================

class LinkedListException : public std::exception {
public:
	LinkedListException(const char * msg) {
		msg = msg;
	}
	const char * what() {
		return msg;
	}
private:
	const char * msg;
};

class AccessViolationException : public LinkedListException {
public:
	AccessViolationException() 
		: LinkedListException("Access violation on linked list!") {}
};

class NotFoundException : public LinkedListException {
public:
	NotFoundException()
		: LinkedListException("Item not found") {}
};

// ========================================================
// Class LinkedList::iterator | Member Function Definitions
// ========================================================

template <typename T>
T & LinkedList<T>::iterator::operator*() {
	return current->data;
}

template<typename T>
T * LinkedList<T>::iterator::operator->()
{
	return &current->data;
}

template<typename T>
typename LinkedList<T>::iterator & LinkedList<T>::iterator::operator++()
{
	if (current) {
		current = current->next;
	}
	return *this;
}

template <typename T>
typename LinkedList<T>::iterator & LinkedList<T>::iterator::operator++(int a) {
	iterator temp = *this;
	++*this;
	return temp;
}

template <typename T>
bool LinkedList<T>::iterator::operator==(const iterator & rhs) const {
	return current == rhs.current;
}

template <typename T>
bool LinkedList<T>::iterator::operator!=(const iterator & rhs) const {
	return current != rhs.current;
}

template <typename T>
typename LinkedList<T>::iterator & LinkedList<T>::iterator::operator--() {
	if (current) {
		current = current->prev;
	}
	return *this;
}

template <typename T>
typename LinkedList<T>::iterator & LinkedList<T>::iterator::operator--(int a) {
	iterator temp = *this;
	--*this;
	return temp;
}

// ==============================================
// Class LinkedList | Member Function Definitions
// ==============================================

template <typename T>
LinkedList<T>::LinkedList() {
	Node * dummy_node = new Node;
	dummy_node->next = nullptr;
	dummy = dummy_node;
	tail = dummy_node;
	list_size = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList && rhs) {
	Node * dummy_node = new Node;
	dummy_node->next = nullptr;
	dummy = dummy_node;
	tail = dummy_node;
	list_size = 0;
	for (LinkedList::iterator it = rhs.begin(); it != rhs.end(); it++) {
		this->push_back(*it);
	}
}

template <typename T>
LinkedList<T>::~LinkedList() {
	makeEmpty();
}

template <typename T>
void LinkedList<T>::push_back(const T & data) {
	Node * new_node = new Node(data);
	tail->next = new_node;
	new_node->prev = tail;
	tail = new_node;
	list_size++;
}

template <typename T>
void LinkedList<T>::push_front(const T & data) {
	Node * new_node = new Node(data);
	new_node->next = dummy->next;
	new_node->prev = dummy;
	dummy->next = new_node;
	if (new_node->next == nullptr) {
		tail = new_node;
	}
	else {
		new_node->next->prev = new_node;
	}
	list_size++;
}

template <typename T>
void LinkedList<T>::pop_front() {
	if (list_size > 0) {
		Node *& temp = dummy->next;
		dummy->next = dummy->next->next;
		dummy->next->prev = nullptr;
		delete temp;
		list_size--;
	}
}

template <typename T>
void LinkedList<T>::pop_back() {
	if (list_size > 0) {
		Node * new_tail = tail->prev;
		delete tail;
		tail = new_tail;
		if (tail != nullptr) {
			tail->next = nullptr;
		}
		list_size--;
	}
}

template <typename T>
T & LinkedList<T>::find(const T & data) const {
	// Perform a bidirectional search for better performance
	Node * left = dummy->next;
	Node * right = tail;
	unsigned int left_pos = 0, right_pos = list_size - 1;
	while (right_pos > left_pos) {
		if (left->data == data) {
			return left->data;
		}
		else if (right->data == data) {
			return right->data;
		}
		left = left->next;
		right = right->prev;
		left_pos++;
		right_pos--;
	}
	throw NotFoundException();
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
	return list_size == 0;
}

template <typename T>
unsigned int LinkedList<T>::size() const {
	return list_size;
}

template <typename T>
void LinkedList<T>::operator=(const LinkedList & rhs) {
	Node * rhs_iter = rhs.dummy->next;
	while (rhs_iter != nullptr) {
		this->push_back(rhs_iter->data);
	}
}

template <typename T>
void LinkedList<T>::makeEmpty() {
	while (dummy->next != nullptr) {
		pop_back();
	}
}

template <typename T>
T LinkedList<T>::operator[](const unsigned int index) const {
	if (list_size < index) {
		throw AccessViolationException();
	}

	Node * iter;
	if (index < list_size / 2) {
		iter = dummy->next;
		for (int i = 0; i < index; i++) {
			iter = iter->next;
		}
		return iter->data;
	}
	else {
		iter = tail;
		for (int i = list_size - 1; i > index; i--) {
			iter = iter->prev;
		}
		return iter->data;
	}
}
#endif