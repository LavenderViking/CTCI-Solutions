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
#include <set>
#include <vector>
#include <array>
#include <queue>
using namespace std;

// s: smaller string, b: bigger string, loc: location in b:
bool isSubstringAtLocation(string s, string b, int loc) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != b[i+loc]) return false;
	}

	return true;
}

// 1: Brute force: O(bkt)  b = length of longer string, k = length of longest string in T, t = count of strings in T
unordered_map<string,vector<int>> multiSearch(string b, vector<string> T) {

	int len = b.length();

	unordered_map<string,vector<int>> S;

	for (int i = 0; i < T.size(); i++) {
		string s = T[i];

		for (int i = 0; i < len; i++) {
			if (isSubstringAtLocation(s,b,i)) S[s].push_back(i);
		}
	}

	return S;
}



void print(unordered_map<string,vector<int>> map) {
        for (auto const &it : map) {
                string s = it.first;
                cout << s << "-> {";
                for (auto const &it2 : it.second) {
                        cout << it2 << ",";
                }
                cout << "}" << endl;
        }
}

class Trie {
	char c = '\0';
	vector<int> indexes;
	unordered_map<char,Trie*> children;

	public:
	Trie() { }
	Trie(char _c) { c = _c; };
	
	void insertIndex(int _index) { indexes.push_back(_index); }
	void insertChild(char _c) { children[_c] = new Trie(_c); }

	vector<int> getIndexes() { return indexes; }
	unordered_map<char,Trie*>& getChildren() { return children; }	

	vector<int> getBackIndexesForTarget(string target) {
		if (target == "") return indexes;

		char c = target[0];

		if (children.count(c) > 0) {
			return this->children[c]->getBackIndexesForTarget(target.substr(1,target.length()-1));
		}

		return {};
	}

	int getChildrenIndexCount() {
		int count = 0;
		for (auto it : children) count += it.second->indexes.size();
		return count;
	}
};

void printTrie(Trie *trie) {
	cout << "Trie: " << endl;

	queue<char> q1;
	queue<Trie*> q2;
	
	for (auto it : trie->getChildren()) {
		q1.push(it.first);
		q2.push(it.second);
	}
	cout << endl;

	while (!q1.empty()) {
		char c = q1.front();
		Trie *t = q2.front();
		q1.pop(); q2.pop();

		cout << c << " ";
		cout << "indexes = ";

		for (int ii = 0; ii < t->getIndexes().size(); ii++) cout << t->getIndexes()[ii] << " ";
		cout << endl;
		for (auto it : t->getChildren()) {
			q1.push(it.first);
			q2.push(it.second);
		}
	}
	
	cout << endl;
}

void insertString(int move, string s, Trie *trie) {
	Trie *temp = trie;
	char *c = &s[0];

	for (int j = 0; j < s.length(); ++j,++c) {
		if (temp->getChildren().count(*c) == 0) temp->insertChild(*c);
		temp = temp->getChildren()[*c];
		temp->insertIndex(move+j);
	}
}

void buildTree(vector<string> T, Trie *trie, bool usePrefix) {
	for (int i = 0; i < T.size(); i++) {
		int move = usePrefix ? i : 0;
		insertString(move,T[i],trie);
	}
}

// 2: Almost optimal: O(b^2 + kt) b = length of longer string, k = length of longest string in T, t = count of strings in T
unordered_map<string,vector<int>> multiSearch2(string b, vector<string> T) {
	unordered_map<string,vector<int>> map;

	// Build trie:
	Trie *trie = new Trie();
	vector<string> prefixes;
	for (int i = 0; i < b.length(); i++) prefixes.push_back(b.substr(i,b.length()-i));
	buildTree(prefixes,trie,true);
	
	// Search through trie for strings in T:
	for (int i = 0; i < T.size(); i++) {
		string str = T[i];
		vector<int> backIndexes = trie->getBackIndexesForTarget(str);
		for (auto &it : backIndexes) it -= (str.length()-1);
		if (backIndexes.size() > 0) map[str] = backIndexes;
	}

	return map;
}

// 3: Optimal: O(bk + kt) b = length of longer string, k = length of longest string in T, t = count of strings in T
unordered_map<string,vector<int>> multiSearch3(string b, vector<string> T) {
	unordered_map<string,vector<int>> map;

	// Build trie:
	Trie *trie = new Trie();
	buildTree(T,trie,false);


	// Loop over longer string b and find which sub words are in T:
	for (int i = 0; i < b.length(); i++) {
		int j = i;
		char c = b[j];
		if (trie->getChildren().count(c) == 0) continue;
		
		Trie *temp = trie;

		while (temp->getChildren().count(c) > 0) {
			temp = temp->getChildren()[c];
			if (temp->getIndexes().size() > temp->getChildrenIndexCount()) {
				string str = b.substr(i,j-i+1);
				map[str].push_back(i);
			}
			c = b[++j];
		}
		c = b[--j];	
	}

	return map;
}


int main() {

	string b = "mississippi";
	//string b = "bibs";
	//vector<string> T = {"b"};
	vector<string> T = {"is","ppi","hi","sis","i","ssippi","ipp"};

	cout << "Large string : " << b << endl;
	cout << "Small strings : ";
	for (auto it : T) cout << it << " ";
	cout << endl;

	unordered_map<string,vector<int>> map = multiSearch(b,T);
	unordered_map<string,vector<int>> map2 = multiSearch2(b,T);
	unordered_map<string,vector<int>> map3 = multiSearch3(b,T);

	cout << "\nCorrect solution : " << endl;
	print(map);

	cout << endl << "Optimized2 solution : " << endl;
	print(map2);

	cout << endl << "Optimized3 solution : " << endl;
	print(map3);

	return 0;
}


