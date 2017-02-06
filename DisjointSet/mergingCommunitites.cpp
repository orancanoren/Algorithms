#inlcude <iostream>

using namespace std;

struct Node {
  int identifier;
  int size; // for union by size operation
  Node * parent;
  Node (int i) : identifier(i) {
    parent(nullptr);
  }
};

class DisjointSet {
public:
  DisjointSet();
  Node * find(Node *);
  Node * merge(Node *, Node *);
private:
  
};
