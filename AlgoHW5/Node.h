#pragma once
#include <vector>
using namespace std;
class Edge;
class Node
{
private:
	int num;
	bool visited;
	vector<Edge> connected;
public:
	Node(int num);
	int getDist(int dest);
	void visit();
	void addNode(Node* node, int dist);
	bool isVisited();
};