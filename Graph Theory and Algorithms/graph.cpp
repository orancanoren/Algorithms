#include "graph.hpp"
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <list>

template <typename K, typename V>
Graph<K, V>::Graph(bool undirected)
	: undirected(undirected) { }

template <typename K, typename V>
Graph<K, V>::~Graph() {
	clear();
}

// Class Graph | Public | Graph Mutators

template <typename K, typename V>
void Graph<K, V>::insert_vertex(const K & key) {
		vertices.push_back(Vertex(key));
}

template <typename K, typename V>
void Graph<K, V>::insert_edge(const K & from, const K & to, const V & weight) {
	// 1 - Find the source vertex
	list<Vertex<K, V>>::iterator source = find_if(vertices.begin(), vertices.end(), vertex_comparator);
	if (source_vertex == vertices.end()) {
		throw NotFound(VERTEX_NOT_FOUND);
	}

	// 2 - Insert the edge if there isn't an edge incident on <from> and <to>
	if (find(source_vertex->neighbors.begin(), source_vertex->neighbors.end(), to) != source_vertex->neighbors.end()) {
		throw PARALLEL_EDGE_EXCEPTION();
	}
	source_vertex->neighbors.push_back(Edge(to, weight));

	if (undirected) {
		// 3 - Repeat above steps for the insertion of (to)-[:weight]->(from)
		list<Vertex<K, V>>::iterator source_vertex = find(vertices.begin(), vertices.end(), to);
		if (source_vertex == vertices.end()) {
			throw NotFound(VERTEX_NOT_FOUND);
		}

		if (find(source_vertex->neighbors.begin(), source_vertex->neighbors.end(), from) != source_vertex->neighbors.end()) {
			throw PARALLEL_EDGE_EXCEPTION();
		}
		source_vertex->neighbors.push_back(Edge(from, weight));
	}
}

template <typename K, typename V>
void Graph<K, V>::remove_edge(const K & from, const K & to) {
	// 1 - Find Vertex <from>
	list<Vertex<K, V>>::iterator source = find_if(vertices.begin(), vertices.end(), vertex_comparator(from));
	if (source == vertices.end())
		throw VERTEX_NOT_FOUND();

	// 2 - Remove the edge
	source->neighbors.remove_if(edge_comparator(to));
	if (undirected) {
		list<Vertex<K, V>>::iterator source = find_if(vertices.cbegin(), vertices.cend(), vertex_comparator(to));
		if (source == vertices.end())
			throw VERTEX_NOT_FOUND();

		source->neighbors.remove_if(edge_comparator(from));
	}
}

template <typename K, typename V>
void Graph<K, V>::remove_vertex(const K & key) {
	vertices.remove_if(vertex_comparator(key));
}

template <typename K, typename V>
const V Graph<K, V>::get_distance(const K & to) const {
	Vertex<K, V>::const_iterator find_result = find(vertices.cbegin(), vertices.cend(), vertex_comparator(to));
	if (find_result == vertices.cend())
		throw VERTEX_NOT_FOUND();

	if (find_result->distance == INFINITY)
		throw CannotReach();

	return v->distance;
}

template <typename K, typename V>
void Graph<K, V>::printPath(const K & to) const {

	const Vertex<K, V> * v = *findVertex(to);
	std::string path;
	while (v->from != nullptr) {
		path += " -> " + v->key;
		v = v->from;
	}
	path = v->key + path;
	std::cout << path << std::endl;
}

template <typename K, typename V>
void Graph<K, V>::printGraph() const {
	Vertex<K, V> * iter = vertices;
	if (iter == nullptr) { // there are no vertices
		std::cout << "<none>" << std::endl;
	}
	else {
		while (iter != nullptr) {
			std::cout << iter->key << " ->";
			Edge<K, V> * iter_e = iter->outgoing;
			if (iter_e == nullptr) {std::cout << " <none>" << std::endl;} // there are no edges
			else {
				while (iter_e->next != nullptr) {
					std::cout << " " << iter_e->to->key << ",";
					iter_e = iter_e->next;
				}
				std::cout << " " << iter_e->to->key << std::endl; // last edge
			}
			iter = iter->next;
		}
	}
}

// Mark: Class Graph | Single Source Shortest Path Function Definitions

