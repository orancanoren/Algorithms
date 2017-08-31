#ifndef _GRAPH_H
#define _GRAPH_H

// ADJACENCY LIST REPRESENTATION
#include <limits.h>
#include <string>
#include <list>
#include <exception>
#include <string>
#include <climits>

template <typename K, typename V> struct Edge;

template <typename K, typename V>
struct Vertex {
	Vertex(const K & k)
		: key(k), next(nullptr), distance(INFINITY), outgoing(nullptr), 
		from(nullptr), tail(nullptr), known(false) { }

	// Members
	K key;
	list<Vertex<K, V>>::iterator from;
	std::list<K, V> neighbors;
	V distance;
	bool known;
};

template <typename K, typename V>
struct Edge {
	Edge(Vertex<K, V>::iterator to, const V & weight) : weight(weight), to(to) { }
	list<Vertex<K, V>>::iterator to;
	V weight;
};

template <typename K, typename V>
class Graph {
public:
	Graph(bool undirected = false);
	~Graph();

	// Fundamental Graph Mutators
	void insert_vertex(const K & key);
	void insert_edge(const K & from, const K & to, const V & weight); // parallel edges allowed
	void remove_edge(const K & from, const K & to); // removes all parallel edges
	void remove_vertex(const K & key);

	// Single Source Shortest Path Algorithms
	void bellman_ford(const K & source_key);

	// Graph Traversal Algorithms
	void BFS(const K & source_key);
	void DFS(const K & source_key);

	// Utilities
	const V get_distance(const K & to) const;
	void print_path(const K & to) const;
	void printGraph() const;
	static bool vertex_comparator(const Vertex<K, V> & v1, const Vertex<K, V> & v2);
private:
	// Members
	bool undirected;
	std::list<Vertex<K, V>> vertices;

	// Utilities
	void clear(); // sets the graph into its initial states (i.e. no vertices or edges)
	void newEdge(const K & from, const K & to, const V & weight);
	void setInitialDistance(const K & source_key);
	std::list<Vertex<K, V>>::iterator findVertex(const K & key) const;
};

// =====================
// GRAPH EXCEPTION CLASS
// =====================

enum ExceptionType {
	UNKNOWN_EXCEPTION = 0, // shouldn't be thrown
	UNKNOWN_EXCEPTION_STR, // same as above, includes additional info
	NOT_FOUND,
	NEGATIVE_WEIGHT_CYCLE,
	CANNOT_REACH,
	HANGING_EDGE
};

class GraphException : public std::exception {
public:
	GraphException(ExceptionType excType = UNKNOWN_EXCEPTION, const char * msg = "UNKNOWN_EXCEPTION")
		: excType(excType), message(msg) { }

	ExceptionType getExceptionType() const noexcept {
		return excType;
	}
	
	const char * what() noexcept {
		return message;
	}
private:
	ExceptionType excType;
	const char * message;
};

enum Reason {
	VERTEX_NOT_FOUND,
	EDGE_NOT_FOUND
};

class NotFound : public GraphException {
public:
	NotFound(Reason reason) 
		: GraphException(NOT_FOUND, ((reason == VERTEX_NOT_FOUND) ? "VERTEX NOT FOUND!" : "EDGE_NOT_FOUND")) { }
};

class NegativeWeightCycle : public GraphException {
public:
	NegativeWeightCycle() 
		: GraphException(NEGATIVE_WEIGHT_CYCLE, "NEGATIVE WEIGHT CYCLE DETECTED!") {}
};

class CannotReach : public GraphException {
public:
	CannotReach() : GraphException(CANNOT_REACH, "CANNOT REACH TO SPECIFIED VERTEX") { }
};

class HangingEdge : public GraphException {
public:
	HangingEdge() : GraphException(HANGING_EDGE, "THERE IS AN EDGE INCIDENT ON THIS VERTEX") { }
};

#include "graph.cpp"

#endif
