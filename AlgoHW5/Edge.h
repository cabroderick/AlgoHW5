#pragma once
using namespace std;
class Node;
class Edge
{
private:
	int dist;
	Node* node;
public:
	Edge(Node* node, int dist);
	int getDist();
	Node* getNode();
};

