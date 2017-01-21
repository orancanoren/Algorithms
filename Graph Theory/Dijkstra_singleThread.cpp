#include <iostream>
#include <vector>

#define NOT_A_VERTEX -1
#define INFINITY INT_MAX
typedef unsigned int uint;

using namespace std;

class Dijsktra {
public:
	Dijsktra(int numVertices, int source);

	void setWeight(int from, int to, uint weight);
	void calculateDistance();
	uint getWeight(const int to) const;
	void printPath(const int to) const;
	int getDistance(const int to);
private:
	int getClosestUnknownNode() const;
	vector< vector<int> > graph;
	vector<uint> distance;
	vector<bool> known;
	vector<int> predecessor;
	int numVertices;
	int source;
};

Dijsktra::Dijsktra(int numVertices, int source) : numVertices(numVertices), source(source-1) {
	source = this -> source;
	graph.resize(numVertices, vector<int>(numVertices,INFINITY));
	distance.resize(numVertices, INFINITY);
	known.resize(numVertices, false);
	predecessor.resize(numVertices, NOT_A_VERTEX);
	graph[source][source] = 0;
	distance[source] = 0;
}

void Dijsktra::setWeight(int from, int to, uint weight) {
	graph[from-1][to-1] = weight;
}

int Dijsktra::getClosestUnknownNode() const {
	// the uknown vertex with the closest distance among all has to be adjacent to a known vertex
	uint minDistance = INFINITY;
	int closestVertex = NOT_A_VERTEX;
	for (int i = 0; i < numVertices; i++) {
		if ((!known[i]) && minDistance > distance[i]) {
			minDistance = distance[i];
			closestVertex = i;
		}
	}
	return closestVertex;
}

void Dijsktra::calculateDistance() {
	int closestUnknownNode = getClosestUnknownNode();
	for (int i = 0; i < numVertices && closestUnknownNode != NOT_A_VERTEX; i++) {
		known[closestUnknownNode] = true;
		for (int i = 0; i < numVertices; i++) {
			if (graph[closestUnknownNode][i] < distance[i]) {
				distance[i] = graph[closestUnknownNode][i] + distance[closestUnknownNode];
				predecessor[i] = closestUnknownNode;
			}
		}
		closestUnknownNode = getClosestUnknownNode();
	}
}

int Dijsktra::getDistance(const int to) {
	return distance[to-1];
}

int main() {
	int N, E;
	cin >> N >> E;
	Dijsktra d(N, 1);
	for (int i = 0; i < E; i++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		d.setWeight(from, to, cost);
	}
	d.calculateDistance();
	cout << d.getDistance(N) << endl;
	return 0;
}
