#include "graph.h"
#include <exception>
#include <iostream>

template <typename K, typename V>
Graph::Graph(int size) {
	vertices = nullptr;
	tail = nullptr;
}

template <typename K, typename V>
Graph::~Graph() {
	vertex * iter = vertices;
	// iterate vertices
	for (int i = 0; i < vertex_count; i++, vertices++) {
		edge * iter_edge = iter -> outgoing;
		// iterate edges of the current vertex
		while (iter_edge != nullptr) {
			edge * cur = iter_edge -> next;
			delete iter_edge;
			iter_edge = cur;
		}
	}
}

template <typename K, typename V>
void Graph::insert_vertex(const K & key) {
	if (vertices == nullptr) {
		vertices = new vertex(key);
		tail = vertices;
	}
	else {
		tail -> next = new vertex(key);
	}
}

template <typename K, typename V>
void Graph::insert_edge(const K & from, const K & to, const V & weight) {
	vertex * iter = vertices;
	while (iter != nullptr && iter->key != from) { iter = iter->next; }
	if (iter -> key != from) throw GraphException("Vertex not found");
	edge * iter_e = iter->outgoing;
	if (iter_e == nullptr) { iter_e = new edge(V); }
	else {

	}
}

template <typename K, typename V>
void Graph::remove_edge(const K & from, const K & to) {
	vertex * iter = vertices;
	while (iter != nullptr && iter->key != from) { iter = iter->next; }
	if (iter->key != from) throw GraphException("Vertex not found");

}
