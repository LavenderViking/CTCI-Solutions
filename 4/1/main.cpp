#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>
#include <queue>
#include <deque>
#include <unordered_set>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)


class Graph {
	private:
		int V;
		unordered_set<int> *array;

	public:
		Graph(int V) {
			this->V = V;
			array = new unordered_set<int>[V];
		}

		void addEdge(int src, int dest) {
			array[src].insert(dest);
		}

		unordered_set<int> adjList(int V) {
			return array[V];
		}

		int getNumV() {
			return V;
		}

		void printGraph() {
			fori(0,V) {
				cout << i << ":" ;
				for (const auto& elem : array[i]) {
					cout << elem << " " ;
				}
				cout << endl;
			}
		}
};


bool isRouteBetween(int V1, int V2, Graph G) {
	queue<int> q;
	bool visited[G.getNumV()];

	q.push(V1);

	while(!q.empty()) {
		int V = q.front();
		q.pop();
		visited[V] = true;

		for (const auto& v : G.adjList(V)) {
			if (v == V2) return true;
			if (!visited[v]) q.push(v);
		}
	}
	return false;
}


int main() {

	ifstream file;
	file.open("input.txt");

	int n1;
	file >> n1;

	Graph g(5);
	g.addEdge(0,1);
	g.addEdge(1,0);
	g.addEdge(0,4);
	g.addEdge(1,2);
	g.addEdge(1,3);
	g.addEdge(1,4);
	g.addEdge(2,3);
	g.addEdge(3,4);


	cout << "isRoute = " << isRouteBetween(0,4,g) << endl;

	g.printGraph();
	file.close();

	return 0;
}

