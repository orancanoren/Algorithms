#ifndef _GRAPH_H
#define _GRAPH_H

/* TO DO
BREADTH FIRST SEARCH
DEPTH FIRST SEARCH
UNIFROM COST SEARCH

DIJKSTRA
BELLMAN FORD
KRUSKAL MST
PRIM MST
TOPOLOGICAL SORT
*/

// ADJACENCY LIST REPRESENTATION

template <typename K, typename V>
class Graph {
public:
	Graph();
	~Graph();

	// Utilities
	void insert_vertex(const K & key);
	void insert_edge(const K & from, const K & to, const V & weight);
	void remove_edge(const K & from, const K & to);
	void remove_vertex(const k & key);

	// Single source shortest path algorithms
	void bellman_ford();
private:
	struct vertex {
		K key;
		vertex * from; /* we keep the vertex that we have reached to
					   the current one from so that we can find the
					   shortest path itself along with the distance */
		vertex * next; // keep a linked list of vertices
		edge * outgoing; // keep the outgoing edges from the current vertex in a linked list
		node(const K & k) : key(k), from(nullptr), next(nullptr) { }
		edge * tail; // keep the last edge
	};
	struct edge {
		V weight;
		edge * next; // keep a linked list of edges outgoing from the current vertex
		edge(const V & weight) : weight(weight), next(nullptr) { }
	};

	vertex * vertices, *tail;
	unsigned vertex_count = 0;
};

class GraphException {
public:
	GraphException(char * msg);
	~GraphException();
	const char * const what() const;
private:
	char * msg;
};

#include "graph.cpp";

#endif
