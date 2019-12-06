#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

class Edge;
class Node;

template<typename K, typename V>

class HashNode {
public:
	V value;
	K key;
	HashNode(K key, V value) {
		this->value = value;
		this->key = key;
	}
};

template<typename K, typename V>

class HashMap {
	HashNode<K, V>** arr;
	int capacity;
	//current size 
	int size;
	//dummy node 
	HashNode<K, V>* dummy;
public:
	HashMap() {
		//Initial capacity of hash array 
		capacity = 1000;
		size = 0;
		arr = new HashNode<K, V> * [capacity];

		for (int i = 0; i < capacity; i++) arr[i] = NULL;
	}
	int hashCode(K key)
	{
		return key % capacity;
	}

	void insertNode(K key, V value)
	{
		HashNode<K, V>* temp = new HashNode<K, V>(key, value);

		int hashIndex = key;
 
		while (arr[hashIndex] != NULL && arr[hashIndex]->key == key && arr[hashIndex]->key != -1) {
			if (arr[hashIndex]->value == value) return;
			hashIndex++;
			hashIndex %= capacity;
		}
		while (arr[hashIndex] != NULL && arr[hashIndex]->key != key && arr[hashIndex]->key != -1) {
			hashIndex++;
			hashIndex %= capacity;
		}

		if (arr[hashIndex] == NULL || arr[hashIndex]->key == -1) size++;
		arr[hashIndex] = temp;
	}
	V deleteNode(int key)
	{
		int hashIndex = hashCode(key);

		while (arr[hashIndex] != NULL) {
			if (arr[hashIndex]->key == key)	{
				HashNode<K, V>* temp = arr[hashIndex];
				arr[hashIndex] = dummy;
				size--;
				return temp->value;
			}
			hashIndex++;
			hashIndex %= capacity;

		}
		return NULL;
	}

	V get(int key) {
		int hashIndex = hashCode(key);
		int counter = 0;
		while (arr[hashIndex] != NULL) {
			int counter = 0;
			if (counter++ > capacity) return NULL;
			if (arr[hashIndex]->key == key) return arr[hashIndex]->value;
			hashIndex++;
			hashIndex %= capacity;
		}
		return NULL;
	}

	int sizeofMap() {
		return size;
	}

	bool isEmpty() {
		return size == 0;
	}

	void display()
	{
		int nonEmpty = 0;

		bool currentlyCountingEmpty = false;

		int startEmpty = 0;
		int endEmpty = 0;
		int currentStartEmpty = 0;
		int largestEmpty = 0;
		int currentEmpty = -1;

		bool currentlyCountingCluster = false;

		int startCluster = 0;
		int endCluster = 0;
		int currentStartCluster;
		int largestCluster = 0;
		int currentCluster = 0;

		string farthestString = "";
		int largestDist = 0;
		int a;
		int b;

		for (int i = 0; i < capacity; i++)
		{
			if (arr[i] != NULL && arr[i]->key != -1) {
				nonEmpty++;
				cout << i << " " << arr[i]->value << " " << arr[i]->key << endl;

				if (currentEmpty > largestEmpty) {
					largestEmpty = currentEmpty;
					startEmpty = currentStartEmpty;
					endEmpty = i - 1;
				}
				currentEmpty = 0;
				currentStartEmpty = 0;
				currentlyCountingEmpty = false;

				currentCluster++;
				if (!currentlyCountingCluster) {
					currentlyCountingCluster = true;
					currentStartCluster = i;
				}

				int dist = abs(arr[i]->key - i);
				if (dist > largestDist) {
					farthestString = arr[i]->value;
					largestDist = dist;
					a = i;
					b = arr[i]->key;
				}
			}
			else {
				cout << i << " " << -1 << endl;

				currentEmpty++;
				if (!currentlyCountingEmpty) {
					currentlyCountingEmpty = true;
					currentStartEmpty = i;
				}

				if (currentCluster > largestCluster) {
					largestCluster = currentCluster;
					startCluster = currentStartCluster;
					endCluster = i - 1;
				}
				currentCluster = 0;
				currentStartCluster = 0;
				currentlyCountingCluster = false;
			}
		}
		cout << "Non-empty addresses: " << nonEmpty << endl;
		cout << "Load factor: " << ((double)nonEmpty / 1000) << endl;
		cout << "Longest empty area on table from index " << startEmpty << " to index " << endEmpty << " with " << largestEmpty << " empty values." << endl;
		cout << "Largest cluster on table from index " << startCluster << " to index " << endCluster << " with " << largestCluster << " consecutive values." << endl;
		cout << "Word that is farthest from actual address is " << farthestString << " with a distance of " << largestDist << " with table address " << a << " and hash address " << b << endl;
	}
};

