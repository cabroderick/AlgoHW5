#include "Node.h"
#include "Edge.h"
using namespace std;
// Adds a node to the adjacent node lists
// node: The node to add
// dist: The distance to that node
void Node::addNode(Node* node, int dist) {
	Edge* newEdge = new Edge(node, dist);
	this->connected.push_back(*newEdge);
}

bool Node::isVisited() {
	return this->visited;
}

int Node::getDist(int dest) {
	if (dest == num) return 0; // base
	int minDist = INT_MAX;
	int next = 0;
	for (int i = 0; i < connected.size(); i++) {
		if (connected[i].getNode()->isVisited()) {
			int dist = connected[i].getNode()->getDist(dest);
			if (dist < minDist) {
				minDist = dist;
				next = i;
			}
		}
	}
	connected[next].getNode()->visit(); // mark visited node as visited
	return minDist + connected[next].getDist();
}

void Node::visit() {
	visited = true;
}