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
#include <set>
using namespace std;



// Implement a hash table with chaining:
class hashTable {
	vector<set<string>> A;
	int size;
	double max_load_factor = 0.67;
	int used=0;
	double load_factor = 0;

	public:	
	hashTable(int size) {
		A = vector<set<string>>(size);
		this->size = size;
	}

	void insert(string s) {
		int hash = getHash(s);

		A[hash].insert(s);
		used++;
		load_factor = used / (size*1.0);

		if (load_factor > max_load_factor) {
			cout << "Resizing " << endl;
			int oldsize = size;
			size *= 2;
			vector<set<string>> Anew(size);
			
			// Move items from old hash table into the new one:
			for (int i = 0; i < oldsize; ++i) {
				for (auto const &it : A[i]) {
					int hash = getHash(it);
					Anew[hash].insert(it);
				}
			}

			A = Anew;
			load_factor /= 2;
		}
	}

	bool contains(string s) {
		int hash = getHash(s);
		return A[hash].count(s) > 0 ? true : false;
	}

	int getHash(string s) {
		int h = 7;
		for (int i = 0; i < s.length(); ++i) h = (h*7) + (s[i]-'0');
		return h%size;
	}

	void print() {
		cout << "Printing hash table\n";
		cout << "Load factor:" << load_factor << "with " << used << " items\n";
		for (int i = 0; i < size; i++) {
			cout << i << "->";
			for (auto const &it : A[i]) cout << it << ",";
			cout << endl;
		}
	}
};


int main() {


	hashTable HT = hashTable(5);

	HT.insert("TAG");
	HT.insert("AMG");
	HT.insert("BMW");
	HT.print();
	HT.insert("MBW");
	HT.print();

	cout << "Contains TAG " << HT.contains("TAG") << endl;

	return 0;
}