template <typename K, typename V>
void Graph<K, V>::bellman_ford(const K & source_key) {
	// 1) Set initial distances
	setInitialDistance(source_key);

	// 2) Perform relaxation over all edges V-1 times
	Vertex<K, V> * iter;
	for (int i = 0; i < Vertex_count - 1; i++) {
		iter = vertices;
		while (iter != nullptr) {
			Edge<K, V> * iter_e = iter->outgoing;
			while (iter_e != nullptr) {
				if (iter->distance + iter_e->weight < iter_e->to->distance) {
					iter_e->to->distance = iter->distance + iter_e->weight;
					iter_e->to->from = iter;
				}
				iter_e = iter_e->next;
			}
			iter = iter->next;
		}
	};

	// 3) Check for negative weight cycle
	iter = vertices;
	while (iter != nullptr) {
		Edge<K, V> * iter_e = iter->outgoing;
		while (iter_e != nullptr) {
			if (iter->distance + iter_e->weight < iter_e->to->distance) {
				throw NegativeWeightCycle();
			}
			iter_e = iter_e->next;
		}
		iter = iter->next;
	}
}

// Mark: Class Graph | Graph Traversal Algorithm Definitions

template <typename K, typename V>
void Graph<K, V>::BFS(const K & source_key) {
	queue<Vertex<K, V> *> BFSqueue;
	Vertex<K, V> * source_ptr = *findVertex(source_key);
	setInitialDistance(source_key);

	BFSqueue.push(source_ptr);
	while (!BFSqueue.empty()) {
		Vertex<K, V> * frontElement_ptr = BFSqueue.front();
		Edge<K, V> * iter = frontElement_ptr->outgoing;
		BFSqueue.pop();

		// look for unvisited neighbors of the front element that's just popped
		while (iter != nullptr) {
			if (!iter->to->known) {
				iter->to->known = true;
				iter->to->distance = frontElement_ptr->distance + 1;
				BFSqueue.push(iter->to);
			}
			iter = iter->next;
		}
	}
}

template <typename K, typename V>
void Graph<K, V>::DFS(const K & source_key) {
	Vertex<K, V> * source_ptr = *findVertex(source_key);
	stack<Vertex<K, V> *> DFSstack;

	DFSstack.push(source_ptr);
	while (!DFSstack.empty()) {
		Vertex<K, V> * topElement_ptr = DFSstack.top();
		
		Edge<K, V> * iter_e = topElement_ptr->outgoing;
		while (iter_e != nullptr && !iter_e->to->known) { // find an unvisited descendant
			iter_e = iter_e->next;
		}
		if (iter_e != nullptr) {
			iter_e->to->known = true;
			iter_e->to->distance = topElement_ptr->distance + 1;
			DFSstack.push(iter_e->to);
		}
		else {
			DFSstack.pop();
		}
	}
}

// Class Graph | Private Member Function Definitions

template <typename K, typename V>
Vertex<K, V> ** Graph<K, V>::findVertex(const K & key) const {
	// Returns the address of the pointer to the found vertex
	Vertex<K, V> * iter = vertices;
	while (iter != nullptr && iter->key != key) { iter = iter->next; }
	if (iter == nullptr) throw NotFound(VERTEX_NOT_FOUND);
	Vertex<K, V> ** foundVertex = &iter;
	return foundVertex;
}

template <typename K, typename V>
void Graph<K, V>::newEdge(const K & from, const K & to, const V & weight) {
	// 1) Find Vertex `from`
	Vertex<K, V> * v = *findVertex(from);
	// 2) Find Vertex `to`
	Vertex<K, V> * v_to = *findVertex(to);
	// 3) Insert the new Edge
	if (v->tail == nullptr) {
		v->outgoing = new Edge<K, V>(weight, v_to);
		v->tail = v->outgoing;
	}
	else {
		v->tail->next = new Edge<K, V>(weight, v_to);
		v->tail = v->tail->next;
	}
}

template <typename K, typename V>
void Graph<K, V>::makeEmpty() {
	Vertex<K, V> * iter = vertices;
	// iterate vertices
	while (iter != nullptr) {
		Edge<K, V> * iter_Edge = iter->outgoing;
		// iterate Edges of the current Vertex
		while (iter_Edge != nullptr) {
			Edge<K, V> * cur = iter_Edge->next;
			delete iter_Edge;
			iter_Edge = cur;
		} // comment
		Vertex<K, V> * temp = iter;
		iter = iter->next;
		delete temp;
	}
}

template <typename K, typename V>
void Graph<K, V>::setInitialDistance(const K & source_key) {
	Vertex<K, V> * iter = vertices;
	while (iter != nullptr) {
		if (iter->key == source_key) {
			iter->distance = 0;
			iter->known = true;
		}
		else {
			iter->distance = INFINITY;
		}
		iter = iter->next;
	}
}
