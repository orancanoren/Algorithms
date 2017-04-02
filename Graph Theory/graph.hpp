#ifndef _GRAPH_H
#define _GRAPH_H

/* TO DO
BREADTH FIRST SEARCH
DEPTH FIRST SEARCH
UNIFROM COST SEARCH

DIJKSTRA
KRUSKAL MST
PRIM MST
TOPOLOGICAL SORT
*/

// ADJACENCY LIST REPRESENTATION

#define INFINITY INT_MAX

template <typename K, typename V> class Edge;

template <typename K, typename V>
class Vertex {
public:
	K key;
	Vertex<K, V> * from; /* we keep the Vertex that we have reached to
				   the current one from so that we can find the
				   shortest path itself along with the distance */
	Vertex<K, V> * next; // keep a linked list of vertices
	Edge<K, V> * outgoing, *tail; // keep the outgoing Edges from the current Vertex in a linked list
	V distance; // keep the distance to the source Vertex
	Vertex(const K & k) 
		: key(k), next(nullptr), distance(INFINITY), outgoing(nullptr), from(nullptr), tail(nullptr) { }
};

template <typename K, typename V>
class Edge {
public:
	Vertex<K, V> * to;
	V weight;
	Edge * next; // keep a linked list of Edges outgoing from the current Vertex
	Edge(const V & weight, Vertex<K, V> *& to) : weight(weight), next(nullptr), to(to) { }
};

template <typename K, typename V>
class Graph {
public:
	Graph();
	~Graph();

	// Utilities
	void insert_Vertex(const K & key);
	void insert_Edge(const K & from, const K & to, const V & weight);
	void remove_Edge(const K & from, const K & to);
	void remove_Vertex(const K & key);
	const V & getWeight(const K & to) const;
	void printPath(const K & to) const;

	// Single source shortest path algorithms
	void bellman_ford(const K & source_key);
private:
	bool graph_altered;
	Vertex<K, V> * vertices, * tail, * source;
	unsigned Vertex_count = 0;

	Vertex<K, V> *& findVertex(const K & key) const;
	void makeEmpty();
	void setInitialDistance(const K & source_key);
};

class GraphException {
public:
	GraphException(char * msg);
	~GraphException();
	const char * const what() const;
private:
	const char * const msg;
};

class EdgeNotFoundException : public GraphException {
public:
	EdgeNotFoundException() : GraphException("Edge not found!") { }
};

class VertexNotFoundException : public GraphException {
public:
	VertexNotFoundException() : GraphException("Vertex not found!") { }
};

class NegativeWeightCycleException : public GraphException {
public:
	NegativeWeightCycleException() : GraphException("Negative Weight Cycle Detected") { }
};

#include "graph.cpp"

#endif
