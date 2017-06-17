#ifndef _GRAPH_H
#define _GRAPH_H

// ADJACENCY LIST REPRESENTATION
#include <limits.h>
#include <string>
#include <exception>
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
	Graph(bool undirected = false);
	~Graph();

	// Utilities
	void insert_Vertex(const K & key);
	void insert_Edge(const K & from, const K & to, const V & weight);
	void remove_Edge(const K & from, const K & to);
	void remove_Vertex(const K & key);
	const V & getDistance(const K & to) const;
	void printPath(const K & to) const;
	void printGraph() const;
	bool isAltered() const;

	// Single source shortest path algorithms
	void bellman_ford(const K & source_key);
private:
	bool graph_altered;
	bool undirected;
	Vertex<K, V> * vertices, * tail, * source;
	unsigned Vertex_count = 0;

	Vertex<K, V> ** findVertex(const K & key) const;
	void makeEmpty();
	void newEdge(const K & from, const K & to, const V & weight);
	void setInitialDistance(const K & source_key);
};

//
// GRAPH EXCEPTION CLASS
//

enum ExceptionType {
	UNKNOWN_EXCEPTION = 0, // shouldn't be thrown
	UNKNOWN_EXCEPTION_STR, // same as above, includes additional info
	NOT_FOUND,
	NEGATIVE_WEIGHT_CYCLE,
	CANNOT_REACH
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

#include "graph.cpp"

#endif