// Generates a hash for a given string
// word: The string to generate the hash from
// Returns the generated hash
int genHash(string word) {
	int h = 0;
	int C = 123;
	int m = 1000;
	for (int i = 0; i < word.length(); i++) {
		h = (h * C + (int)word[i]) % m;
	}
	return h;
}

// Creates and displays a hash table from the given file
// filename: The name of the file to be used
void genTable(string filename) {
	ifstream file;
	file.open(filename);
	HashMap<int, string> *map = new HashMap<int, string>;
	while (!file.eof()) {
		string word;
		file >> word;
		if (word == "resting-place") {
			map->insertNode(genHash("resting"), "resting");
			map->insertNode(genHash("place"), "place");
		}
		else {
			word.erase(remove_if(word.begin(), word.end(), ispunct), word.end()); // removes punctuation
			if (word.length() != 0) {
				map->insertNode(genHash(word), word);
			}
		}
	}
	map->display();
	file.close();
}

// Number of vertices in the graph 
#define V 10

int minDistance(int dist[], bool sptSet[])
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min) min = dist[v], min_index = v;
	return min_index;
}

void printSolution(int dist[])
{
	printf("Vertex \t\t Distance from Source\n");
	for (int i = 0; i < V; i++) {
		printf("%d \t\t %d\n", i, dist[i]);
	}
}

void dijkstra(vector<vector<int>> graph, int src, int dest) {
	int dist[V]; // The output array.  dist[i] will hold the shortest 
	// distance from src to i 

	bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest 
	// path tree or shortest distance from src to i is finalized 

	// Initialize all distances as INFINITE and stpSet[] as false 
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0 
	dist[src] = 0;

	// Find shortest path for all vertices 
	for (int count = 0; count < V - 1; count++) {
		// Pick the minimum distance vertex from the set of vertices not 
		// yet processed. u is always equal to src in the first iteration. 
		int u = minDistance(dist, sptSet);

		// Mark the picked vertex as processed 
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex. 
		for (int v = 0; v < V; v++)

			// Update dist[v] only if is not in sptSet, there is an edge from 
			// u to v, and total weight of path from src to  v through u is 
			// smaller than current value of dist[v] 
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

	// print the constructed distance array 
	//printSolution(dist);
	cout << "The shortest distance from node " << src << " to node " << dest << " is " << dist[dest];
}

int main() {
	genTable("Raven.txt");

	ifstream file;
	file.open("Graph.txt");
	string strSize;
	file >> strSize;
	int size = stoi(strSize); // gets size of matrix

	vector<vector<int>> graph(size, vector<int>(size, 0));
	int currentRow = 0;
	int currentCol = 0;

	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			string strNum;
			file >> strNum;
			int num = stoi(strNum);
			graph[i][j] = num;
		}
	}
	
	
	file.close();

	int src;
	int dest;
	cout << "Enter a source node: ";
	cin >> src;
	fflush(stdin);
	cout << "Enter a destination node: ";
	cin >> dest;
	dijkstra(graph, src, dest);
}