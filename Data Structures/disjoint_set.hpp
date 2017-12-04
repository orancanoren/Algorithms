#ifndef _DISJOINT_SET_H
#define _DISJOINT_SET_H

#define _DEBUG_HIGH

#include <iostream>
#include <memory>

template <typename node_t, typename set_t>
class DisjointSet {
public:
	explicit DisjointSet(unsigned int numElements);
	~DisjointSet();
	set_t find(const node_t vertex); // non-const since path compression is applied
	void unionVertices(node_t root1, node_t root2);
private:
	node_t * arr;
};

template <typename node_t, typename set_t>
DisjointSet<node_t, set_t>::DisjointSet(unsigned int numElements) {
#ifdef _DEBUG_HIGH
	std::cout << "DisjointSet::DisjointSet() invoked" << std::endl;
#endif
	arr = new node_t[numElements];//static_cast<node_t *>(malloc(sizeof(node_t)*numElements));
	for (int i = 0; i < numElements; i++) {
		arr[i] = -1;
	}
}

template <typename node_t, typename set_t>
DisjointSet<node_t, set_t>::~DisjointSet() {
#ifdef _DEBUG_HIGH
	std::cout << "DisjointSet::~DisjointSet() invoked" << std::endl;
#endif
	delete[] arr;
}

template <typename node_t, typename set_t>
void DisjointSet<node_t, set_t>::unionVertices(node_t v1, node_t v2) {
	// union by size
	node_t root_v1 = find(v1);
	node_t root_v2 = find(v2);

	unsigned int size_v1 = (-1)*arr[root_v1];
	unsigned int size_v2 = (-1)*arr[root_v2];

	if (size_v1 > size_v2) {
		arr[root_v2] = root_v1;
	}
	else {
		arr[root_v1] = root_v2;
	}
	
}

template <typename node_t, typename set_t>
set_t DisjointSet<node_t, set_t>::find(const node_t vertex) {
	if (arr[vertex] < 0) {
		return vertex;
	}
	else {
		arr[vertex] = find(arr[vertex]); // path compression
		return arr[vertex];
	}
}

#endif 
