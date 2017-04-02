#include <iostream>
#include <string>

template <typename K, typename V>
Graph<K, V>::Graph() {
	vertices = nullptr;
	tail = nullptr;
	graph_altered = true;
	Vertex_count = 0;
}

template <typename K, typename V>
Graph<K, V>::~Graph() {
	makeEmpty();
	Vertex_count = 0;
}

template <typename K, typename V>
void Graph<K, V>::insert_Vertex(const K & key) {
	if (vertices == nullptr) {
		vertices = new Vertex<K, V>(key);
		tail = vertices;
	}
	else {
		tail->next = new Vertex<K, V>(key);
		tail = tail->next;
	}
	Vertex_count++;
	graph_altered = true;
}

template <typename K, typename V>
void Graph<K, V>::insert_Edge(const K & from, const K & to, const V & weight) {
	// 1) Find Vertex `from`
	Vertex<K, V> * v = findVertex(from);
	// 2) Find Vertex `to`
	Vertex<K, V> * v_to = findVertex(to);
	// 3) Insert the new Edge
	if (v->tail == nullptr) {
		v->outgoing = new Edge<K, V>(weight, v_to);
		v->tail = v->outgoing;
	}
	else {
		v->tail->next = new Edge<K, V>(weight, v_to);
		v->tail = v->tail->next;
	}
	graph_altered = true;
}

template <typename K, typename V>
void Graph<K, V>::remove_Edge(const K & from, const K & to) {
	// 1) Find Vertex `from`
	Vertex<K, V> * v = findVertex(from);
	// 2) Find the Edge
	Edge<K, V> * iter = v->outgoing;
	if (iter->to == to) {
		delete iter;
		v->outgoing = nullptr;
		graph_altered = true;
	}
	else if (iter->next != nullptr) {
		while (iter->next != nullptr && iter->next->to != to) { iter = iter->next; }
		if (iter->next == nullptr) throw EdgeNotFoundException();
		Edge * temp = iter->next;
		iter->next = iter->next->next;
		delete temp;
		graph_altered = true;
	}
	else throw EdgeNotFoundException();
}

template <typename K, typename V>
void Graph<K, V>::remove_Vertex(const K & key) {
	Vertex * iter = vertices;
	if (iter->key == key) {
		Vertex * temp = vertices;
		vertices = vertices->next;
		delete temp;
		Vertex_count--;
		graph_altered = true;
	}
	else if (iter->next != nullptr) {
		while (iter->next != nullptr && iter->next->key != key) { iter = iter->next; }
		if (iter->next == nullptr) throw VertexNotFound();
		Vertex * temp = iter->next;
		iter->next = iter->next->next;
		delete temp;
		Vertex_count--;
		graph_altered = true;
	}
	else throw VertexNotFoundException();
}

template <typename K, typename V>
const V & Graph<K, V>::getWeight(const K & to) const {
	Vertex<K, V> * v = findVertex(to);
	return v->distance;
}

template <typename K, typename V>
void Graph<K, V>::printPath(const K & to) const {
	const Vertex<K, V> * v = findVertex(to);
	std::string path;
	while (v->from != nullptr) {
		path += " -> " + v->key;
		v = v->from;
	}
	path = v->key + path;
	cout << path << endl;
}

template <typename K, typename V>
void Graph<K, V>::bellman_ford(const K & source_key) {
	if (!graph_altered) return; // no need to recalculate the distances if the graph hasn't been altered
	// 1) Set initial distances
	setInitialDistance(source_key);

	// 2) Perform relaxation over all edges V-1 times 
	Vertex<K, V> * iter = vertices;
	for (int i = 0; i < Vertex_count - 1; i++) {
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
				throw NegativeWeightCycleException();
			}
			iter_e = iter_e->next;
		}
		iter = iter->next;
	}

	graph_altered = false;
}

// Class Graph Private Member Function Definitions

template <typename K, typename V>
Vertex<K, V> *& Graph<K, V>::findVertex(const K & key) const {
	Vertex<K, V> * iter = vertices;
	while (iter != nullptr && iter->key != key) { iter = iter->next; }
	if (iter == nullptr) throw VertexNotFoundException();
	return iter;
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
	graph_altered = true;
}

template <typename K, typename V>
void Graph<K, V>::setInitialDistance(const K & source_key) {
	Vertex<K, V> * iter = vertices;
	while (iter != nullptr) {
		if (iter->key == source_key) {
			iter->distance = 0;
		}
		else {
			iter->distance = INFINITY;
		}
		iter = iter->next;
	}
}
