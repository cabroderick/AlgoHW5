#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Edge;

//template for generic type 
template<typename K, typename V>

//Hashnode class 
class HashNode
{
public:
	V value;
	K key;

	//Constructor of hashnode  
	HashNode(K key, V value)
	{
		this->value = value;
		this->key = key;
	}
};

//template for generic type 
template<typename K, typename V>

//Our own Hashmap class 
class HashMap
{
	//hash element array 
	HashNode<K, V>** arr;
	int capacity;
	//current size 
	int size;
	//dummy node 
	HashNode<K, V>* dummy;

public:
	HashMap()
	{
		//Initial capacity of hash array 
		capacity = 1000;
		size = 0;
		arr = new HashNode<K, V> * [capacity];

		//Initialise all elements of array as NULL 
		for (int i = 0; i < capacity; i++)
			arr[i] = NULL;

		//dummy node with value and key -1 
		//dummy = new HashNode<K, V>(-1, -1);
	}
	// This implements hash function to find index 
	// for a key 
	int hashCode(K key)
	{
		return key % capacity;
	}

	//Function to add key value pair 
	void insertNode(K key, V value)
	{
		HashNode<K, V>* temp = new HashNode<K, V>(key, value);
		// Apply hash function to find index for given key 
		int hashIndex = key;
		//find next free space 
 
		while (arr[hashIndex] != NULL && arr[hashIndex]->key == key && arr[hashIndex]->key != -1) {
			if (arr[hashIndex]->value == value) return;
			hashIndex++;
			hashIndex %= capacity;
		}
		while (arr[hashIndex] != NULL && arr[hashIndex]->key != key && arr[hashIndex]->key != -1) {
			hashIndex++;
			hashIndex %= capacity;
		}
		//if new node to be inserted increase the current size 
		if (arr[hashIndex] == NULL || arr[hashIndex]->key == -1)
			size++;
		arr[hashIndex] = temp;
	}
	//Function to delete a key value pair 
	V deleteNode(int key)
	{
		// Apply hash function to find index for given key 
		int hashIndex = hashCode(key);

		//finding the node with given key 
		while (arr[hashIndex] != NULL)
		{
			//if node found 
			if (arr[hashIndex]->key == key)
			{
				HashNode<K, V>* temp = arr[hashIndex];

				//Insert dummy node here for further use 
				arr[hashIndex] = dummy;

				// Reduce size 
				size--;
				return temp->value;
			}
			hashIndex++;
			hashIndex %= capacity;

		}

		//If not found return null 
		return NULL;
	}

	//Function to search the value for a given key 
	V get(int key)
	{
		// Apply hash function to find index for given key 
		int hashIndex = hashCode(key);
		int counter = 0;
		//finding the node with given key    
		while (arr[hashIndex] != NULL)
		{
			int counter = 0;
			if (counter++ > capacity)  //to avoid infinite loop 
				return NULL;
			//if node found return its value 
			if (arr[hashIndex]->key == key)
				return arr[hashIndex]->value;
			hashIndex++;
			hashIndex %= capacity;
		}

		//If not found return null 
		return NULL;
	}

	//Return current size  
	int sizeofMap()
	{
		return size;
	}

	//Return true if size is 0 
	bool isEmpty()
	{
		return size == 0;
	}

	//Function to display the stored key value pairs 
	void display()
	{
		int nonEmpty = 0;
		// variables for counting empty

		bool currentlyCountingEmpty = false;

		int startEmpty = 0;
		int endEmpty = 0;
		int currentStartEmpty = 0;
		int largestEmpty = 0;
		int currentEmpty = -1;

		// variables for counting cluster

		bool currentlyCountingCluster = false;

		int startCluster = 0;
		int endCluster = 0;
		int currentStartCluster;
		int largestCluster = 0;
		int currentCluster = 0;

		// variables for counting farthest string
		string farthestString = "";
		int largestDist = 0;
		int a; // index
		int b; // hash

		for (int i = 0; i < capacity; i++)
		{
			if (arr[i] != NULL && arr[i]->key != -1) { // non-empty
				nonEmpty++;
				cout << i << " " << arr[i]->value << " " << arr[i]->key << endl;

				// old
				if (currentEmpty > largestEmpty) {
					largestEmpty = currentEmpty;
					startEmpty = currentStartEmpty;
					endEmpty = i - 1;
				}
				currentEmpty = 0;
				currentStartEmpty = 0;
				currentlyCountingEmpty = false;

				// new
				currentCluster++;
				if (!currentlyCountingCluster) {
					currentlyCountingCluster = true;
					currentStartCluster = i;
				}

				int dist = abs(arr[i]->key - i); // difference between hash address and actual hash address
				if (dist > largestDist) {
					farthestString = arr[i]->value;
					largestDist = dist;
					a = i;
					b = arr[i]->key;
				}
			}
			else { // empty
				cout << i << " " << -1 << endl;

				// old
				currentEmpty++;
				if (!currentlyCountingEmpty) {
					currentlyCountingEmpty = true;
					currentStartEmpty = i;
				}

				// new
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

class Node {
	vector<Edge> connected;
};

class Edge {
	Node connected;
};

int main() {
	genTable("Raven.txt");
}