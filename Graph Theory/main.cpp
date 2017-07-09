#include "graph.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>

using namespace std;

class UserGraph {
public:
	UserGraph() : g(Graph<string, int>(true)) {
	}

	void prepare_graph() {
		g.insert_Vertex("Istanbul");
		g.insert_Vertex("Ankara");
		g.insert_Vertex("Izmir");
		g.insert_Vertex("Izmit");
		g.insert_Vertex("Los Angeles");

		g.insert_Edge("Izmir", "Ankara", 400);
		g.insert_Edge("Izmir", "Istanbul", 600);
		g.insert_Edge("Istanbul", "Los Angeles", 400);
		g.insert_Edge("Izmit", "Istanbul", 150);
	}

	void menu() {
		cout << "Options" << endl
			<< "-------" << endl
			<< "1. Insert new vertex" << endl
			<< "2. Insert new edge" << endl
			<< "3. Remove an edge" << endl
			<< "4. Remove a vertex" << endl
			<< "5. Bellman Ford Shortest Path" << endl
			<< "6. Breadth First Search" << endl
			<< "7. Depth First Search" << endl
			<< "8. Get distance to a vertex" << endl
			<< "9. Exit" << endl;
	}

	void edge() {
		string from, to;
		int weight;
		cout << "<from> <to> <weight>" << endl
			<< ">> ";
		cin >> from >> to >> weight;
		g.insert_Edge(from, to, weight);
	}

	void redge() {
		string from, to;
		cout << "<from> <to>" << endl
			<< ">> ";
		cin >> from >> to;
		try {
			g.remove_Edge(from, to);
		}
		catch (GraphException & exc) {
			cout << "Error\n-----\n" << exc.what() << endl;
		}
	}

	void vertex() {
		string key;
		cout << "Enter the name of the vertex" << endl
			<< ">> ";
		cin >> key;
		g.insert_Vertex(key);
	}

	void rvertex() {
		string key;
		cout << "Enter the name of the vertex" << endl
			<< ">> ";
		cin >> key;
		try {
			g.remove_Vertex(key);
		}
		catch (GraphException & exc) {
			cout << "Error\n----" << exc.what() << endl;
		}
	}

	void bford() {
		string source;
		cout << "Enter the name of the source vertex" << endl
			<< ">> ";
		cin >> source;
		auto begin = chrono::high_resolution_clock::now();
		g.bellman_ford(source);
		auto end = chrono::high_resolution_clock::now();
		cout << "Distance calculation has been completed in "
			<< chrono::duration_cast<chrono::milliseconds>(end - begin).count()
			<< " ms" << endl;
	}

	void BFS() {
		string source;
		cout << "Enter the name of the source vertex" << endl
			<< " >> ";
		cin >> source;
		auto begin = chrono::high_resolution_clock::now();
		g.BFS(source);
		auto end = chrono::high_resolution_clock::now();
		cout << "Distance calculation has been completed in "
			<< chrono::duration_cast<chrono::milliseconds>(end - begin).count() 
			<< " ms" << endl;
	}

	void DFS() {
		string source;
		cout << "Enter the name of the source vertex" << endl
			<< " >> ";
		cin >> source;
		auto begin = chrono::high_resolution_clock::now();
		g.DFS(source);
		auto end = chrono::high_resolution_clock::now();
		cout << "Distance calculation has been completed in "
			<< chrono::duration_cast<chrono::milliseconds>(end - begin).count()
			<< " ms" << endl;
	}

	void dist() {
		string destination;
		cout << "Enter the name of the vertex you want to reach" << endl
			<< ">> ";
		cin >> destination;
		try {
			int pathWeight = g.getDistance(destination);
			cout << "Distance: " << pathWeight << endl;
		}
		catch (GraphException & exc) {
			cout << "Error\n-------\n" << exc.what() << "\n-------\n" << endl;
		}
	}

	void printGraph() {
		g.printGraph();
	}

private:
	Graph<string, int> g;
};

int main() {
	UserGraph g; // undirected graph
	//g.prepare_graph();
	bool clearScreen = false;
	int choice;
	do {
		cout << "Current Graph:" << endl;
		g.printGraph();
		cout << "Enter a command (1-8) or 0 for menu" << endl
			<< ">> ";
		cin >> choice;
		switch (choice) {
		case 0:
			system("CLS");
			g.menu();
			break;
		case 1:
			system("CLS");
			g.vertex();
			break;
		case 2:
			g.edge();
			break;
		case 3:
			system("CLS");
			g.redge();
			break;
		case 4:
			system("CLS");
			g.rvertex();
			break;
		case 5:
			system("CLS");
			g.bford();
			break;
		case 6:
			system("CLS");
			g.BFS();
			break;
		case 7:
			system("CLS");
			g.DFS();
			break;
		case 8:
			system("CLS");
			g.dist();
			break;
		case 9:
			cout << "K THX BYE" << endl;
			break;
		default:
			system("CLS");
			cout << "Enter a valid command" << endl;
			cin.clear();
			break;
		}
	} while (choice != 9);
	return 0;
}
