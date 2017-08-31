#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <ctime>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <array>
#include <list>
using namespace std;


// Uses a hash table to map keys to locations of strings in a doubly
// linked list. 

// HT: 
// 1 -> location of Tomas
// 6 -> location of Jeroen
// 9 -> location of Katrin
// 33 -> location of Viola

//     1              6               9                33        HASH TABLE
//     |              |               |                |
//     V              V               V                V
//  {1,Tomas} <--> {6,Jeroen} <--> {9,Katrin} <--> {33,Viola}    DOUBLY LINKED LIST


class LRUcache {

	int SIZE = 0;
	int usedSize = 0;
	unordered_map<int,list<pair<int,string>>::iterator> cache;
	list<pair<int,string>> l; 

	public:
	LRUcache(int size) { SIZE = size; }

	void insert(int key, string value) {
		// Create a new doubly linked list node with the {key,value} pair.
		// Insert key->node mapping into hash table:
		cout << "Inserting " << value << "lru = " << lru() << endl;
		auto it = cache.find(key);

		// Value is in cache:
		if (it != cache.end()) {
			// Remove node from the linked list:
			l.erase(it->second);
			// Put node to front of list:
			l.push_front({key,value});
			// Update node's location in the hash table:
			it->second = l.begin();		
		} else {
			// Value is not in cache:
			// Evict least recently used item if cache is full:
			if (usedSize == SIZE) {
				// Delete last node from cache:
				cache.erase(l.back().first);
				// Delete last node from linked list:
				l.pop_back();
			} else {
				usedSize++;		
			}

			// Insert new {key,value} pair to the front of the list:
			l.push_front({key,value});
			// Add address of node to hash table:
			cache[key] = l.begin();
		}

		cout << "cache = " << endl;

		for (auto it : cache) {
			cout << it.first << endl;
		}

		cout << endl << "list = " << endl;

		for (auto it : l) cout << it.first << endl;
		cout << endl;
	}

	string retrieve(int key) {
		// Lookup the key in the hash table and find which node in the linked list
		// contains the value associated with this key:
		cout << "Retrieving " << key << endl;
		auto it = cache.find(key);
		if (it == cache.end()) return "-1"; // key not in hash table:
		
		// Move the node to the front of the linked list.
		l.erase(it->second);
		l.push_front({key,it->second->second});
		it->second = l.begin();

		cout << "cache = " << endl;

		for (auto it : cache) {
			cout << it.first << endl;
		}

		cout << endl << "list = " << endl;

		for (auto it : l) cout << it.first << endl;
		cout << endl;


		return l.front().second;
	}

	string lru() {
		// Return the value at the end of the linked list:
		if (l.size() == 0) return "";

		return l.back().second;
	}

	string mru() {
		// Return the value at the end of the linked list:
		if (l.size() == 0) return "";

		return l.front().second;
	}
};



int main() {


	LRUcache LRU = LRUcache(2);

	LRU.insert(1,"1");
	LRU.insert(2,"2");
	LRU.retrieve(1);
	LRU.insert(3,"3");
	LRU.retrieve(2);
	LRU.insert(4,"4");
	LRU.retrieve(1);
	LRU.retrieve(3);
	LRU.retrieve(4);


/*	LRUcache LRU = LRUcache(5);

	LRU.insert(5,"tag");
	LRU.insert(7,"arnar");
	LRU.insert(9,"gud");
	LRU.insert(11,"jon");
	LRU.retrieve(5);
	LRU.insert(0,"james");
	LRU.insert(90,"yoyo");
	cout << LRU.retrieve(5);*/

	return 0;
}


